#include<vector>
#include<cmath>
#include<array>


enum index_type {
	pos_x = 0,
	pos_y = 1,
	pos_z = 2,
	vel_x = 3,
	vel_y = 4,
	vel_z = 5,
};

using StateType = std::array<std::vector<double>, 6>;

class GravityModel {
public:


	std::vector<double> mass;

	double G=1.;
	int n_active_bodies;


	void calculate_momentum(const StateType &x, StateType &dxdt, const double t) {
		for(auto i = n_active_bodies; i-->0;) {
			const auto b_x = x[pos_x][i];
			const auto b_y = x[pos_y][i];
			const auto b_z = x[pos_z][i];
			for(int j = x.size(); j --> 0;) {
				dxdt[pos_x][j] = x[vel_x][j];
				dxdt[pos_y][j] = x[vel_y][j];
				dxdt[pos_z][j] = x[vel_z][j];
				if(i==j) continue;
				const auto delta_x = x[pos_x][j] - b_x;
				const auto delta_z = x[pos_y][j] - b_y;
				const auto delta_y = x[pos_z][j] - b_z;
				const auto r2 = delta_x * delta_x
					+ delta_y * delta_y
					+ delta_z * delta_z;
				const auto f = G*mass[i]*mass[j]/(r2*std::sqrt(r2));
				dxdt[vel_x][j] -= f*delta_x;
				dxdt[vel_y][j] -= f*delta_y;
				dxdt[vel_z][j] -= f*delta_z;
			}
		}
	}
};

int main() {
	auto gm = GravityModel{};
	auto state = StateType{};
	auto n_bodies=100;
	std::fill(state.begin(), state.end(), std::vector<double>(n_bodies));
	gm.n_active_bodies = 3.;
	gm.mass = std::vector<double>(n_bodies);
}
