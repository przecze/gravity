#pragma once
#include <boost/units/pow.hpp>
#include "natural_units.h"
#include "Vector3.h"
#include "Effect.h"

class CentralGravity: public Effect {
public:
	natural_units::Mass M;
	CentralGravity(natural_units::Mass M): M(M) {}
	Vector3<natural_units::Acceleration> calculate_acceleration(
			const Vector3<natural_units::Length>& q,
			const Vector3<natural_units::Velocity>& v,
			natural_units::Time t) {
		using namespace boost::units;
		using namespace natural_units;
		auto r3 = pow<static_rational<3,2>>(norm(q));
		return (M / r3 * pow<3>(unit_l)*pow<-1>(unit_m)*pow<-2>(unit_t)) * (-q);
	}
};
