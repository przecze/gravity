#include <boost/array.hpp>

#include "point_type.hpp"

#include "scenario.h"
#include "common.h"

typedef point< double , 3 > point_type;
typedef boost::array< point_type , N_BODIES > container_type;
typedef boost::array< double , N_BODIES > mass_type;
mass_type mass;

const double gravitational_constant = 1.;

struct solar_system_momentum
{
    const mass_type &m_masses;

    solar_system_momentum( const mass_type &masses ) : m_masses( masses ) { }

    void operator()( const container_type &q , container_type &dpdt ) const
    {
        for( size_t i=0 ; i<N_ACTIVE_BODIES ; ++i )
        {
            for( size_t j=0 ; j<N_BODIES ; ++j )
            {
                point_type diff = q[j] - q[i];
                double d = abs( diff );
                diff *= ( gravitational_constant * m_masses[i] / d / d / d );
                dpdt[j] -= diff;

            }
        }
    }
};

int main() {
	container_type a;
	for(int i=0; i<N_BODIES; ++i) {
		mass[i] = 1.;
		a[i] = point_type(i, i, i);
	}
	container_type b;
	solar_system_momentum ssm(mass);
	for(int i=0; i<EVALUATION_COUNT; ++i) {
  	ssm(a, b);
	}
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[i][3]);
	}
	std::cout<<std::endl;
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[i][4]);
	}
	std::cout<<std::endl;
	for(int i=0; i<TO_PRINT+N_ACTIVE_BODIES; ++i) {
		print(b[i][5]);
	}
	std::cout<<std::endl;

}
