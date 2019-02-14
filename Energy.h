#include<natural_units.h>

natural_units::Energy TotalEnergy(
    Vector3<natural_units::Length> pos,
    Vector3<natural_units::Velocity> vel) {
  using namespace natural_units;
  Energy EKin = 0.5*unit_m * norm(vel);
  Energy EPot = 1.*unit_m * mu / (1.*abs(pos));
  return EKin+EPot;
}
