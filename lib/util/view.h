#ifndef VIEW_H
#define VIEW_H

#include "../math/mat4.h"
#include "util.h"
#include <math.h>
#include <stdio.h>

mat4 mat4_VrotateZ(float s, float c);
mat4 mat4_VrotateX(float s, float c);
mat4 mat4_VrotateY(float s, float c);

mat4 look_at(vec4 eyePoint, vec4 atPoint, vec4 upVec);
mat4 ortho(GLfloat left, GLfloat right,
           GLfloat bottom, GLfloat top,
           GLfloat near, GLfloat far);

mat4 frustrum(GLfloat left, GLfloat right,
              GLfloat bottom, GLfloat top,
              GLfloat near, GLfloat far);
#endif
