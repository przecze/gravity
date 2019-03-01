#include "configuration.h"
#include "Model.h"
#include "natural_units.h"
#include "Vector3.h"

#include<toml.hpp>

#include<boost/units/systems/si.hpp>
#include<boost/units/systems/si/prefixes.hpp>

#include<map>


namespace config {
  using namespace boost::units;
  struct VALUE_NOT_ALLOWED{};
  template<typename Dim>
  Vector3<quantity<unit<Dim, natural_units::natural_system>, double>>
  load_vector(
      const toml::Table & tab,
      std::unordered_map<std::string, quantity<unit<Dim, si::system>, double>>&& unit_multipliers
      ) {
    auto values = toml::get<std::vector<double>>(tab.at("values"));
    if(values.size() != 3) {
      auto should_fail = toml::get<int>(tab.at("values"));
    }
    auto initial_velocity_unit = toml::get<std::string>(tab.at("unit"));
    auto velocity_multiplier = unit_multipliers.find(initial_velocity_unit);
    if(velocity_multiplier == unit_multipliers.end()) {
      auto should_fail = toml::get<int>(tab.at("unit"));
    }
    return natural_units::make_vector(
      values[0],
      values[1],
      values[2],
      natural_units::make_natural(velocity_multiplier->second)
    );
  }

  Model load_config_from_file(std::string path) {
    auto model = Model{};
    auto config = toml::parse(path);
    auto velocity = load_vector<natural_units::velocity_dimension>(
        toml::get<toml::Table>(config.at("velocity")),
        {
          {"kmps", 1000.*si::meter_per_second},
          {"kmph", 100./6.*si::meter_per_second},
          {"mps", 1.*si::meter_per_second}
        }
    );
    auto position = load_vector<natural_units::length_dimension>(
        toml::get<toml::Table>(config.at("position")),
        {
          {"km", 1000.*si::meter},
          {"m", 1.*si::meter}
        }
    );
    model.set_initial_state(std::make_pair(position, velocity));
    return Model{};
  }
}
