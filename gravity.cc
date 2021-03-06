#include "gravity.h"

#include<cmath>
#include<array>
#include<iostream>
#include<functional>
#include<fstream>
#include<boost/numeric/odeint.hpp>

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

	std::valarray<bool> stationary;

	int n_active_bodies;

	bool one_over_r=false;

	void calculate_momentum(const ContainerType &q, const ContainerType& p, ContainerType &dpdt, double t) {
		dpdt = get_container(q[0].size());
		for(auto i = n_active_bodies; i-->0;) {
			const auto b_x = q[pos_x][i];
			const auto b_y = q[pos_y][i];
			const auto b_z = q[pos_z][i];
			for(int j = q[0].size(); j --> 0;) {
				if(i==j or stationary[j]) continue;
				const auto delta_x = q[pos_x][j] - b_x;
				const auto delta_y = q[pos_y][j] - b_y;
				const auto delta_z = q[pos_z][j] - b_z;
				const auto r2 = delta_x * delta_x
											+ delta_y * delta_y
											+ delta_z * delta_z;
				const auto f = mass[i]/(one_over_r?(r2):r2*std::sqrt(r2));
				dpdt[pos_x][j] -= f*delta_x;
				dpdt[pos_y][j] -= f*delta_y;
				dpdt[pos_z][j] -= f*delta_z;
			}
		}
	}

	void calculate_positions(const ContainerType &p, ContainerType &dqdt) {
		for(int j = p[0].size(); j --> 0;) {
			if(stationary[j]) {
				dqdt[pos_x][j] = 0;
				dqdt[pos_y][j] = 0;
				dqdt[pos_z][j] = 0;
				continue;
			}
			dqdt[pos_x][j] = p[pos_x][j];
			dqdt[pos_y][j] = p[pos_y][j];
			dqdt[pos_z][j] = p[pos_z][j];
		}
	}
};

using point_type = std::valarray<double>;

struct System {
	ContainerType q;
	ContainerType p;
	std::valarray<double> mass;
	std::valarray<bool> stationary;
};

System rewrite(const std::vector<Body>& bodies) {
	auto count = bodies.size();
	auto s = System{};
	s.q = get_container(count);
	s.p = get_container(count);
	s.mass = std::valarray<double>(count);
	s.stationary = std::valarray<bool>(count);
	for(auto j = count; j --> 0;) {
		const auto& body = bodies[j];
		for(auto dim=3; dim --> 0;) {
			s.q[dim][j] = body.pos[dim];
			s.p[dim][j] = body.vel[dim];
		}
		s.stationary[j] = body.stationary;
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

    void operator()(const ContainerType &q, const ContainerType &p, ContainerType &dpdt, double t) const
    {
			gm.calculate_momentum(q, p, dpdt, t);
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
	}
};

void predict(std::vector<Body> bodies, double t, int active_bodies, bool one_over_r) {
	auto s = rewrite(bodies);
	auto gm = GravityModel{};
	if(active_bodies==-1) {
		active_bodies=s.p[0].size();
	}
	gm.n_active_bodies = active_bodies;
	gm.mass = s.mass;
	gm.stationary = s.stationary;
	gm.one_over_r = one_over_r;
	using namespace boost::numeric::odeint;
  auto stepper = velocity_verlet<ContainerType>{};
	const double dt = 0.1;
	auto curr_t  = 0.;
	auto state = std::make_pair(std::ref(s.q), std::ref(s.p));
	printing_functor(std::cout)(state, 0.);
	while(curr_t<t) {
		stepper.do_step(
						momentum_functor(gm),
						state,
						t, dt);
		curr_t += dt;
		printing_functor(std::cout)(state, 0.);
	}
}

void remove_total_momentum(std::vector<Body>& bodies, int active_bodies) {
	auto total_p = point_type{0.,0.,0.};
	for(int i = 0; i<active_bodies; ++i) {
		const auto& body = bodies[i];
		total_p += body.vel*body.mass;
	}
	for(int i = 0; i<active_bodies; ++i) {
		auto& body = bodies[i];
		body.vel -= total_p/body.mass/bodies.size();
		//std::cout<<"DP"<<body.vel[0]<<" "<<body.vel[1]<<" "<<body.vel[2]<<std::endl;
	}
}

void predict_from_file() {
	auto input = std::fstream{"system.txt"};
	auto planets = std::vector<Body>{};
	double d_n_planets, d_n_active_planets, d_one_over_r, t;
	double dummy;
	input >> d_n_planets >> d_n_active_planets >> d_one_over_r >> t;
	auto one_over_r = d_one_over_r==1.;
	auto n_planets = int(d_n_planets);
	auto n_active_planets = int(d_n_active_planets);
	t = t==-1?1000.:t;
	for(int i = 0; i++<8 - 4;) {
		input >> dummy;
	}
	for(int i = 0; i++<n_planets;) {
		double x, y, z, vx, vy, vz, m, stationary;
		input >> x >> y >> z >> vx >> vy >> vz >>m >> stationary;
		planets.push_back(Body{{x,y,z}, {vx,vy,vz}, m, stationary==1.});
	}
	for(auto i = 0; i<6; ++i) {
		std::cout<<planets.size()<<" ";
	}
	std::cout<<'\n';
	predict(planets, t, n_active_planets, one_over_r);
}
