#include<memory>
#include<iostream>
#include "Model.h"
#include "Orbit.h"
#include "CentralGravity.h"
#include "natural_units.h"
#include<boost/units/systems/si/io.hpp>
#include<boost/units/systems/si/prefixes.hpp>

	
template<class T>
std::ostream& operator<<(std::ostream& ost, const Vector3<natural_units::quantity<T>>& v) {
	for(auto i = 0; i<3; ++i) {
		ost<<boost::units::engineering_prefix<<make_si(v[i])<<" ";
	}
	return ost;
}


void print_cartesian(const Body::state_type& t) {
	std::cout<<"Q: "<<t.first<<"\nV: "<<t.second<<std::endl;
}

void print_kepler(const Body::state_type& t) {
	std::cout<<"Q: "<<t.first<<"\nV: "<<t.second<<std::endl;
}

void print_prediction(const Model::Prediction& prediction) {
  std::cout<<"T = "<<make_si(prediction.time)<<std::endl;
  print_cartesian(prediction.state);
  print_kepler(prediction.state);
}

int main(int argc, char *argv[]) {
	using namespace natural_units;
	using namespace boost::units;
	auto model = Model{};
	model.add_effect(std::make_shared<CentralGravity>());
	auto b = Body{
		make_vector(1.,0.,0.,1.*unit_l + make_natural(408000.*si::meter)),
		make_vector(0.,7.66,0.,1.0*si::kilo*si::meter_per_second)
	};
	print_prediction(Model::Prediction(std::make_pair(b.pos, b.vel), 0*unit_t));

	auto pred = model.predict(b, 1.*unit_t, .1*unit_t);
	auto passed_time = Time{0.*unit_t};
	for(int i = 0; i < pred.size()-1; ++i) {
		passed_time +=.1*unit_t;
		if((pred[i].state.first[0]*pred[i+1].state.first[0]).value()<0) {
			break;
		}
	}
	std::for_each(pred.begin(), pred.end(), print_prediction);
}
