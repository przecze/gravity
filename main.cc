#include<memory>
#include<iostream>
#include "Model.h"
#include "CentralGravity.h"
#include "natural_units.h"
#include<boost/units/systems/si/io.hpp>

	
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
	using namespace boost::units;
	auto a = Length{1.*unit_l};
	auto b = quantity<si::length>{a};
	auto c = quantity<si::mass>{1.*unit_m};
	auto d = quantity<si::velocity>{1.*unit_v};
	auto muu = quantity<si_mu_unit>{1*mu};
	std::cout<<b<<std::endl;
	std::cout<<c<<std::endl;
	std::cout<<muu<<std::endl;
	//auto pred = model.predict(a, 100.*unit_t, 1.*unit_t);
	//std::for_each(pred.begin(), pred.end(), print_state);
}
