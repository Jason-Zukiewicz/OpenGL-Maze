#include "util.h"
#include <stdlib.h>
#include <math.h>

/*
 * Output:
 *   vec4 color
 */
vec4 getRandomColor()
{
    // Generate random values for red, green, blue, and alpha components
    float r = (float)rand() / RAND_MAX; // Random value between 0 and 1 for red
    float g = (float)rand() / RAND_MAX; // Random value between 0 and 1 for green
    float b = (float)rand() / RAND_MAX; // Random value between 0 and 1 for blue
    float a = 1.0;                      // Alpha component set to 1

    // Create a vec4 color vector
    vec4 color = {r, g, b, a};

    return color;
}

/*
 * Input:
 *   int num_verts: the number of vertexts and size of memory
 *   int verts_per_color: this is to have a certain number of vertex, in order, the same color
 * Output:
 *   vec4* vertex_colors: the array of colors
 */
vec4 *makeColors(int num_verts, int verts_per_color)
{
    vec4 *colors = (vec4 *)malloc(num_verts * sizeof(vec4));
    for (int i = 0; i < num_verts; i += verts_per_color)
    {
        vec4 temp = getRandomColor();
        for (int j = 0; j < verts_per_color; j++)
        {
            colors[i + j] = temp;
        }
    }
    return colors;
}

/*
 * Input:
 *   vec4* verts: we will do the multiplaction in place
 *   int num_verts: the number of vertexs and size of memory
 *
 */
void viewBottom(vec4 *verts, int num_verts)
{
    mat4 view = {{1, 0, 0, 0}, {0, 0, -1, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}};
    for (int i = 0; i < num_verts; i++)
        verts[i] = mat4_MVM(view, verts[i]);
}

/*
 * Input:
 *   vec4* verts: we will do the multiplaction in place
 *   int num_verts: the number of vertexs and size of memory
 *
 */
void viewTilt(vec4 *verts, int num_verts)
{
    mat4 view = {{1, 0, 0, 0}, {0, 0.71, -0.71, 0}, {0, 0.71, 0.71, 0}, {0, 0, 0, 1}};
    for (int i = 0; i < num_verts; i++)
        verts[i] = mat4_MVM(view, verts[i]);
}

mat4 mat4_translate(float x, float y, float z)
{
    mat4 t = (mat4){{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {x, y, z, 1}};
    return t;
}

mat4 mat4_scale(float x, float y, float z)
{
    mat4 s = (mat4){{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}};
    return s;
}

mat4 mat4_rotateX(float theta)
{
    theta = theta * M_PI / 180.0; // Convert To radians
    mat4 r = (mat4){{1, 0, 0, 0},
                    {0, cos(theta), sin(theta), 0},
                    {0, -sin(theta), cos(theta), 0},
                    {0, 0, 0, 1}};
    return r;
}

mat4 mat4_rotateY(float theta)
{
    theta = theta * M_PI / 180.0; // Convert To radians
    mat4 r = (mat4){{cos(theta), 0, -sin(theta), 0},
                    {0, 1, 0, 0},
                    {sin(theta), 0, cos(theta), 0},
                    {0, 0, 0, 1}};
    return r;
}

mat4 mat4_rotateZ(float theta)
{
    mat4 r = (mat4){{cos(theta), sin(theta), 0, 0},
                    {-sin(theta), cos(theta), 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}};
    return r;
}

vec4 vec4_rotate(vec4 origin, vec4 point, float theta)
{
    vec4 trans = mat4_MVM(mat4_translate(-origin.x, -origin.y, -origin.z), point);
    trans = mat4_MVM(mat4_rotateY(theta), trans);
    point = mat4_MVM(mat4_translate(origin.x, origin.y, origin.z), trans);
    return point;
}
