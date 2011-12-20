#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>

#include "entity.hpp"
#include "graphics.hpp"
#include "main.hpp"
#include "matrix.hpp"
#include "model.hpp"

using namespace std;

int screen_width=640;
int screen_height=480;

entity worldcamera;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Camera rotation
	float* multmat = worldcamera.rotationmatrix().openglmatrix();
	glMultMatrixf( (GLfloat*)multmat );
	delete multmat;
	
	// Camera translation
	glTranslatef(worldcamera.locationmatrix()[0][0], worldcamera.locationmatrix()[0][1], worldcamera.locationmatrix()[0][2]);
	
	// for each entity
	vector< entity* >::iterator k;
	for (k = entities.begin(); k != entities.end(); k++) {
		entity* i = *k;
		if (i->m == 0) continue;
		
		glPushMatrix();

		// Entity translation
		glTranslatef(-i->location[0][0],-i->location[0][1],-i->location[0][2]);
		
		// Entity rotation
		float* entitymultmat = quaterniontomatrix(i->rotation).openglmatrix();
		glMultMatrixf( (GLfloat*)entitymultmat );
		delete entitymultmat;
		
		// Entity scale
		matrix<4,4> entityscale = identitymatrix<4,4>()*i->scale();
		entityscale[3][3] = 1.0;
		float* entityscalemat = entityscale.openglmatrix();
		glMultMatrixf( (GLfloat*)entityscalemat );
		delete entityscalemat;
		
//		glColor3f(i->m->colour[0][0], i->m->colour[0][1], i->m->colour[0][2]);
		glColor3f(1.0,1.0,1.0);
		
		// for each face
		vector< vector< int > >::iterator ii;
		for (ii = i->m->faces.begin(); ii != i->m->faces.end(); ii++) {
			glBegin(GL_POLYGON);
			vector< int >::iterator iii;
			for (iii = ii->begin(); iii != ii->end(); iii++) {
				glVertex3f(i->m->vertices[*iii][0][0],i->m->vertices[*iii][0][1],i->m->vertices[*iii][0][2]);
			}
			glEnd();
		}
		glPopMatrix();
	}
	
	glFlush();
	glutSwapBuffers();
}

void resize(int width, int height) {
	screen_width = width;
	screen_height = height;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,screen_width,screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);
	glutPostRedisplay();
}

int graphics(int argc, char* argv[]) {

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_width,screen_height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Space Simulator");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	
	glClearColor(0.0, 0.0, 0.1, 0.0);
	glShadeModel(GL_SMOOTH);
	glViewport(0,0,screen_width,screen_height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

