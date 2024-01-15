#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wcomment"

// this is a test
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#endif

#include "../lib/util/initShader.h"
#include "../lib/util/inputs.h"
#include "../lib/maze/maze.h"
#include "../lib/light/light.h"
#include <unistd.h>

#define BUFFER_OFFSET(offset) ((GLvoid *)(offset))

//<----------------------------------- [ VARIABLES ]  ----------------------------------->//

//* DISPLAY VARIABLES *//
int WIDTH = 1024;
int HEIGHT = 1024;

//* FRUSTRUM *//
GLuint model_loc;
GLuint proj_loc;
mat4 model_view_matrix = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 projection_matrix = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

//* Shape Controls *//
vec4 *verts;
vec4 *colors;
vec2 *texs;
vec4 *norms;
int numVerts = 0;

//* Texture *//
char *texture_loc = "../textures/coin.raw";
int texWidth = 1600;
int texHeight = 1200;

//* View Controls *//
GLuint ctm_loc;
mat4 ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

//* Animnation *//
vec4 step, to, rotate;
int curStep = 0;
int const maxSteps = 1000;
bool isAnimating = false;

float theta = 1.0 / (float)maxSteps * 90;

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
STATE state;

vec4 eyePoint = {0, 0.5, 1, 1};
vec4 atPoint = {1, 0.5, 1, 1};
vec4 upVec = {0, 5, 0, 0};
vec4 temp1, eyeDelta, upDelta;

extern int coinStart;

//* Light  *//
GLuint light_position_loc;
vec4 lightPoint;

GLuint aFlag_loc, dFlag_loc, sFlag_loc;
float aFlag = 1;
float dFlag = 1;
float sFlag = 1;

GLuint aFactor_loc;
float aFactor = 0.2f;
//<----------------------------------- [ FUNCTIONS ]  ----------------------------------->//

void init()
{
    // Use the size of the dynamically allocated arrays
    GLsizei vertexDataSize = numVerts * sizeof(vec4);
    GLsizei colorDataSize = vertexDataSize;
    GLsizei texDataSize = numVerts * sizeof(vec2);

    GLubyte my_texels[texWidth][texHeight][3];

    FILE *fp = fopen(texture_loc, "r");
    if (!fp)
        printf("[ERROR] COULD NOT LOAD TEXTURE \n");
    fread(my_texels, texWidth * texHeight * 3, 1, fp);
    fclose(fp);

    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint mytex[1];
    glGenTextures(1, mytex);
    glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(vec4) + sizeof(vec2)) * numVerts, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * numVerts, verts);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * numVerts, sizeof(vec2) * numVerts, texs);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(vec4) * numVerts));
    GLuint texture_location = glGetUniformLocation(program, "texture");
    glUniform1i(texture_location, 0);

    ctm_loc = glGetUniformLocation(program, "ctm");
    model_loc = glGetUniformLocation(program, "model_view_matrix");
    proj_loc = glGetUniformLocation(program, "projection_matrix");

    //? LIGHT V2
    light_position_loc = glGetUniformLocation(program, "light_position");

    aFlag_loc = glGetUniformLocation(program, "aFlag");
    dFlag_loc = glGetUniformLocation(program, "dFlag");
    sFlag_loc = glGetUniformLocation(program, "sFlag");

    aFactor_loc = glGetUniformLocation(program, "aFactor");
    glUniform1f(aFactor_loc, aFactor);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glUniformMatrix4fv(ctm_loc, 1, GL_FALSE, (GLfloat *)&ctm);
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (GLfloat *)&model_view_matrix);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (GLfloat *)&projection_matrix);

    //? Light
    glUniform4fv(light_position_loc, 1, (GLfloat *)&lightPoint);
    glUniform1f(aFlag_loc, aFlag);
    glUniform1f(dFlag_loc, dFlag);
    glUniform1f(sFlag_loc, sFlag);

    glDrawArrays(GL_TRIANGLES, 0, numVerts);
    glutSwapBuffers();
}
// < ---------------------------------------- [IDLE] -------------------------------------- >\\


/*
 * NOTES about EYE and At
 * Changeing Z changes distance always
 * Changes X will move left - RIGHT ALWAYS
 */

