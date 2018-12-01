#include<valarray>
#include<vector>

using point_type = std::valarray<double>;
struct Body {
	point_type pos;
	point_type vel;
	double mass;
	Body(point_type pos, point_type vel, double mass): pos(pos), vel(vel), mass(mass){}
};

void predict(std::vector<Body> bodies, double t, int active_bodies=-1);