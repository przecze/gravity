#pragma once
#include "natural_units.h"
#include "Body.h"
#include<boost/units/systems/si/plane_angle.hpp>
#include<boost/geometry/arithmetic/cross_product.hpp>
#include<boost/mpl/assert.hpp>

struct Orbit {
	using Radians = natural_units::quantity<boost::units::si::plane_angle>;
	Radians inclination;
	natural_units::Length semimajor_axis;
	natural_units::Dimensionless eccentricity;
	static Orbit get_orbit(Body body) {
		auto orbit = Orbit{};
		using boost::geometry::cross_product;
		using boost::units::static_rational;
		using boost::units::pow;
		using natural_units::mu;
		const auto a = 1./(norm(body.vel)/mu - 2./abs(body.pos));
		const auto h = cross_product<decltype(body.pos*body.vel)>(body.pos, body.vel);
		const auto e = pow<static_rational<1,2>>(1. - norm(h)/mu/a);
		orbit.semimajor_axis = a;
		orbit.eccentricity = e;
		return orbit;
	}
};
