#pragma once
#include <boost/operators.hpp>
#include <boost/units/pow.hpp>
#include <ostream>

template< class T , size_t Dim = 3>
class point {
public:

	const static size_t dim = Dim;
	typedef T value_type;
	typedef point< value_type , dim > point_type;

	point( void )
	{
			for( size_t i=0 ; i<dim ; ++i ) m_val[i] = T{};
	}

	point( value_type val )
	{
			for( size_t i=0 ; i<dim ; ++i ) m_val[i] = val;
	}

	point(value_type x , value_type y , value_type z)
	{
			if( dim > 0 ) m_val[0] = x;
			if( dim > 1 ) m_val[1] = y;
			if( dim > 2 ) m_val[2] = z;
	}

	T operator[]( size_t i ) const { return m_val[i]; }
	T& operator[]( size_t i ) { return m_val[i]; }

	template<class U>
	point_type& operator+=(const point<U, Dim> p)
	{
			for(size_t i=0; i<dim; ++i)
					m_val[i] += p[i];
			return *this;
	}

	template<class U>
	point_type& operator-=(const point<U, Dim> p)
	{
			for(size_t i=0; i<dim; ++i)
					m_val[i] -= p[i];
			return *this;
	}

	template<class U>
	point_type& operator+=(const U& val)
	{
			for(size_t i=0; i<dim; ++i)
					m_val[i] += val;
			return *this;
	}

	template<class U>
	point_type& operator-=(const U& val)
	{
			for(size_t i=0; i<dim; ++i)
					m_val[i] -= val;
			return *this;
	}

	template<class U>
	point_type& operator*=(const U& val)
	{
			for(size_t i=0; i<dim; ++i)
					m_val[i] *= val;
			return *this;
	}

	template<class U>
	point_type& operator/=(const U& val)
	{
			for(size_t i=0; i<dim; ++i)
					m_val[i] /= val;
			return *this;
	}
	
	auto sum() {
		auto tmp = value_type{};
		for(size_t i=0; i<dim; ++i)
			tmp += m_val[i];
		return tmp;
	}

private:

	T m_val[dim];
};
	

template<class T, size_t Dim>
point<T, Dim> operator-(const point<T, Dim> &p) {
    point<T, Dim> tmp;
    for(size_t i=0 ; i<Dim ; ++i) tmp[i] = -p[i];
    return tmp;
}

template<class T, class U, size_t Dim>
auto operator+(const point<T, Dim> &p, const point<U, Dim> &u) {
    point<decltype(p[0]+u[0]), Dim> tmp;
    for(size_t i=0 ; i<Dim ; ++i) tmp[i] = p[i] - u[i];
    return tmp;
}

template<class T, class U, size_t Dim>
auto operator-(const point<T, Dim> &p, const point<U, Dim> &u) {
    return p + (-u);
}

template<class T, class U, size_t Dim>
auto operator*(const point<T, Dim> &p, const point<U, Dim> &u) {
    point<decltype(p[0]*u[0]), Dim> tmp;
    for(size_t i=0 ; i<Dim ; ++i) tmp[i] = p[i]*u[i];
    return tmp;
}

template<class T, class U, size_t Dim>
auto operator/(const point<T, Dim> &p, const point<U, Dim> &u) {
    point<decltype(p[0]/u[0]), Dim> tmp;
    for(size_t i=0 ; i<Dim ; ++i) tmp[i] = p[i]/u[i];
    return tmp;
}

template<class T, class U, size_t Dim>
auto operator*(const point<T, Dim> &p, const U &u) {
    point<decltype(p[0]*u), Dim> tmp;
    for(size_t i=0 ; i<Dim ; ++i) tmp[i] = p[i]*u;
    return tmp;
}

template<class T, class U, size_t Dim>
auto operator/(const point<T, Dim> &p, const U &u) {
    point<decltype(p[0]/u), Dim> tmp;
    for(size_t i=0 ; i<Dim ; ++i) tmp[i] = p[i]/u;
    return tmp;
}

template<class T, class U, size_t Dim>
auto scalar_prod(const point<T, Dim> &p, const point<U, Dim> &u) {
    return (p*u).sum();
}

template<class T, size_t Dim>
auto norm(const point<T, Dim> &p) {
    return scalar_prod(p, p);
}

template<class T, size_t Dim>
auto abs(const point<T, Dim> &p) {
    return boost::units::root(norm(p));
}

template<class T, size_t Dim>
std::ostream& operator<<(std::ostream &out, const point<T, Dim> &p) {
		if(Dim > 0) out << p[0];
		for(size_t i=1; i<Dim; ++i) out << " " << p[i];
		return out;
}
