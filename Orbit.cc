#include "Orbit.h"

#include<boost/units/systems/si/plane_angle.hpp>
#include<boost/geometry/arithmetic/cross_product.hpp>
#include<boost/mpl/assert.hpp>
#include<boost/units/cmath.hpp>

Orbit Orbit::get_orbit(Body body) {
  return Orbit::get_orbit(std::make_pair(body.pos, body.vel));
}

Orbit Orbit::get_orbit(Body::state_type state) {
	auto orbit = Orbit{};
	using boost::geometry::cross_product;
	using boost::units::static_rational;
	using boost::units::pow;
	using boost::units::sqrt;
	using boost::units::atan2;
	using natural_units::mu;

	const auto v2 = norm(state.second);
	const auto v  = sqrt(v2);

	const auto r_vec = state.first;
	const auto r2 = norm(r_vec);
	const auto r  = sqrt(r2);

	const auto h_vec = cross_product<decltype(state.first*state.second)>(state.first, state.second);
	const auto h2 = norm(h_vec);
	const auto h  = sqrt(h2);

	const auto a = 1./(2./r - v2/mu);

	const auto e = pow<static_rational<1,2>>(-(h2/mu/a - 1.));

	const auto lan = atan2(- h_vec.m_val[0],h_vec.m_val[1]);

	const auto i = atan2(h_vec.m_val[0],h_vec.m_val[2]*sin(lan));

	const auto w = atan2(1.*h*v,h2/r-1.*mu);

	const auto u = atan2(r_vec.m_val[2]/sin(i),
												r_vec.m_val[0]*cos(lan) + r_vec.m_val[1]*sin(lan));

	const auto omega = u - w;

	orbit.longitude_ascending_node = lan;
	orbit.inclination = i;
	orbit.semimajor_axis = a;
	orbit.eccentricity = e;
	orbit.true_anomaly = w;
	orbit.argument_of_periapsis = omega;
	return orbit;
}
