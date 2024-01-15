#pragma GCC diagnostic ignored "-Wcomment"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wswitch"

#include "light.h"

/*
 * Red-Amb  Green-Amb   Blue-Amb W.x
 * Red-Def  Green-Def   Blue-Def W.x
 * Red-Spec Green-Spec  Blue-Spec W.x
 * X.w      Y.w         Z.w     w.w
 */

vec4 light_ambient = {0.1, 0.1, 0.1, 1.0};
vec4 light_diffuse = {1.0, 1.0, 1.0, 1.0};
vec4 light_specular = {1.0, 1.0, 1.0, 1.0};

vec4 light_position = {1.0, 2.0, 3.0, 1.0};

vec4 reflect_ambient = {0.2, 0.2, 0.2, 1.0};
vec4 reflect_diffuse = {1.0, 0.8, 0.0, 1.0};
vec4 reflect_specular = {1.0, 1.0, 1.0, 1.0};

typedef struct
{
    vec4 reflect_ambient;
    vec4 reflect_diffuse;
    vec4 reflect_specular;
    vec4 emission;
    float shininess;
} material;

material brassMaterials = {
    {0.33, 0.22, 0.03, 1.0}, // ambient
    {0.78, 0.57, 0.11, 1.0}, // diffuse
    {0.99, 0.91, 0.81, 1.0}, // specular
    {0.0, 0.0, 0.0, 1.0},    // emission
    27.8                     // shininess
};

extern int numVerts;
extern vec4 *norms;
extern vec4 *verts;
extern vec4 *texs;
/*
void applyLight()
{
    vec4 ambient, diffuse, specular;
    for (int i = 0; i < numVerts; i = i + 3)
    {
        vec4 p0 = verts[i];
        vec4 p1 = verts[i + 1];
        vec4 p2 = verts[i + 2];
        // Calculate normal for all three vertices, p0, p1, and p2
        // Calculate ambient, diffuse, and specular for the first vertex
        ambient = vec4_Prod(light_ambient, reflect_ambient);
        diffuse = vec4_Prod(light_diffuse, reflect_diffuse);
        specular = vec4_Prod(light_specular, reflect_specular);

        texs[i] = ambient + diffuse + specular;
        texs[i].w = 1.0;
        // Calculate ambient, diffuse, and specular for the second vertex
        texs[i + 1] = ambient + diffuse + specular;
        texs[i + 1].w = 1.0;
        // Calculate ambient, diffuse, and specular for the third vertex
        texs[i + 2] = ambient + diffuse + specular;
        texs[i + 2].w = 1.0;
    }
}
*/
// < -------------------------------------------[] ----------------------------------------------\\


void makeNormal()
{
    norms = (vec4 *)malloc(sizeof(vec4) * numVerts);

    for (int i = 0; i < numVerts; i += 3)
    {
        vec4 p0 = verts[i + 0];
        vec4 p1 = verts[i + 1];
        vec4 p2 = verts[i + 2];

        vec4 u = vec4_VVS(p1, p0);
        vec4 v = vec4_VVS(p2, p0);
        vec4 norm = vec4_Norm(vec4_Cross(u, v));

        norms[i + 0] = norm;
        norms[i + 1] = norm;
        norms[i + 2] = norm;
    }
}