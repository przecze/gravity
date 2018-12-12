#include<vector>
#include<iostream>
#include<valarray>
#include<fstream>

#include "natural_units.h"
#include "gravity.h"


void remove_total_momentum(std::vector<Body>& bodies, int active_bodies) {
	using namespace natural_units;
	using boost::units::quantity;
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
	

int main(int argc, char *argv[]) {
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
		
	//remove_total_momentum(planets, n_active_planets);
	//for(auto i = 0; i<10;i+=1) {
	//		for(auto v = 0.; v<10;++v) {
	//		planets.push_back(Body({r+i/20.,0,0}, {0,v+v/20.,0}, 1.));
	//}}
	for(auto i = 0; i<6; ++i) {
		std::cout<<planets.size()<<" ";
	}
	std::cout<<'\n';
	predict(planets, t, n_active_planets, one_over_r);
}
