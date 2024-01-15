#ifndef LIGHT_H
#define LIGHT_H

#include "../math/mat4.h"
#include <stdlib.h>

/*
vec4 lig_ambient = (vec4){1, 1, 1, 1.0};
vec4 lig_diffuse = (vec4){1, 1, 1, 1.0};
vec4 lig_specular = (vec4){1, 1, 1, 1.0};
vec4 lig_position = (vec4){0, 1, 0, 1};

vec4 ref_ambient = (vec4){1, 1, 1, 1.0};
vec4 ref_diffuse = (vec4){1, 1, 1, 1.0};
vec4 ref_specular = (vec4){1, 1, 1, 1.0};
GLfloat shine = 0;

typedef struct
{
    vec4 ambi;
    vec4 diff;
    vec4 spec;
    vec4 emis;
    float shine;
} materialStruct;

materialStruct brassMaterials = {
    {0.33, 0.22, 0.03, 1.0}, // ambient
    {0.78, 0.57, 0.11, 1.0}, // diffuse
    {0.99, 0.91, 0.81, 1.0}, // specular
    {0.0, 0.0, 0.0, 1.0},    // emission
    27.8                     // shininess
};


typedef struct
{
    vec4 reflect_ambient;
    vec4 reflect_diffuse;
    vec4 reflect_specular;
    vec4 emission;
    float shininess;
} material;

*/
void makeNormal();

#endif