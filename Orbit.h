#pragma once
#include "natural_units.h"
#include "Body.h"
#include<boost/units/systems/si/plane_angle.hpp>

struct Orbit {
	natural_units::Radians inclination;
	natural_units::Radians longitude_ascending_node;
	natural_units::Radians true_anomaly;
	natural_units::Radians argument_of_periapsis;
	natural_units::Length semimajor_axis;
	natural_units::Dimensionless eccentricity;
	static Orbit get_orbit(Body body);
};
