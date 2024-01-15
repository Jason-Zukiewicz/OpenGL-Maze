#include "inputs.h"

#pragma GCC diagnostic ignored "-Wswitch"

extern int shapeStart;
extern int shapeLocs[];
extern int shapeSize;
extern mat4 ctm;
extern int WIDTH;
extern int HEIGHT;

extern bool isAnimating;
extern bool isTurning;
extern bool isTInvert;
extern float theta;
extern float moveSpeed;

extern vec4 eyePoint;
extern vec4 atPoint;
extern vec4 upVec;
extern vec4 model_view_matrix;
vec4 initPos, finalPos;
bool click = false;

typedef enum
{
    none,
    move_forward,
    move_backward,
    move_left,
    move_right,
    turn_left,
    turn_right,
    move_up,
    move_down,
} STATE;

extern STATE state;
extern float aFlag, dFlag, sFlag;

void keyboard(unsigned char key, int mousex, int mousey)
{
    switch (key)
    {
    case ('q'):
        break;
    case ('p'):
        printf("-------------------------------------------------------------\n");
        printf("Eye: ");
        vec4_print(eyePoint);
        printf("At:  ");
        vec4_print(atPoint);
        printf("To:  ");
        vec4_print(vec4_VVS(atPoint, eyePoint));
        break;
    case ('a'):
        if (aFlag != 0)
            aFlag = 0;
        else
            aFlag = 1;
        break;
    case ('d'):
        if (dFlag != 0)
            dFlag = 0;
        else
            dFlag = 1;
        break;
    case ('s'):
        if (sFlag != 0)
            sFlag = 0;
        else
            sFlag = 1;
        break;
    case (50): //? NUM2 - BACKWARDS
        if (!isAnimating && canMoveDirection(eyePoint, atPoint, DOWN))
        {
            vec4 temp = vec4_VVS(atPoint, eyePoint);
            vec4_print(temp);
            isAnimating = true;
            state = move_backward;
        }
        break;
    case (52): //? NUM4 - LEFT
        if (!isAnimating && canMoveDirection(eyePoint, atPoint, LEFT))
        {
            isAnimating = true;
            state = move_left;
        }
        break;
    case (54): //? NUM6 - RIGHT
        if (!isAnimating && canMoveDirection(eyePoint, atPoint, RIGHT))
        {
            isAnimating = true;
            state = move_right;
        }
        break;
    case (56): //? NUM8 - FORWARDS
        if (!isAnimating && canMoveDirection(eyePoint, atPoint, UP))
        {
            isAnimating = true;
            state = move_forward;
        }
        break;
    case (55): //? NUM7 - TURN LEFT
        if (!isAnimating)
        {
            isAnimating = true;
            state = turn_left;
        }
        break;
    case (57): //? NUM9 - TURN RIGHT
        if (!isAnimating)
        {
            isAnimating = true;
            state = turn_right;
        }
        break;

    case (53): // NUM5
        if (!isAnimating)
        {
            isAnimating = true;
            if (state == move_up)
                state = move_down;
            else
                state = move_up;
        }
        break;
    case (51): // NUM3
        break;
    case (49): // NUM1
        break;

    default:
        printf("Value: %i \n", key);
    }
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case (0): // GLUT_KEY_DOWN
        printf("DOWN WAS PRESSED\n");
        break;
    case (113):
        break;
    case (103): // Down Arrow
        break;
    case (101): // Up Arrow
        break;
    case (102): // Right Arro
        break;
    case (100): // Left Arrow
        break;
    case (117): // Alt - Away
        break;
    case (115): // ctrl - towards
        break;
    default:
        printf("Value: %i \n", key);
    }
}

void mouse(int button, int state, int x, int y)
{
    float SCALE = 0.1;
    switch (button)
    {
    case (0): // Left
        switch (state)
        {
        case (0): // Down
                  /*
                      float X = (((float)x) - (WIDTH / 2)) / (WIDTH / 2);
                      float Y = -(((float)y) - (HEIGHT / 2)) / (HEIGHT / 2);
                      float Z = fmax(sqrt(1 - X * X - Y * Y), 0);
                      initPos = (vec4){X, Y, Z, 1};
                      click = true;
                      */
            break;
        case (1): // Up
            click = false;
            break;
        }
        break;
    case (1): // Middle
        switch (state)
        {
        case (0): // Up
            printf("Middle click - Up\n");
            break;
        case (1): // Down
            printf("Middle click - Down\n");
            break;
        }
        break;
    case (2): // Right
        switch (state)
        {
        case (0): // Down
            printf("Right click - Down\n");
            break;
        case (1): // Up
            printf("Right click - Up\n");
            break;
        }
        break;
    case (3): // Scroll up
        ctm = mat4_MMM(mat4_scale(1 + SCALE, 1 + SCALE, 1 + SCALE), ctm);
        break;
    case (4): // Scroll down
        ctm = mat4_MMM(mat4_scale(1 - SCALE, 1 - SCALE, 1 - SCALE), ctm);
        break;
    }
}

void calcMove()
{
    //! Calcs
    vec4 v = (vec4)vec4_Cross(initPos, finalPos);
    v = vec4_Norm(v);
    float d = sqrt(v.y * v.y + v.z * v.z);
    // float theta = acos(vec4_Dot(initPos, finalPos) / (vec4_Mag(initPos) * vec4_Mag(finalPos)));

    float cosTheta = vec4_Dot(initPos, finalPos) / (vec4_Mag(initPos) * vec4_Mag(finalPos));
    float sinTheta = sqrt(1 - cosTheta * cosTheta);

    //! ROTATE
    if (d > 0)
        ctm = mat4_MMM(mat4_VrotateX(v.y / d, v.z / d), ctm);

    ctm = mat4_MMM(mat4_transpose(mat4_VrotateY(v.x, d)), ctm);
    // ctm = mat4_MMM(mat4_rotateZ(theta), ctm);
    ctm = mat4_MMM(mat4_transpose(mat4_VrotateZ(-sinTheta, cosTheta)), ctm);
    ctm = mat4_MMM(mat4_VrotateY(v.x, d), ctm);

    if (d > 0)
        ctm = mat4_MMM(mat4_transpose(mat4_VrotateX(v.y / d, v.z / d)), ctm);

    glutPostRedisplay();
}

void passive(int x, int y)
{
    if (click)
    {
        float X = (((float)x) - (WIDTH / 2)) / (WIDTH / 2);
        float Y = -(((float)y) - (HEIGHT / 2)) / (HEIGHT / 2);
        float Z = fmax(sqrt(1 - X * X - Y * Y), 0);

        if (-1 <= X && X <= 1)
            if (-1 <= Y && Y <= 1)
                if (0 <= Z && Z <= 1)
                {
                    finalPos = (vec4){X, Y, Z, 1};
                    calcMove();
                    initPos = finalPos;
                }
    }
}