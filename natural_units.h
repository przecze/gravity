#pragma once
#include<boost/units/unit.hpp>
#include<boost/units/base_unit.hpp>
#include<boost/units/make_system.hpp>
#include<boost/units/quantity.hpp>
#include<boost/units/physical_dimensions.hpp>
#include<boost/units/static_constant.hpp>
#include <boost/units/quantity.hpp>
#include<boost/units/systems/si.hpp>

using boost::units::quantity;
namespace natural_units {
using namespace boost::units;

using mu_dimension =  derived_dimension<length_base_dimension,3,
																				time_base_dimension,-2>::type;
struct length_base_unit : base_unit<length_base_unit, length_dimension, 1> { };
struct mass_base_unit : base_unit<mass_base_unit, mass_dimension, 2> { };
struct mu_base_unit : base_unit<mu_base_unit, mu_dimension, 3>{ };

using natural_system = make_system<
    length_base_unit,
    mass_base_unit,
    mu_base_unit>::type;

using dimensionless_unit=  unit<dimensionless_type,natural_system>;

using	length_unit   =	unit<length_dimension,natural_system>;
using	mass_unit     =	unit<mass_dimension,natural_system>;
using	time_unit     =	unit<time_dimension,natural_system>;

using	energy_unit   =	unit<energy_dimension,natural_system>;
using	velocity_unit =	unit<velocity_dimension,natural_system>;
using	acceleration_unit =	unit<acceleration_dimension,natural_system>;
using	momentum_unit =	unit<momentum_dimension,natural_system>;
using plane_angle_unit = unit<plane_angle_dimension,natural_system>;

BOOST_UNITS_STATIC_CONSTANT(unit_l, length_unit);
BOOST_UNITS_STATIC_CONSTANT(unit_m, mass_unit);
BOOST_UNITS_STATIC_CONSTANT(unit_v, velocity_unit);
BOOST_UNITS_STATIC_CONSTANT(unit_t, time_unit);
BOOST_UNITS_STATIC_CONSTANT(unit_e, energy_unit);

using Length       = quantity<length_unit>;
using Velocity     = quantity<velocity_unit>;
using Acceleration = quantity<acceleration_unit>;
using Time         = quantity<time_unit>;
using Mass         = quantity<mass_unit>;
using Energy       = quantity<energy_unit>;
using Dimensionless= quantity<dimensionless_unit>;
using Radians      = quantity<plane_angle_unit>;

using mu_unit = unit<mu_dimension, natural_system>;
BOOST_UNITS_STATIC_CONSTANT(mu, mu_unit);

using si_mu_unit = unit<mu_dimension, si::system>;
}
BOOST_UNITS_DEFINE_CONVERSION_FACTOR(natural_units::mu_base_unit, natural_units::si_mu_unit, long long int, 3.986004419e14);
BOOST_UNITS_DEFINE_CONVERSION_FACTOR(natural_units::length_base_unit, boost::units::si::meter_base_unit, long long int, 6.3781e6);
BOOST_UNITS_DEFINE_CONVERSION_FACTOR(natural_units::mass_base_unit, boost::units::si::kilogram_base_unit, long long int, 1.);
