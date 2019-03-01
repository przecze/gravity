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
  const std::unordered_map<std::string, quantity<si::velocity>> allowed_velocity_units =
  {
    {"kmps", 1000.*si::meter_per_second},
    {"kmph", 100./6.*si::meter_per_second},
    {"mps", 1.*si::meter_per_second}
  };


  Model load_config_from_file(std::string path) {
    auto model = Model{};
    auto config = toml::parse(path);
    auto velocity_tab = toml::get<toml::Table>(config.at("velocity"));
    auto initial_velocity_values = toml::get<std::vector<double>>(velocity_tab.at("values"));
    if(initial_velocity_values.size() != 3) {
      throw "Wrong size";
    }
    auto initial_velocity_unit = toml::get<std::string>(velocity_tab.at("unit"));
    auto velocity_multiplier = allowed_velocity_units.find(initial_velocity_unit);
    if(velocity_multiplier == allowed_velocity_units.end()) {
      throw "Wrong unit";
    }
    Vector3<natural_units::Velocity> initial_velocity = natural_units::make_vector(
      initial_velocity_values[0],
      initial_velocity_values[1],
      initial_velocity_values[2],
      natural_units::make_natural(velocity_multiplier->second)
    );
    return Model{};
  }
}
