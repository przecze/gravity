#include<iostream>
#include<vector>
#include<cmath>
using state_type = std::vector<double>;

int n_bodies = 1000;
int n_active_bodies = 10;

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

int aidx(int body_number) {
	return i*n_active_bodies + body_number;
}


void calculate_forces(const state_type &x, state_type &dxdt, const double t) {
	std::vector<std::vector<double>> deltas(3*n_active_bodies, std::vector<double>(n_bodies));
	std::vector<std::vector<double>> r(n_active_bodies, std::vector<double>(n_bodies));
	for(int j = 0; j<n_bodies; ++j)
		dxdt[idx<pos_x>(i)] = x[idx<pos_x>(i)];
		dxdt[idx<pos_y>(i)] = x[idx<pos_y>(i)];
		dxdt[idx<pos_z>(i)] = x[idx<pos_z>(i)];
	for(int i = 0; i<n_active_bodies; ++i) {
		for(int j = 0; j<n_bodies; ++j) {
			deltas[aidx<pos_x>(i)][j] = x[idx<pos_x>(j)] - x[idx<pos_x>(i)];
			deltas[aidx<pos_y>(i)][j] = x[idx<pos_y>(j)] - x[idx<pos_y>(i)];
			deltas[aidx<pos_z>(i)][j] = x[idx<pos_z>(j)] - x[idx<pos_z>(i)];
			r[i][j]  = std::pow(deltas[aidx<pos_x>(i)][j], 2);
			r[i][j] += std::pow(deltas[aidx<pos_y>(i)][j], 2);
			r[i][j] += std::pow(deltas[aidx<pos_z>(i)][j], 2);
			dxdt[idx<vel_x>(i)] += deltas[aidx<pos_x>(i)][j]/(r[i]*std::sqrt(r[i]));
			dxdt[idx<vel_y>(i)] += deltas[aidx<pos_y>(i)][j]/(r[i]*std::sqrt(r[i]));
			dxdt[idx<vel_z>(i)] += deltas[aidx<pos_z>(i)][j]/(r[i]*std::sqrt(r[i]));
		}
	}
}

int main() {
	state_type a(6*n_bodies, 0.);
	for(int i=0; i<n_bodies; ++i) {
		a[idx<pos_x>(i)] = i;
		a[idx<pos_y>(i)] = i;
		a[idx<pos_z>(i)] = i;
	}
	state_type b(6*n_bodies);
	for(int i=0; i<1e3; ++i) {
		calculate_forces(a, b, 1.);
	}
	//for(auto x: b) {
	//	std::cout<<x<<" ";
	//}
	//std::cout<<std::endl;
}
