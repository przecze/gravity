#pragma once
#include <boost/units/pow.hpp>
#include "natural_units.h"
#include "Vector3.h"
#include "Effect.h"

class CentralGravity: public Effect {
public:
	Vector3<natural_units::Acceleration> calculate_acceleration(
			const Vector3<natural_units::Length>& q,
			const Vector3<natural_units::Velocity>& v,
			natural_units::Time t) {
		using namespace boost::units;
		using namespace natural_units;
		auto r3 = pow<static_rational<3,2>>(norm(q));
		return (mu/r3) * (-q);
	}
};
