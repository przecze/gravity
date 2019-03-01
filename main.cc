#include<memory>
#include<iostream>

#include "Model.h"
#include "Orbit.h"
#include "CentralGravity.h"
#include "natural_units.h"
#include "configuration.h"
#include "util.h"

#include<boost/units/systems/si/prefixes.hpp>

	

int main(int argc, char *argv[]) {
	using namespace natural_units;
	using namespace boost::units;
  Body::state_type state = std::make_pair(
		make_vector(1./sqrt(2.),0.,1./sqrt(2.),1.*unit_l + make_natural(408000.*si::meter)),
		make_vector(0.,-7.66,0.,1.0*si::kilo*si::meter_per_second));
	print_prediction(Model::Prediction(state, 0*unit_t));

	auto model = Model{};
	model.add_effect(std::make_shared<CentralGravity>())
       .set_initial_state(std::move(state))
       .set_end_time(5.*unit_t)
       .set_dt(.1*unit_t);
  auto model2 = config::load_config_from_file("config.toml");

	auto predictions = model.predict();

	auto passed_time = Time{0.*unit_t};
	for(int i = 1; i < predictions.size()-1; ++i) {
		passed_time +=.1*unit_t;
    print_prediction(predictions[i]);
	}
}
