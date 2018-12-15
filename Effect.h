#pragma once
#include "natural_units.h"
#include "Vector3.h"

class Effect {
public:
	virtual ~Effect() = default;
	virtual Vector3<natural_units::Acceleration> calculate_acceleration(
			const Vector3<natural_units::Length>& q,
			const Vector3<natural_units::Velocity>& v,
			natural_units::Time t) = 0;
};
