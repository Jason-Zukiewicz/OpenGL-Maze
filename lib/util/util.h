#ifndef UTIL_H
#define UTIL_H

#include "../math/vec4.h"
#include "../math/mat4.h"

vec4 getRandomColor();
vec4 *makeColors(int num_verts, int verts_per_color);
void viewBottom(vec4 *verts, int num_verts);
void viewTilt(vec4 *verts, int num_verts);

mat4 mat4_translate(float x, float y, float z);
mat4 mat4_scale(float x, float y, float z);

mat4 mat4_rotateX(float theta);
mat4 mat4_rotateY(float theta);
mat4 mat4_rotateZ(float theta);

vec4 vec4_rotate(vec4 origin, vec4 point, float theta);

#endif