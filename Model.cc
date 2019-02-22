#include "Model.h"
#include<boost/numeric/odeint.hpp>

void Model::operator()(const Vector3<natural_units::Length>& q,
                const Vector3<natural_units::Velocity>& v,
                Vector3<natural_units::Acceleration> &dvdt,
                natural_units::Time t) {
		dvdt*=0.;
		for(auto &effect: effects) {
			dvdt += effect->calculate_acceleration(q, v, t);
		}
}
std::vector<Model::Prediction> Model::predict(natural_units::Time t, natural_units::Time dt) {
  std::vector<Prediction> predictions;
  using namespace boost::numeric::odeint;
  using namespace natural_units;
  auto current_t = .0*unit_t;
  auto stepper = velocity_verlet<
    Body::position_type,
    Body::velocity_type,
    double,
    Body::acceleration_type,
    Time,
    decltype(unit_t*unit_t*1.),
    vector_space_algebra
    >{};
  auto state = initial_state;
  while(current_t<t) {
    stepper.do_step(
            *this,
            std::make_pair(std::ref(state.first), std::ref(state.second)),
            t, dt);
    current_t += dt;
    predictions.emplace_back(state, current_t);
  }
  return predictions;
}
