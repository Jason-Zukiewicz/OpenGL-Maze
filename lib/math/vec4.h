#ifndef VEC4_MATH_H
#define VEC4_MATH_H

#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} vec4;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3;

typedef struct
{
    GLfloat x;
    GLfloat y;
} vec2;

void vec4_print(vec4 V);
void vec3_print(vec3 V);
void vec2_print(vec2 V);

void vec4_round(vec4 *v);

vec4 vec4_SVA(float S, vec4 V);
vec4 vec4_SVM(float S, vec4 V);
vec4 vec4_VVA(vec4 V, vec4 U);
vec4 vec4_VVS(vec4 V, vec4 U);
GLfloat vec4_Mag(vec4 V);
vec4 vec4_Norm(vec4 V);
GLfloat vec4_Dot(vec4 V, vec4 U);
vec4 vec4_Cross(vec4 V, vec4 U);
vec4 vec4_Prod(vec4 V, vec4 U);

#endif /* VEC4_MATH_H */
