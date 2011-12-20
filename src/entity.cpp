#include "graphics.hpp"
#include "matrix.hpp"
#include "entity.hpp"

using namespace std;

entity::entity() {
	location = location_v = (matrix<3,1>){{ {0,0,0} }};
	rotation = rotation_v = quaternionfromaxis( (matrix<3,1>){{ {0.0,0.0,1.0} }}, 0.0).unitvector();
	m = 0;
	scale_m = 1;
}

void entity::moveW(matrix<3,1> delta) {
	location = location + delta;
}

void entity::accelerateW(matrix<3,1> delta) {
	location_v = location_v + delta;
}

void entity::rotateX(float xrmod) {
	matrix<4,1> q = quaternionfromaxis( (matrix<3,1>){{ {1.0,0.0,0.0} }}, xrmod);
	rotation = multiplyquaternions(rotation,q);
}

void entity::accelerateX(float xrmod) {
	matrix<4,1> q = quaternionfromaxis( (matrix<3,1>){{ {1.0,0.0,0.0} }}, xrmod);
	rotation_v = multiplyquaternions(rotation_v,q);
}

void entity::rotateY(float yrmod) {
	matrix<4,1> q = quaternionfromaxis( (matrix<3,1>){{ {0.0,1.0,0.0} }}, yrmod);
	rotation = multiplyquaternions(rotation,q);
}

void entity::accelerateY(float yrmod) {
	matrix<4,1> q = quaternionfromaxis( (matrix<3,1>){{ {0.0,1.0,0.0} }}, yrmod);
	rotation_v = multiplyquaternions(rotation_v,q);
}

void entity::rotateZ(float zrmod) {
	matrix<4,1> q = quaternionfromaxis( (matrix<3,1>){{ {0.0,0.0,1.0} }}, zrmod);
	rotation = multiplyquaternions(rotation,q);
}

void entity::accelerateZ(float zrmod) {
	matrix<4,1> q = quaternionfromaxis( (matrix<3,1>){{ {0.0,0.0,1.0} }}, zrmod);
	rotation_v = multiplyquaternions(rotation_v,q);
}

void entity::moveC(matrix<3,1> m) {
	location = location + rotatevectorbyquaternion(m, rotation);
}

void entity::accelerateC(matrix<3,1> d, float m) {
	location_v = location_v + rotatevectorbyquaternion(d, rotation)*m;
}

void entity::step(int n) {
//	cout << n << endl;
//	n = 25;
	float m = n/1000.0f;
	//float m = 25/1000.0f;
//	cout << m << endl;
	moveW(location_v * m);
	rotation = multiplyquaternions(rotation,slowquaternionrotation(rotation_v,m));
}

matrix<3,1> entity::locationmatrix() {
	return location;
}

matrix<4,4> entity::rotationmatrix() {
	return quaterniontomatrix(rotation);
}

void entity::scale(float s) {
	scale_m *= s;
}

float entity::scale() {
	return scale_m;
}
