#include<memory>
#include<iostream>
#include "Model.h"
#include "CentralGravity.h"
#include "natural_units.h"

	
template<class T>
std::ostream& operator<<(std::ostream& ost, const Vector3<natural_units::quantity<T>>& v) {
	for(auto i = 0; i<3; ++i) {
		ost<<boost::units::quantity_cast<double>(v[i])<<" ";
	}
	return ost;
}

void print_state(const Body::state_type& t) {
	std::cout<<"Q: "<<t.first<<"\nV: "<<t.second<<std::endl;
}

int main(int argc, char *argv[]) {
	using namespace natural_units;
	auto model = Model{};
	model.add_effect(std::make_shared<CentralGravity>(1.*unit_m));
	auto a = Body{{1.,0.,0.,},{0.,0.,1.}, 1.};
	auto pred = model.predict(a, 100.*unit_t, 1.*unit_t);
	std::for_each(pred.begin(), pred.end(), print_state);
}
