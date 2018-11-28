/* Boost libs/numeric/odeint/examples/solar_system.cpp

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Solar system example for Hamiltonian stepper

 Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#include <iostream>
#include <boost/array.hpp>

#include "point_type.hpp"

#include "scenario.h"
//[ container_type_definition
// we simulate 5 planets and the sun

typedef point< double , 3 > point_type;
typedef boost::array< point_type , N_BODIES > container_type;
typedef boost::array< double , N_BODIES > mass_type;
//]
mass_type mass;

//[ coordinate_function
const double gravitational_constant = 1.;

//[ momentum_function
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

}
