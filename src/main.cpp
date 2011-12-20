#include <iostream>
#include <vector>
#include <string>
#include "asteroid.hpp"
#include "entity.hpp"
#include "graphics.hpp"
#include "matrix.hpp"
#include "main.hpp"
#include "model.hpp"
#include "GL/glut.h"

using namespace std;

vector< entity* > entities;

bool keystates[256];

void update(int n) {
	// keyboard inputs
	if (keystates['k']) worldcamera.accelerateX(R_STEP);
	if (keystates['j']) worldcamera.accelerateX(-R_STEP);
	if (keystates['h']) worldcamera.accelerateY(R_STEP);
	if (keystates['l']) worldcamera.accelerateY(-R_STEP);
	if (keystates['o']) worldcamera.accelerateZ(R_STEP);
	if (keystates['p']) worldcamera.accelerateZ(-R_STEP);
	
	if (keystates['a']) worldcamera.accelerateC( (matrix<3,1>){{ {1.0,0.0,0.0} }}, M_STEP );
	if (keystates['d']) worldcamera.accelerateC( (matrix<3,1>){{ {-1.0,0.0,0.0} }}, M_STEP );
	if (keystates['f']) worldcamera.accelerateC( (matrix<3,1>){{ {0.0,1.0,0.0} }}, M_STEP );
	if (keystates['r']) worldcamera.accelerateC( (matrix<3,1>){{ {0.0,-1.0,0.0} }}, M_STEP );
	if (keystates['w']) worldcamera.accelerateC( (matrix<3,1>){{ {0.0,0.0,1.0} }}, M_STEP );
	if (keystates['s']) worldcamera.accelerateC( (matrix<3,1>){{ {0.0,0.0,-1.0} }}, M_STEP );
	
	if (keystates['b']) worldcamera.location_v = worldcamera.location_v * B_STEP;
	if (keystates['v']) worldcamera.rotation_v = slowquaternionrotation(worldcamera.rotation_v,B_STEP);
	
	vector< entity* >::iterator i;
	for (i = entities.begin(); i != entities.end(); i++) {
		(*i)->step(n);
	}
	worldcamera.step(n);
	glutPostRedisplay();
	worldcamera.rotation_v = slowquaternionrotation(worldcamera.rotation_v, 0.93);
	if (fabs(worldcamera.location_v.magnitude()) > MAX_VEL) {
		worldcamera.location_v = worldcamera.location_v.unitvector() * MAX_VEL;
	}
	glutTimerFunc(25,update,25);
}

void keyup(unsigned char key, int x, int y) {
	keystates[key] = false;
}

void keydown(unsigned char key, int x, int y) {
	keystates[key] = true;
}

int main(int argc, char* argv[]) {
	
	glutInit(&argc, argv);
	
	asteroidfactory factory(60.0,20.0,10.0,2.0);
	int i;
	for (i = 0; i < 50; i++) {
		entity* a = factory.createasteroid();
		entities.push_back(a);
	}
	
	model station("models/starship.obj");
	
	entity e;
	e.location = (matrix<3,1>){{ {0.0,0.0,0.0} }};
	e.rotation = quaternionfromaxis( (matrix<3,1>){{ {0.0,0.0,1.0} }}, 0.0);
	e.rotation_v = quaternionfromaxis( (matrix<3,1>){{ {0.0,0.0,1.0} }}, 0.0001);
	e.m = &station;
	e.scale(0.5);
	
	entities.push_back(&e);



	worldcamera.location = (matrix<3,1>){{ {0.0,0.0,-50.0} }};
	worldcamera.rotation = quaternionfromaxis( (matrix<3,1>){{ {0.0,1.0,0.0} }}, 0.0);

	graphics(argc, argv);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);

	update(25);
	glutMainLoop();
}
