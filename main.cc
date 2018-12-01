#include<vector>
#include<iostream>
#include<valarray>

#include "gravity.h"

void remove_total_momentum(std::vector<Body>& bodies) {
	auto total_p = point_type{0.,0.,0.};
	for(auto body: bodies) {
		total_p += body.vel*body.mass;
	}
	for(auto& body: bodies) {
		body.vel -= total_p/body.mass/bodies.size();
	}
}
	

int main(int argc, char *argv[]) {
	auto planets = std::vector<Body>{};
	double r = 6.;
	auto vel = 2.;
	auto sun = Body({0.,0.,0.}, {0.,0.,0.,}, 10.);
	auto earth = Body({r,0.,0.}, {0.,vel,0.,}, 1.);
	planets.push_back(sun);
	planets.push_back(earth);
	remove_total_momentum(planets);
	for(auto i = 0; i<10;i+=1) {
			for(auto v = 0.; v<10;++v) {
			planets.push_back(Body({r+i/20.,0,0}, {0,v+v/20.,0}, 1.));
	}}
	for(auto i = 0; i<6; ++i) {
		std::cout<<planets.size()<<" ";
	}
	std::cout<<'\n';
	//planets.push_back(earth);
	//planets.push_back(Body{{1.5*r,0.,0.}, {-0.2,-2.,0.} , 1.});
	predict(planets, 1000., 2);
}
