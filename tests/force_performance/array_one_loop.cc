#include<vector>
#include<cmath>
#include "scenario.h"
#include "common.h"
using state_type = std::array<double, 6*N_BODIES>;

std::array<double, N_BODIES> mass;

double G=1.;

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
	return i*N_BODIES + body_number;
}

template<index_type i>
int aidx(int body_number) {
	return i*N_ACTIVE_BODIES + body_number;
}


void calculate_forces(const state_type &x, state_type &dxdt, const double t) {
	for(int j = 0; j<N_BODIES; ++j) {
		dxdt[idx<pos_x>(j)] = x[idx<pos_x>(j)];
		dxdt[idx<pos_y>(j)] = x[idx<pos_y>(j)];
		dxdt[idx<pos_z>(j)] = x[idx<pos_z>(j)];
	}
	for(int i = 0; i<N_ACTIVE_BODIES; ++i) {
		for(int j = 0; j<N_BODIES; ++j) {
			if(i==j) continue;
			auto delta_x = x[idx<pos_x>(j)] - x[idx<pos_x>(i)];
			auto delta_y = x[idx<pos_y>(j)] - x[idx<pos_y>(i)];
			auto delta_z = x[idx<pos_z>(j)] - x[idx<pos_z>(i)];
			auto r  = std::pow(delta_x, 2) + std::pow(delta_y, 2) + std::pow(delta_z, 2);
			auto r3 = r *std::sqrt(r);
			auto f = G*mass[i]/r3;
			dxdt[idx<vel_x>(j)] -= f*delta_x;
			dxdt[idx<vel_y>(j)] -= f*delta_y;
			dxdt[idx<vel_z>(j)] -= f*delta_z;
		}
	}
}

int main() {
	std::fill(mass.begin(), mass.end(), 1.);
	state_type a;
	std::fill(a.begin(), a.end(), 0.);
	for(int i=0; i<N_BODIES; ++i) {
		a[idx<pos_x>(i)] = i;
		a[idx<pos_y>(i)] = i;
		a[idx<pos_z>(i)] = i;
		a[idx<vel_x>(i)] = i;
		a[idx<vel_y>(i)] = i;
		a[idx<vel_z>(i)] = i;
	}
	state_type b;
	std::fill(b.begin(), b.end(), 0.);
	for(int i=0; i<EVALUATION_COUNT; ++i) {
		calculate_forces(a, b, 1.);
	}
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[idx<vel_x>(i)]);
	}
	std::cout<<std::endl;
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[idx<vel_y>(i)]);
	}
	std::cout<<std::endl;
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[idx<vel_z>(i)]);
	}
	std::cout<<std::endl;

}
