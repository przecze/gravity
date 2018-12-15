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
	using state_type = std::pair<position_type, velocity_type>;
	Vector3<natural_units::Length> pos;
	Vector3<natural_units::Velocity> vel;
	natural_units::Mass mass;
	Body(Vector3<natural_units::Length>&& pos,
	      Vector3<natural_units::Velocity>&& vel,
				natural_units::Mass mass):
		pos(std::move(pos)), vel(std::move(vel)), mass(mass) {}
	Body(Vector3<double>&& pos,
	     Vector3<double>&& vel,
			 double mass):
		pos((1.*natural_units::unit_l)*pos),
		vel((1.*natural_units::unit_v)*vel),
		mass(natural_units::unit_m*mass) {}
};
