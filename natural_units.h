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

using dimensionless =  unit<dimensionless_type,natural_system>;

using	length=	unit<length_dimension,natural_system>        ;
using	mass  =	unit<mass_dimension,natural_system>          ;
using	time  =	unit<time_dimension,natural_system>          ;

using	area  =	unit<area_dimension,natural_system>          ;
using	energy=	unit<energy_dimension,natural_system>        ;
using	velocity =	unit<velocity_dimension,natural_system>        ;
using	momentum =	unit<momentum_dimension,natural_system>        ;

BOOST_UNITS_STATIC_CONSTANT(unit_l, length);
BOOST_UNITS_STATIC_CONSTANT(unit_m, mass);
BOOST_UNITS_STATIC_CONSTANT(unit_v, velocity);
BOOST_UNITS_STATIC_CONSTANT(unit_t, time);
BOOST_UNITS_STATIC_CONSTANT(unit_e, energy);
}
