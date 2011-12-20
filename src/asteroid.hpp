#ifndef ASTEROID_H
#define ASTEROID_H

#include "entity.hpp"
#include "model.hpp"

class asteroidfactory {
	public:
		asteroidfactory(float radius, float h_randomness, float v_randomness, float s_randomness);
		entity* createasteroid();
	private:
		float radius, h_randomness, v_randomness, s_randomness;
		model asteroidmodel;//("models/asteroid_0.obj");
};


#endif
