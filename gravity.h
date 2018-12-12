#include<valarray>
#include<vector>

#include "natural_units.h"
#include<boost/units/pow.hpp>

using point_type = std::valarray<double>;
struct Body {
	std::valarray<double>pos;
	std::valarray<double> vel;
	double mass;
	Body(point_type pos, point_type vel, double mass, bool stationary = false): pos(pos), vel(vel), mass(mass), stationary(stationary){}
	bool stationary;
};

using point_type = std::valarray<double>;
struct United_Body {
	std::valarray<quantity<natural_units::length>> pos;
	std::valarray<quantity<natural_units::velocity>> vel;
	quantity<natural_units::mass> mass;
	//United_Body(point_type pos, point_type vel, double mass, bool stationary = false): pos(pos*natural_units::unit_l), vel(vel*natural_units::unit_v), mass(mass*natural_units::unit_m), stationary(stationary){}
	bool stationary;
	void foo() {
		using namespace natural_units;
		using boost::units::pow;
		velocity a = unit_v;
		
	}
};

void predict(std::vector<Body> bodies, double t, int active_bodies=-1, bool one_over_r=false);
void predict(std::vector<United_Body> bodies, quantity<natural_units::time> t, int active_bodies=-1, bool one_over_r=false);
