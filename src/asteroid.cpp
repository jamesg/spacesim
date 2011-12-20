#include <cmath>
#include "asteroid.hpp"
#include "entity.hpp"

float frand() {
	return (float)((float)rand()/RAND_MAX);
}

asteroidfactory::asteroidfactory(float radius, float h_randomness, float v_randomness, float s_randomness) {
	this->radius = radius; this->h_randomness = h_randomness; this->v_randomness = v_randomness; this->s_randomness = s_randomness;
	asteroidmodel = model("models/asteroid_0.obj");
}

entity* asteroidfactory::createasteroid() {
	entity* e = new entity;
	e->rotation_v = quaternionfromaxis( (matrix<3,1>){{ {frand(),frand(),frand()} }}, frand()*0.010);
	
	matrix<3,1> p = {{ {1.0,0.0,0.0} }};
	p = rotatevectorbyquaternion(p, quaternionfromaxis( (matrix<3,1>){{ {0.0,1.0,0.0} }}, frand()*360)).unitvector()*(radius+( (frand()-0.5)*h_randomness));
	p[0][1] = (v_randomness)*(frand()-0.5);
	e->location = p;
	
	e->scale((frand()-0.5)*s_randomness+1);
	
	e->m = &asteroidmodel;
	return e;
}
