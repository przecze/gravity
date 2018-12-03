#include<vector>
#include<iostream>
#include<valarray>
#include<fstream>

#include "gravity.h"

void remove_total_momentum(std::vector<Body>& bodies, int active_bodies) {
	auto total_p = point_type{0.,0.,0.};
	for(int i = 0; i<active_bodies; ++i) {
		const auto& body = bodies[i];
		total_p += body.vel*body.mass;
	}
	for(int i = 0; i<active_bodies; ++i) {
		auto& body = bodies[i];
		body.vel -= total_p/body.mass/bodies.size();
		std::cout<<"DP"<<body.vel[0]<<" "<<body.vel[1]<<" "<<body.vel[2]<<std::endl;
	}
}
	

int main(int argc, char *argv[]) {
	auto input = std::fstream{"system.txt"};
	auto planets = std::vector<Body>{};
	double d_n_planets, d_n_active_planets, t;
	double dummy;
	input >> d_n_planets >> d_n_active_planets >> t;
	auto n_planets = int(d_n_planets);
	auto n_active_planets = int(d_n_active_planets);
	t = t==-1?1000.:t;
	for(int i = 0; i++<7 - 3;) {
		input >> dummy;
	}
	//std::cout<<"D"<<n_active_planets<<" "<<n_active_planets<<" "<<t<<std::endl;
	for(int i = 0; i++<n_planets;) {
		double x, y, z, vx, vy, vz, m;
		input >> x >> y >> z >> vx >> vy >> vz >>m;
		planets.push_back(Body{{x,y,z}, {vx,vy,vz}, m});
		//std::cout<<"D:"<<x<<" "<<y<<" "<<z<<" "<<vx<<" "<<vy<<" "<<vz<<" "<<m<<" "<<std::endl;
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
	predict(planets, t, n_active_planets);
}
