#include "view.h"

mat4 mat4_VrotateX(float s, float c)
{
    mat4 r = (mat4){{1, 0, 0, 0},
                    {0, c, s, 0},
                    {0, -s, c, 0},
                    {0, 0, 0, 1}};
    return r;
}

mat4 mat4_VrotateY(float s, float c)
{
    mat4 r = (mat4){{c, 0, -s, 0},
                    {0, 1, 0, 0},
                    {s, 0, c, 0},
                    {0, 0, 0, 1}};
    return r;
}

mat4 mat4_VrotateZ(float s, float c)
{
    mat4 r = (mat4){{c, s, 0, 0},
                    {-s, c, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}};
    return r;
}

/*
 * u = cross(v,n)
 */

mat4 look_at(vec4 eyePoint, vec4 atPoint, vec4 upVec)
{
    vec4 forward, right, up;

    forward = vec4_Norm(vec4_VVS(eyePoint, atPoint));
    right = vec4_Norm(vec4_Cross(upVec, forward));
    up = vec4_Norm(vec4_Cross(forward, right));

    mat4 view = {{right.x, up.x, forward.x, 0}, {right.y, up.y, forward.y, 0}, {right.z, up.z, forward.z, 0}, {0, 0, 0, 1}};
    mat4 transform = mat4_translate(-eyePoint.x, -eyePoint.y, -eyePoint.z);
    mat4 result = mat4_MMM(view, transform);
    return result;
}
/*

mat4 look_at(vec4 eyePoint, vec4 atPoint, vec4 upVec)
{
    vec4 forward, right, up, translate;

    forward = vec4_Norm(vec4_VVS(atPoint, eyePoint));
    right = vec4_Norm(vec4_Cross(forward, upVec));
    up = vec4_Cross(right, forward);
    translate = (vec4){ -eyePoint.x, -eyePoint.y, -eyePoint.z, -eyePoint.w };

    mat4 viewMatrix;

    viewMatrix.X = (vec4){right.x, up.x, -forward.x, 0.0f};
    viewMatrix.Y = (vec4){right.y, up.y, -forward.y, 0.0f};
    viewMatrix.Z = (vec4){right.z, up.z, -forward.z, 0.0f};
    viewMatrix.W = (vec4){vec4_Dot(right, translate), vec4_Dot(up, translate), vec4_Dot(forward, translate), 1.0f};

    return viewMatrix;
}
*/

/*
* Translate  --> Scale
* Translate center of mass
* Scale to new volume
* x = (right + left) / 2
* y = (top + bottom) / 2
* z = (near + far) / 2
* mat4 T = Translate by making a mat where w.x = -x, w.y = -y, w.z = -z, w.w = 1 // move center to origin so negative
* Scale mat4 S = X.x = width, Y.y = height, Z.z =depth, w.w = 1
* width = 2 / (right - left)
* height = 2 / (top - bottom)
* depth = 2 / (near - far)
* N = ST ,

*/
mat4 ortho(GLfloat left, GLfloat right,
           GLfloat bottom, GLfloat top,
           GLfloat near, GLfloat far)
{
    mat4 projectionMatrix;

    projectionMatrix.X.x = 2.0 / (right - left);
    projectionMatrix.X.y = 0.0;
    projectionMatrix.X.z = 0.0;
    projectionMatrix.X.w = 0.0;

    projectionMatrix.Y.x = 0.0;
    projectionMatrix.Y.y = 2.0 / (top - bottom);
    projectionMatrix.Y.z = 0.0;
    projectionMatrix.Y.w = 0.0;

    projectionMatrix.Z.x = 0.0;
    projectionMatrix.Z.y = 0.0;
    projectionMatrix.Z.z = 2.0 / (near - far);
    projectionMatrix.Z.w = 0.0;

    projectionMatrix.W.x = -(right + left) / (right - left);
    projectionMatrix.W.y = -(top + bottom) / (top - bottom);
    projectionMatrix.W.z = -(near + far) / (near - far);
    projectionMatrix.W.w = 1.0;

    return projectionMatrix;
}

mat4 frustrum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
    mat4 projectionMatrix;

    projectionMatrix.X.x = (-2.0 * near) / (right - left);
    projectionMatrix.X.y = 0.0;
    projectionMatrix.X.z = 0.0;
    projectionMatrix.X.w = 0.0;

    projectionMatrix.Y.x = 0.0;
    projectionMatrix.Y.y = (-2.0 * near) / (top - bottom);
    projectionMatrix.Y.z = 0.0;
    projectionMatrix.Y.w = 0.0;

    projectionMatrix.Z.x = (right + left) / (right - left);
    projectionMatrix.Z.y = (top + bottom) / (top - bottom);
    projectionMatrix.Z.z = (far + near) / (far - near);
    projectionMatrix.Z.w = -1.0;

    projectionMatrix.W.x = 0.0;
    projectionMatrix.W.y = 0.0;
    projectionMatrix.W.z = (-2.0 * far * near) / (far - near);
    projectionMatrix.W.w = 0.0;
    return projectionMatrix;
}

/*
mat4 frustrum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
    mat4 projectionMatrix;

    projectionMatrix.X.x = (-2.0 * near) / (right - left);
    projectionMatrix.X.y = 0.0;
    projectionMatrix.X.z = 0.0;
    projectionMatrix.X.w = 0.0;

    projectionMatrix.Y.x = 0.0;
    projectionMatrix.Y.y = (-2.0 * near) / (top - bottom);
    projectionMatrix.Y.z = 0.0;
    projectionMatrix.Y.w = 0.0;

    projectionMatrix.Z.x = (left + right) / (right - left);
    projectionMatrix.Z.y = (bottom + top) / (top - bottom);
    projectionMatrix.Z.z = (near + far) / (far - near);
    projectionMatrix.Z.w = -1.0;

    projectionMatrix.W.x = 0.0;
    projectionMatrix.W.y = 0.0;
    projectionMatrix.W.z = (-2 * near * far) / (far - near);
    projectionMatrix.W.w = 0.0;

    return projectionMatrix;
}
*/