#ifndef MAIN_H
#define MAIN_H

#include <vector>

// slow
/*
#define R_STEP 0.0003
#define M_STEP 0.003
#define B_STEP 0.9
#define MAX_VEL 0.05
*/

// very fast acceleration
/*
#define R_STEP 0.0010
#define M_STEP 0.010
#define B_STEP 0.9
#define MAX_VEL 0.10
*/

#define R_STEP 0.06
#define M_STEP 1.00
#define B_STEP 0.9
#define MAX_VEL 8.0

void keyboard_input(unsigned char key, int x, int y);

extern vector< entity* > entities;

#endif
