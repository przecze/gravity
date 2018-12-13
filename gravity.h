#include<valarray>
#include<vector>

#include "natural_units.h"
#include "point.h"
#include<boost/units/pow.hpp>

using point_type = std::valarray<double>;
template<class T>
using Vector3 = point<T, 3>;

struct Body {
	std::valarray<double>pos;
	std::valarray<double> vel;
	double mass;
	Body(point_type pos, point_type vel, double mass, bool stationary = false): pos(pos), vel(vel), mass(mass), stationary(stationary){}
	bool stationary;
};

void predict(std::vector<Body> bodies, double t, int active_bodies=-1, bool one_over_r=false);

struct _Body {
	Vector3<natural_units::Length> pos;
	Vector3<natural_units::Velocity> vel;
	natural_units::Mass mass;
	_Body(Vector3<natural_units::Length> pos,
	      Vector3<natural_units::Velocity> vel,
				natural_units::Mass mass,
				bool stationary=false):
		pos(pos), vel(vel), mass(mass), stationary(stationary) {}
	bool stationary;
};

void predict(std::vector<Body> bodies, natural_units::Time t, int active_bodies=-1, bool one_over_r=false);
