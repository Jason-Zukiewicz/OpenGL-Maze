#ifndef MAT4_MATH_H
#define MAT4_MATH_H

#include "vec4.h"

typedef struct {
    vec4 X;
    vec4 Y;
    vec4 Z;
    vec4 W;
} mat4;


typedef struct {
    vec3 X;
    vec3 Y;
    vec3 Z;
} mat3;



void mat4_print(mat4 M);
void mat3_print(mat3 );

mat4 mat4_SMM(float S, mat4 M);
mat4 mat4_MMA(mat4 M, mat4 N);
mat4 mat4_MMS(mat4 M, mat4 N);
mat4 mat4_MMM(mat4 M, mat4 N);
vec4 mat4_MVM(mat4 M, vec4 V);

mat4 mat4_inverse(mat4 M);
mat4 mat4_minor(mat4 M);
mat4 mat4_cofactor(mat4 M);
mat4 mat4_transpose(mat4 M);

GLfloat mat4_determinant(mat4 M, mat4 N);
GLfloat mat3_determinant(mat3 M);

mat4 mat4_identity();


#endif /* MAT4_MATH_H */
