#pragma once
#include<memory>
#include<utility>
#include<vector>
#include "natural_units.h"
#include "Effect.h"
#include "Body.h"
#include "Vector3.h"
class Model {
public:
  struct Prediction {
    Body::state_type state;
    natural_units::Time time;
    Prediction(Body::state_type state, natural_units::Time time)
      : state(state), time(time) {}
  };
	virtual ~Model() = default;
	void operator()(const Vector3<natural_units::Length>& q,
									const Vector3<natural_units::Velocity>& v,
									Vector3<natural_units::Acceleration> &dvdt,
									natural_units::Time t);

	std::vector<Prediction> predict();

	Model& add_effect(std::shared_ptr<Effect>&& effect) {
		effects.push_back(std::move(effect));
    return *this;
	}
  Model& set_initial_state(Body::state_type&& state) {
    initial_state = state;
    return *this;
  }
  Model& set_initial_state(const Body::state_type& state) {
    initial_state = state;
    return *this;
  }
  Model& set_dt(natural_units::Time a_dt) { dt = a_dt; return *this; }
  Model& set_end_time(natural_units::Time time) { end_time = time; return *this; }
private:
  Body::state_type initial_state;
  natural_units::Time end_time;
  natural_units::Time dt;
	std::vector<std::shared_ptr<Effect>> effects;
};
