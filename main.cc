#include<memory>
#include<iostream>
#include "Model.h"
#include "CentralGravity.h"
#include "natural_units.h"
#include<boost/units/systems/si/io.hpp>
#include<boost/units/systems/si/prefixes.hpp>

	
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
	auto model = Model{};
	model.add_effect(std::make_shared<CentralGravity>());
	auto b = Body{
		make_vector(1.,0.,0.,1.*unit_l + make_natural(408000.*si::meter)),
		make_vector(0.,7.66,0.,1.0*si::kilo*si::meter_per_second)
	};
	std::cout<<b.pos[0].value()<<std::endl;
	std::cout<<quantity<si::length>{b.pos[0]}<<std::endl;
	print_state(std::make_pair(b.pos, b.vel));
	//boost::units::conversion_factor<si::time, natural_units::time_unit>;
	//boost::units::conversion_factor<si::length, natural_units::length_unit>;
	//boost::units::conversion_factor<si::velocity, natural_units::velocity_unit>;
	//auto a = Length{1.*si::meter};
	quantity<si::length> a{1.*unit_l};
	quantity<si::velocity> asdf{1.*unit_v};

	//auto pred = model.predict(b, 10.*unit_t, .1*unit_t);
	//auto pass_t = Time{0.*unit_t};
	//for(int i = 0; i < pred.size()-1; ++i) {
	//	pass_t +=.1*unit_t;
	//	if((pred[i].first[0]*pred[i+1].first[0]).value()<0) {
	//		break;
	//	}
	//}
	//std::for_each(pred.begin(), pred.end(), print_state);
}
