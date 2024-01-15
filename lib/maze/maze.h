#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "../math/mat4.h"
#include "../util/util.h"

typedef struct
{
    bool top;
    bool left;
    bool right;
    bool bottom;
    int dir;
} Cell;

typedef enum
{
    BLANK,
    UP,
    RIGHT,
    DOWN,
    LEFT,
} Direction;

typedef enum
{
    EXIT = -1,
    TURN_LEFT = 0,
    MOVE_FORWARD = 1,
    TURN_RIGHT = 2,
} Path;

void addString(char *string, char *addition, int start, int size);

//? Maze
void initMaze();
void genMaze(int r1, int r2, int c1, int c2);
void printMaze();
void Maze(int r, int c);
void freeMaze();

//? Path
void printPath();
int *createPath();
int *createPathOpt();
int *invertPath(int *path);

//? Verts
void makeCylinder();
void makeSquareX(float y1, float y2, float z1, float z2, float x);
void makeSquareY(float x1, float x2, float z1, float z2, float y);
void makeSquareZ(float x1, float x2, float y1, float y2, float z);
void makeCube(float x1, float x2, float y1, float y2, float z1, float z2);
void makeWallHori(int row, int col);
void makeWallVert(int r, int c);
void makePillar(int row, int col);
void makeFloor();

void convertMaze();

Direction getDirection(Direction moveDir, Direction lookDir);
bool moveDirection(vec4 eye, vec4 at, Direction moveDir);
bool canMoveDirection(vec4 eye, vec4 at, Direction moveDir);

#endif