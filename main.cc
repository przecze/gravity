#include<valarray>
#include<cmath>
#include<array>
#include<iostream>
#include<functional>
#include <boost/numeric/odeint.hpp>


enum index_type {
	pos_x = 0,
	pos_y = 1,
	pos_z = 2,
	vel_x = 3,
	vel_y = 4,
	vel_z = 5,
};

using ContainerType = std::array<std::valarray<double>, 3>;

ContainerType get_container(size_t size) {
	auto container = ContainerType{};
	std::fill(container.begin(), container.end(), std::valarray<double>(size));
	return container;
}

class GravityModel {
public:


	std::valarray<double> mass;

	double G=10.;
	int n_active_bodies;


	void calculate_momentum(const ContainerType &q, ContainerType &dpdt) {
		for(auto i = n_active_bodies; i-->0;) {
			const auto b_x = q[pos_x][i];
			const auto b_y = q[pos_y][i];
			const auto b_z = q[pos_z][i];
			for(int j = q.size(); j --> i+1;) {
				const auto delta_x = q[pos_x][j] - b_x;
				const auto delta_z = q[pos_y][j] - b_y;
				const auto delta_y = q[pos_z][j] - b_z;
				const auto r2 = delta_x * delta_x
					+ delta_y * delta_y
					+ delta_z * delta_z;
				const auto f = G*mass[i]*mass[j]/(r2*std::sqrt(r2));
				dpdt[pos_x][j] -= f*delta_x;
				dpdt[pos_y][j] -= f*delta_y;
				dpdt[pos_z][j] -= f*delta_z;
			}
			for(int j = i; j --> 0;) {
				const auto delta_x = q[pos_x][j] - b_x;
				const auto delta_z = q[pos_y][j] - b_y;
				const auto delta_y = q[pos_z][j] - b_z;
				const auto r2 = delta_x * delta_x
					+ delta_y * delta_y
					+ delta_z * delta_z;
				const auto f = G*mass[i]*mass[j]/(r2*std::sqrt(r2));
				dpdt[pos_x][j] -= f*delta_x;
				dpdt[pos_y][j] -= f*delta_y;
				dpdt[pos_z][j] -= f*delta_z;
			}
		}
	}

	void calculate_positions(const ContainerType &p, ContainerType &dqdt) {
		for(int j = p.size(); j --> 0;) {
			dqdt[pos_x][j] = p[pos_x][j] / mass[j];
			dqdt[pos_y][j] = p[pos_y][j] / mass[j];
			dqdt[pos_z][j] = p[pos_z][j] / mass[j];
		}
	}
};

using point_type = std::valarray<double>;
struct Body {
	point_type pos;
	point_type vel;
	double mass;
	Body(point_type pos, point_type vel, double mass): pos(pos), vel(vel), mass(mass){}
};

struct System {
	ContainerType q;
	ContainerType p;
	std::valarray<double> mass;
};

System rewrite(const std::vector<Body>& bodies) {
	auto count = bodies.size();
	auto s = System{};
	s.q = get_container(count);
	s.p = get_container(count);
	s.mass = std::valarray<double>(count);
	for(auto j = count; j --> 0;) {
		const auto& body = bodies[j];
		for(auto dim=3; dim --> 0;) {
			s.q[dim][j] = body.pos[dim];
			s.p[dim][j] = body.vel[dim];
		}
		s.mass[j] = body.mass;
	}
	return s;
}
	

struct positions_functor
{
    GravityModel &gm;

    positions_functor(GravityModel &agm) : gm(agm) { }

    void operator()( const ContainerType &p , ContainerType &dqdt ) const
    {
			gm.calculate_positions(p, dqdt);
    }
};

struct momentum_functor
{
    GravityModel &gm;

    momentum_functor(GravityModel &agm) : gm(agm) { }

    void operator()( const ContainerType &q , ContainerType &dpdt ) const
    {
			gm.calculate_momentum(q, dpdt);
    }
};

struct printing_functor {
	std::ostream& out;
	printing_functor(std::ostream& out): out(out){}
	template<typename State>
	void operator()(const State& x, double t) const {
		const auto& q = x.first;
		const auto& p = x.second;
		for(auto j=q[0].size(); j --> 0;) {
			out<<q[pos_x][j]<<" "<<q[pos_y][j]<<" "<<q[pos_z][j]<<' ';
			out<<p[pos_x][j]<<" "<<p[pos_y][j]<<" "<<p[pos_z][j]<<'\n';
		}
		std::cout<<std::flush;
	}
};

void predict(std::vector<Body> bodies, double t) {
	auto s = rewrite(bodies);
	auto gm = GravityModel{};
	gm.n_active_bodies = s.p.size();
	gm.mass = s.mass;
	using namespace boost::numeric::odeint;
  using StepperType = symplectic_rkn_sb3a_mclachlan< ContainerType >;
	const double dt = 1.;
	integrate_const(
					StepperType(),
					std::make_pair(positions_functor(gm), momentum_functor(gm)),
					std::make_pair(std::ref(s.q), std::ref(s.p)),
					0.0, t, dt, printing_functor(std::cout));
}

int main(int argc, char *argv[]) {
	auto n_bodies=3;
	auto planets = std::vector<Body>{};
	double r = 100.;
	planets.push_back(Body{{-r,0.,0.}, {0.,1.,0.}, 1.});
	planets.push_back(Body{{0.,0.,0.}, {0.2,1.,0.}, 5.});
	planets.push_back(Body{{1.5*r,0.,0.}, {-0.2,-2.,0.} , 1.});
	predict(planets, 1000.);
}
