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


mat4 look_at(vec4 eyePoint, vec4 atPoint, vec4 upVec)
{
    vec4 forward, right, up, w;

    // Calculate the forward vector
    forward.x = atPoint.x - eyePoint.x;
    forward.y = atPoint.y - eyePoint.y;
    forward.z = atPoint.z - eyePoint.z;
    forward.w = 0.0;
    forward = vec4_Norm(forward);

    right.x = upVec.y * forward.z - upVec.z * forward.y;
    right.y = upVec.z * forward.x - upVec.x * forward.z;
    right.z = upVec.x * forward.y - upVec.y * forward.x;
    right.w = 0.0;
    right = vec4_Norm(right);

    // Calculate the up vector
    up.x = forward.y * right.z - forward.z * right.y;
    up.y = forward.z * right.x - forward.x * right.z;
    up.z = forward.x * right.y - forward.y * right.x;
    up.w = 0.0;

    // Calculate the translation (w) vector
    w.x = -vec4_Dot(eyePoint, right);
    w.y = -vec4_Dot(eyePoint, up);
    w.z = -vec4_Dot(eyePoint, forward);
    w.w = 1.0;

    mat4 viewMatrix;
    viewMatrix.X = right;
    viewMatrix.Y = up;
    viewMatrix.Z = forward;
    viewMatrix.W = w;

    return viewMatrix;
}

mat4 ortho(GLfloat left, GLfloat right,
           GLfloat bottom, GLfloat top,
           GLfloat near, GLfloat far)
{
    mat4 projectionMatrix;

    projectionMatrix.X.x = 2.0 / (right - left);
    projectionMatrix.X.y = 0.0;
    projectionMatrix.X.z = 0.0;
    projectionMatrix.X.w = -(right + left) / (right - left);

    projectionMatrix.Y.x = 0.0;
    projectionMatrix.Y.y = 2.0 / (top - bottom);
    projectionMatrix.Y.z = 0.0;
    projectionMatrix.Y.w = -(top + bottom) / (top - bottom);

    projectionMatrix.Z.x = 0.0;
    projectionMatrix.Z.y = 0.0;
    projectionMatrix.Z.z = -2.0 / (far - near);
    projectionMatrix.Z.w = -(far + near) / (far - near);

    projectionMatrix.W.x = 0.0;
    projectionMatrix.W.y = 0.0;
    projectionMatrix.W.z = 0.0;
    projectionMatrix.W.w = 1.0;
    
    return projectionMatrix; 
}

mat4 frustrum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
    mat4 projectionMatrix;

    projectionMatrix.X.x = (2.0 * near) / (right - left);
    projectionMatrix.X.y = 0.0;
    projectionMatrix.X.z = (right + left) / (right - left);
    projectionMatrix.X.w = 0.0;

    projectionMatrix.Y.x = 0.0;
    projectionMatrix.Y.y = (2.0 * near) / (top - bottom);
    projectionMatrix.Y.z = (top + bottom) / (top - bottom);
    projectionMatrix.Y.w = 0.0;

    projectionMatrix.Z.x = 0.0;
    projectionMatrix.Z.y = 0.0;
    projectionMatrix.Z.z = -(far + near) / (far - near);
    projectionMatrix.Z.w = (-2.0 * far * near) / (far - near);

    projectionMatrix.W.x = 0.0;
    projectionMatrix.W.y = 0.0;
    projectionMatrix.W.z = -1.0;
    projectionMatrix.W.w = 0.0;

    return projectionMatrix;
}
