#ifndef ENTITY_H
#define ENTITY_H

//#include "graphics.hpp"
#include "matrix.hpp"
#include "model.hpp"

using namespace std;

class entity {
	public:
		entity();
		void moveW(matrix<3,1> delta);
		void accelerateW(matrix<3,1> delta);
		void rotateX(float xrmod);
		void rotateY(float yrmod);
		void rotateZ(float zrmod);
		void accelerateX(float xrmod);
		void accelerateY(float yrmod);
		void accelerateZ(float zrmod);
		void moveC(matrix<3,1> m);
		void accelerateC(matrix<3,1> d, float m);
		void step(int n);
		void scale(float s);
		float scale();
		matrix<3,1> locationmatrix();
		matrix<4,4> rotationmatrix();
		model* m;
		matrix<4,1> rotation, rotation_v;
		matrix<3,1> location, location_v;
	private:
		float scale_m;
};

#endif
