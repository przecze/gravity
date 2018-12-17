#pragma once
#include<boost/units/unit.hpp>
#include<boost/units/base_unit.hpp>
#include<boost/units/make_system.hpp>
#include<boost/units/quantity.hpp>
#include<boost/units/physical_dimensions.hpp>
#include<boost/units/static_constant.hpp>
#include <boost/units/quantity.hpp>

using boost::units::quantity;
namespace natural_units {
using namespace boost::units;
struct length_base_unit : base_unit<length_base_unit, length_dimension, 1> { };
struct mass_base_unit : base_unit<mass_base_unit, mass_dimension, 2> { };
struct time_base_unit : base_unit<time_base_unit, time_dimension, 3> { };

using natural_system = make_system<
    length_base_unit,
    mass_base_unit,
    time_base_unit>::type;

using dimensionless_unit=  unit<dimensionless_type,natural_system>;

using	length_unit   =	unit<length_dimension,natural_system>;
using	mass_unit     =	unit<mass_dimension,natural_system>;
using	time_unit     =	unit<time_dimension,natural_system>;

using	energy_unit   =	unit<energy_dimension,natural_system>;
using	velocity_unit =	unit<velocity_dimension,natural_system>;
using	acceleration_unit =	unit<acceleration_dimension,natural_system>;
using	momentum_unit =	unit<momentum_dimension,natural_system>;

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

using G_dimension =  derived_dimension<mass_base_dimension,-1,
																			length_base_dimension,3,
																			time_base_dimension,-2>::type;
using G_unit = unit<G_dimension, natural_system>;
BOOST_UNITS_STATIC_CONSTANT(G, G_unit);
}
