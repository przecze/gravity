#include<vector>
#include<cmath>
#include "scenario.h"
#include "common.h"
using state_type = std::vector<double>;

std::vector<double> mass(N_BODIES, 1.);

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
		auto delta_x = std::vector<double>(N_BODIES);
		auto delta_y = std::vector<double>(N_BODIES);
		auto delta_z = std::vector<double>(N_BODIES);
		auto f = std::vector<double>(N_BODIES);
		for(int j = 0; j<N_BODIES; ++j) {
			if(i==j) continue;
			delta_x[j] = x[idx<pos_x>(j)] - x[idx<pos_x>(i)];
			delta_z[j] = x[idx<pos_z>(j)] - x[idx<pos_z>(i)];
			delta_y[j] = x[idx<pos_y>(j)] - x[idx<pos_y>(i)];
		}
		for(int j = 0; j<N_BODIES; ++j) {
			if(i==j) continue;
			f[j]  = std::pow(delta_x[j], 2)
					  + std::pow(delta_y[j], 2)
					  + std::pow(delta_z[j], 2);
		  f[j] = f[j] *std::sqrt(f[j]);
			f[j] = G*mass[j]/f[j];
		}
		for(int j = 0; j<N_BODIES; ++j) {
			if(i==j) continue;
			dxdt[idx<vel_x>(j)] -= f[j]*delta_x[j];
			dxdt[idx<vel_y>(j)] -= f[j]*delta_y[j];
			dxdt[idx<vel_z>(j)] -= f[j]*delta_z[j];
		}
	}
}

int main() {
	state_type a(6*N_BODIES, 0.);
	for(int i=0; i<N_BODIES; ++i) {
		a[idx<pos_x>(i)] = i;
		a[idx<pos_y>(i)] = i;
		a[idx<pos_z>(i)] = i;
		a[idx<vel_x>(i)] = i;
		a[idx<vel_y>(i)] = i;
		a[idx<vel_z>(i)] = i;
	}
	state_type b(6*N_BODIES);
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
