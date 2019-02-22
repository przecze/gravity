#pragma once
#include<iostream>

#include "natural_units.h"
#include "Energy.h"

#include<boost/units/systems/si/io.hpp>

template<class T>
std::ostream& operator<<(std::ostream& ost, const Vector3<natural_units::quantity<T>>& v) {
	for(auto i = 0; i<3; ++i) {
		ost<<boost::units::engineering_prefix<<make_si(v[i])<<" ";
	}
	return ost;
}


void print_cartesian(const Body::state_type& t) {
	std::cout<<"Q: "<<t.first<<std::endl;
  std::cout<<"V: "<<t.second<<std::endl;
}

void print_kepler(const Body::state_type& state) {
  auto orbit = Orbit::get_orbit(state);
  std::cout
    <<" inc: "<<std::setprecision(4)<<orbit.inclination
    <<" lan: "<<std::setprecision(4)<<orbit.longitude_ascending_node
    <<" t_a: "<<std::setprecision(4)<<orbit.true_anomaly
    <<" aop: "<<std::setprecision(4)<<orbit.argument_of_periapsis
    <<" sma: "<<std::setprecision(4)<<make_si(orbit.semimajor_axis)
    <<" ecc: "<<std::setprecision(4)<<orbit.eccentricity
    <<std::endl;
}

void print_prediction(const Model::Prediction& prediction) {
  std::cout<<"T = "<<make_si(prediction.time)<<" : ";
  print_kepler(prediction.state);
}
