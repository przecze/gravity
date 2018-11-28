#include<vector>
#include<cmath>
#include<valarray>
#include<array>
#include "common.h"
#include "scenario.h"
using state_type = std::array<std::valarray<double>,6>;


const std::valarray<double> mass(1.,N_BODIES);

double G=1.;

constexpr int	pos_x = 0;
constexpr int	pos_y = 1;
constexpr int	pos_z = 2;
constexpr int	vel_x = 3;
constexpr int	vel_y = 4;
constexpr int	vel_z = 5;


void calculate_forces(const state_type &x, state_type &dxdt, const double t) {
	dxdt[pos_x] = x[vel_x];
	dxdt[pos_y] = x[vel_y];
	dxdt[pos_z] = x[vel_z];
	std::valarray<double> same(0., N_BODIES);
	same[N_ACTIVE_BODIES] = 1.;
	for(auto i = N_ACTIVE_BODIES; i-->0;) {
		same = same.shift(1);
		const auto b_x = x[pos_x][i];
		const auto b_y = x[pos_y][i];
		const auto b_z = x[pos_z][i];
		const std::valarray<double> delta_x = x[pos_x] - b_x;
		const std::valarray<double> delta_z = x[pos_y] - b_y;
		const std::valarray<double> delta_y = x[pos_z] - b_z;
		const std::valarray<double> r2 = delta_x * delta_x
		  + delta_y * delta_y
		  + delta_z * delta_z;
		const std::valarray<double> f = G*mass/(r2*std::sqrt(r2) + same);
		dxdt[vel_x] -= f*delta_x;
		dxdt[vel_y] -= f*delta_y;
		dxdt[vel_z] -= f*delta_z;
	}
}

int main() {
	state_type a;
  std::fill(a.begin(), a.end(), std::valarray<double>(N_BODIES));
	for(int i=0; i<N_BODIES; ++i) {
		a[pos_x][i] = i;
		a[pos_y][i] = i;
		a[pos_z][i] = i;
		a[vel_x][i] = i;
		a[vel_y][i] = i;
		a[vel_z][i] = i;
	}
	state_type b;
  std::fill(std::begin(b), std::end(b), std::valarray<double>(N_BODIES));
	for(int i=0; i<EVALUATION_COUNT; ++i) {
		calculate_forces(a, b, 1.);
	}
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[vel_x][i]);
	}
	std::cout<<std::endl;
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[vel_y][i]);
	}
	std::cout<<std::endl;
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[vel_z][i]);
	}
	std::cout<<std::endl;

}
