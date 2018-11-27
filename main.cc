#include<iostream>
#include<vector>
using state_type = std::vector<double>;

int n_bodies = 10000;

enum index_type {
	pos_x = 0,
	pos_y = 1,
	pos_z = 2,
	vel_x = 3,
	vel_y = 4,
	vel_z = 5,
};

template<index_type i>
int idx(int body_number) {
	return i*n_bodies + body_number;
}


void calculate_forces(const state_type &x, state_type &dxdt, const double t) {
	auto deltas = new double[n_bodies*6];
	for(int i = 0; i<n_bodies; ++i) {
		dxdt[idx<pos_x>(i)] = x[idx<pos_x>(i)];
		dxdt[idx<pos_y>(i)] = x[idx<pos_y>(i)];
		dxdt[idx<pos_z>(i)] = x[idx<pos_z>(i)];
		dxdt[idx<vel_x>(i)] = 0.;
		dxdt[idx<vel_y>(i)] = 0.;
		dxdt[idx<vel_z>(i)] = 0.;
	}
}

int main() {
	state_type a(6*n_bodies, 0.);
	state_type b(6*n_bodies);
	for(int i=0; i<1e4; ++i) {
		calculate_forces(a, b, 1.);
	}
	//for(auto x: b) {
	//	std::cout<<x<<" ";
	//}
	//std::cout<<std::endl;
}
