#pragma once
#include "point.h"
template<typename T>
using Vector3 = point<T, 3>;

template<typename T>
auto make_vector(double x, double y, double z, T t) {
	return Vector3<decltype(x*t)>{x*t, y*t, z*t};
}
