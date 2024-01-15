#include "vec4.h"

void vec4_print(vec4 V)
{
    printf("[%0.4f, %0.4f, %0.4f, %0.4f]\n", V.x, V.y, V.z, V.w);
}

void vec3_print(vec3 V)
{
    printf("[%0.4f, %0.4f, %0.4f]\n", V.x, V.y, V.z);
}

void vec2_print(vec2 V)
{
    printf("[%0.4f, %0.4f]\n", V.x, V.y);
}

void vec4_round(vec4 *v)
{
    v->x = ceil(v->x);
    v->y = ceil(v->y);
    v->z = ceil(v->z);
    v->w = ceil(v->w);
}

vec4 vec4_SVA(float S, vec4 V)
{
    vec4 result;
    result.x = S + V.x;
    result.y = S + V.y;
    result.z = S + V.z;
    result.w = S + V.w;
    return result;
}

/*
 * Scalar Vector Multiplaction
 */
vec4 vec4_SVM(float S, vec4 V)
{
    vec4 result;
    result.x = S * V.x;
    result.y = S * V.y;
    result.z = S * V.z;
    result.w = S * V.w;
    return result;
}

/*
 * Vector Vector Addition
 */
vec4 vec4_VVA(vec4 V, vec4 U)
{
    vec4 result;
    result.x = V.x + U.x;
    result.y = V.y + U.y;
    result.z = V.z + U.z;
    result.w = V.w + U.w;
    return result;
}

/*
 * Vector Vector Subtraction
 */
vec4 vec4_VVS(vec4 V, vec4 U)
{
    vec4 result;
    result.x = V.x - U.x;
    result.y = V.y - U.y;
    result.z = V.z - U.z;
    result.w = V.w - U.w;
    return result;
}

/*
 * Input: 4x1 Vector: V
 * Output: GLfloat: R
 * Function: R = Sqrt(squares)
 */
GLfloat vec4_Mag(vec4 V)
{
    GLfloat result;
    result = sqrt(V.x * V.x + V.y * V.y + V.z * V.z + V.w * V.w);
    return result;
}

/*
 * Input: 4x1 Vector: V
 * Output: 4x1 Vector: R
 * Function: R(i) = R(i) / mag(R)
 */
vec4 vec4_Norm(vec4 V)
{
    vec4 result;
    GLfloat mag = vec4_Mag(V);
    if (mag == 0)
        return (vec4){0, 0, 0, 0};
    result.x = V.x / mag;
    result.y = V.y / mag;
    result.z = V.z / mag;
    result.w = 0;
    return result;
}

/*
 * Input: 4x1 Vector: V
 *        4x1 Vector: U
 * Output: GLfloat: R
 * Function: R += V(i)*U(i)
 */
GLfloat vec4_Dot(vec4 V, vec4 U)
{
    GLfloat result;
    result = V.x * U.x + V.y * U.y + V.z * U.z + V.w * U.w;
    return result;
}

/*
 * Input: 4x1 Vector: V
 *        4x1 Vector: U
 * Output: 4x1 Vector: R
 * Function: R(i) = V(i+1) * U(i+2) - V(i+2) * U(i+1)
 */
vec4 vec4_Cross(vec4 V, vec4 U)
{
    vec4 result;
    result.x = V.y * U.z - V.z * U.y;
    result.y = V.z * U.x - V.x * U.z;
    result.z = V.x * U.y - V.y * U.x;
    result.w = 0.0;
    return result;
}

vec4 vec4_Prod(vec4 V, vec4 U)
{
    vec4 result;
    result.x = V.x * U.x;
    result.y = V.y * U.y;
    result.z = V.z * U.z;
    result.w = V.w * U.w;
    return result;
}
