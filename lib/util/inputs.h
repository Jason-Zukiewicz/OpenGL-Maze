#ifndef INPUTS_H
#define INPUTS_H

#include "../math/vec4.h"
#include "../maze/maze.h"
#include "view.h"
#include "util.h"
#include <math.h>
#include <stdbool.h>
#include "GL/glut.h"

void keyboard(unsigned char key, int mousex, int mousey);
void special(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void calcMove();
void passive(int x, int y);

#endif