void idle(void)
{
    if (isAnimating)
    {
        if (curStep >= maxSteps)
        {
            isAnimating = false;
            curStep = 0;

            eyePoint.x = round(eyePoint.x);
            eyePoint.y = round(eyePoint.y / 0.5) * 0.5;
            eyePoint.z = round(eyePoint.z);

            atPoint.x = round(atPoint.x);
            atPoint.y = round(atPoint.y / 0.5) * 0.5;
            atPoint.z = round(atPoint.z);

            if (state == move_up)
            {

                aFactor = 1.0;
                glUniform1f(aFactor_loc, aFactor);
            }
            else if (state == move_down)
            {
                aFactor = 0.2;
                glUniform1f(aFactor_loc, aFactor);
            }
        }
        else
        {
            if (curStep == 0)
            {
                if (state == move_left || state == move_right)
                {
                    to = vec4_VVS(atPoint, eyePoint);
                    to = mat4_MVM(mat4_rotateY(-90), to);
                    step = vec4_SVM(1.0 / (float)maxSteps, to);
                }
                else if (state != move_down)
                {
                    to = vec4_VVS(atPoint, eyePoint);
                    step = vec4_SVM(1.0 / (float)maxSteps, to);
                }
                if (state == move_up)
                {

                    eyeDelta = vec4_SVM(1.0 / (float)maxSteps, upVec);
                    upDelta = vec4_VVS(to, upVec);
                    upDelta = vec4_SVM(1.0 / (float)maxSteps, upDelta);
                }
            }

            switch (state)
            {
            case (move_forward):
                eyePoint = vec4_VVA(eyePoint, step);
                atPoint = vec4_VVA(atPoint, step);
                break;
            case (move_backward):
                eyePoint = vec4_VVS(eyePoint, step);
                atPoint = vec4_VVS(atPoint, step);
                break;
            case (move_left):
                eyePoint = vec4_VVS(eyePoint, step);
                atPoint = vec4_VVS(atPoint, step);
                break;
            case (move_right):
                eyePoint = vec4_VVA(eyePoint, step);
                atPoint = vec4_VVA(atPoint, step);
                break;
            case (turn_left):
                step = mat4_MVM(mat4_translate(-eyePoint.x, -eyePoint.y, -eyePoint.z), atPoint);
                step = mat4_MVM(mat4_rotateY(90.0 / maxSteps), step);
                atPoint = mat4_MVM(mat4_translate(eyePoint.x, eyePoint.y, eyePoint.z), step);
                break;
            case (turn_right):
                step = mat4_MVM(mat4_translate(-eyePoint.x, -eyePoint.y, -eyePoint.z), atPoint);
                step = mat4_MVM(mat4_rotateY(-90.0 / maxSteps), step);
                atPoint = mat4_MVM(mat4_translate(eyePoint.x, eyePoint.y, eyePoint.z), step);
                break;
            case (move_up):
                eyePoint = vec4_VVA(eyePoint, eyeDelta);
                atPoint = vec4_VVS(atPoint, step);
                upVec = vec4_VVA(upVec, upDelta);
                break;
            case (move_down):
                eyePoint = vec4_VVS(eyePoint, eyeDelta);
                atPoint = vec4_VVA(atPoint, step);
                upVec = vec4_VVS(upVec, upDelta);
                break;
            }
            curStep++;
        }
    }

    model_view_matrix = look_at(eyePoint, atPoint, upVec);
    lightPoint = vec4_Norm(mat4_MVM(model_view_matrix, vec4_VVS(, atPoint)));

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    //? Create Maze
    int mazeRows = 8;
    int mazeCols = 8;
    int *path;
    int *pathOpt;
    int *pathOptInv;

    Maze(mazeRows, mazeCols);
    path = createPath();
    pathOpt = createPathOpt();
    pathOptInv = invertPath(pathOpt);
    printMaze();

    //? Create Verts
    convertMaze();
    // makeTexs(mazeRows, mazeCols);
    makeNormal();

    //? Create View
    float left = -0.25;
    float right = +0.25;
    float bottom = -0.25;
    float top = 0.25;
    float far = -100.0;
    float near = -0.25;
    projection_matrix = frustrum(left, right, bottom, top, near, far);

    //? OPENGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Triangle");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(passive);
    glutIdleFunc(idle);
    glutMainLoop();

    // Free Main Memory
    free(path);
    free(verts);
    free(texs);
    free(path);
    free(pathOpt);
    free(pathOptInv);
    freeMaze();

    return 0;
}
