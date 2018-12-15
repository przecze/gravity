#pragma once
#include<boost/fusion/container.hpp>
#include<utility>
#include "Vector3.h"
#include "natural_units.h"
class Body {
public:
	using position_type = Vector3<natural_units::Length>;
	using velocity_type = Vector3<natural_units::Velocity>;
	using acceleration_type = Vector3<natural_units::Acceleration>;
	using state_type = boost::fusion::vector<position_type, velocity_type>;
	using deriv_type = boost::fusion::vector<velocity_type, acceleration_type>;
	Vector3<natural_units::Length> pos;
	Vector3<natural_units::Velocity> vel;
	natural_units::Mass mass;
	Body(Vector3<natural_units::Length>&& pos,
	      Vector3<natural_units::Velocity>&& vel,
				natural_units::Mass mass):
		pos(std::move(pos)), vel(std::move(vel)), mass(mass) {}
	bool stationary;
};
