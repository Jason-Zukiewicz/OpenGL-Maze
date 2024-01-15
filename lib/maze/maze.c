#pragma GCC diagnostic ignored "-Wcomment"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wswitch"

#include "maze.h"

int rows;
int cols;
Cell **maze;

extern int numVerts;
extern vec4 *verts;

// < ---------------------------------[ CREATION ]---------------------------------------->  \\

void addString(char *string, char *addition, int start, int size)
{
    for (int i = 0; i < size; i++)
        string[start + i] = addition[i];
}

void printMaze()
{
    char strings[rows * 3][5 * cols + 1]; // Array of strings
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            Cell *cell = &maze[r][c];
            int strIndex = r * 3;
            int strPos = c * 5;
            // Top part of the cell
            if (cell->top)
                addString(strings[strIndex + 0], "+---+", strPos, 5);
            else
                addString(strings[strIndex + 0], "+   +", strPos, 5);

            // Middle part of the cell
            if (cell->left)
                addString(strings[strIndex + 1], "| ", strPos, 2);
            else
                addString(strings[strIndex + 1], "  ", strPos, 2);

            switch (cell->dir)
            {
            case (BLANK):
                addString(strings[strIndex + 1], "  ", strPos + 2, 2);
                break;
            case (UP):
                addString(strings[strIndex + 1], "^ ", strPos + 2, 2);
                break;
            case (RIGHT):
                addString(strings[strIndex + 1], "> ", strPos + 2, 2);
                break;
            case (DOWN):
                addString(strings[strIndex + 1], "V ", strPos + 2, 2);
                break;
            case (LEFT):
                addString(strings[strIndex + 1], "< ", strPos + 2, 2);
                break;
            default:
                addString(strings[strIndex + 1], "x ", strPos + 2, 2);
            }

            // Right part of the cell
            if (cell->right)
                addString(strings[strIndex + 1], "|", strPos + 4, 1);
            else
                addString(strings[strIndex + 1], " ", strPos + 4, 1);

            // Bottom part of the cell
            if (cell->bottom)
                addString(strings[strIndex + 2], "+---+", strPos, 5);
            else
                addString(strings[strIndex + 2], "+   +", strPos, 5);

            if (c == cols - 1)
            {
                addString(strings[strIndex + 0], "\0", strPos + 5, 1);
                addString(strings[strIndex + 1], "\0", strPos + 5, 1);
                addString(strings[strIndex + 2], "\0", strPos + 5, 1);
            }
        }
    }

    for (int r = 0; r < rows * 3; r++)
    {
        printf("%s\n", strings[r]);
    }
}

void genMaze(int r1, int r2, int c1, int c2)
{
    srand(clock());

    //? BASE RECURSION CHECK
    if (r1 >= r2 || c1 >= c2)
        return;

    //? Generate Walls
    int rWall = r1 + rand() % (r2 - r1); // INCLUSIVE
    int cWall = c1 + rand() % (c2 - c1); // INCLUSIVE

    //? Place Walls: Left & Right
    for (int r = r1; r <= r2; r++)
    {
        maze[r][cWall].right = true;
        maze[r][cWall + 1].left = true;
    }

    //? Place Walls: Top & Bottom
    for (int c = c1; c <= c2; c++)
    {
        maze[rWall][c].bottom = true;
        maze[rWall + 1][c].top = true;
    }

    //? Gen Cuts
    int cutWall = 0 + rand() % (3 - 0 + 1); // INCLUSIVE
    int cutSpot;

    //? PLACE CUTS
    if (cutWall != 0) //? TOP
    {
        cutSpot = r1 + rand() % (rWall - r1 + 1); // INCLUSIVE
        maze[cutSpot][cWall + 1].left = false;
        maze[cutSpot][cWall].right = false;
    }
    if (cutWall != 1) //? RIGHT
    {
        cutSpot = cWall + 1 + rand() % (c2 - cWall); // HIGH inclusive
        maze[rWall + 1][cutSpot].top = false;
        maze[rWall][cutSpot].bottom = false;
    }
    if (cutWall != 2) //? Bottom
    {
        cutSpot = rWall + 1 + rand() % (r2 - rWall); // HIGH inclusive
        maze[cutSpot][cWall + 1].left = false;
        maze[cutSpot][cWall].right = false;
    }
    if (cutWall != 3) //? LEFT
    {
        cutSpot = c1 + rand() % (cWall - c1 + 1); // INCLUSIVE
        maze[rWall + 1][cutSpot].top = false;
        maze[rWall][cutSpot].bottom = false;
    }

    //? RECURSION
    genMaze(r1, rWall, c1, cWall);         //? TOP-LEFT
    genMaze(r1, rWall, cWall + 1, c2);     //? TOP-RIGHT
    genMaze(rWall + 1, r2, c1, cWall);     //? BOT-LEFT
    genMaze(rWall + 1, r2, cWall + 1, c2); //? BOT-RIGHT
}

void initMaze()
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (y == 0)
                maze[y][x].top = true;
            else
                maze[y][x].top = false;

            if (y == rows - 1)
                maze[y][x].bottom = true;
            else
                maze[y][x].bottom = false;

            if (x == 0)
                maze[y][x].left = true;
            else
                maze[y][x].left = false;

            if (x == cols - 1)
                maze[y][x].right = true;
            else
                maze[y][x].right = false;

            maze[y][x].dir = BLANK;
        }
    }
}

void Maze(int r, int c)
{
    rows = r;
    cols = c;
    maze = (Cell **)malloc(rows * sizeof(Cell *));
    for (int i = 0; i < rows; i++)
        maze[i] = (Cell *)malloc(cols * sizeof(Cell));

    initMaze();
    genMaze(0, rows - 1, 0, cols - 1);

    //? Create Entrance & Exit
    maze[0][0].left = false;
    maze[rows - 1][cols - 1].right = false;

    // printMaze();
}

void freeMaze()
{
    for (int i = 0; i < rows; ++i)
        free(maze[i]); // Free each row
    free(maze);        // Free the array of rows
}
// < ---------------------------------[ Solving ]---------------------------------------->  \\

void printPath(int *path)
{
    int pos = 0;
    char output[50];
    while (path[pos] != -1)
    {
        int action = path[pos++];

        switch (action)
        {
        case (TURN_LEFT):
            snprintf(output, sizeof(output), "Turn Left");
            break;
        case (MOVE_FORWARD):
            snprintf(output, sizeof(output), "Move Forward");
            break;
        case (TURN_RIGHT):
            snprintf(output, sizeof(output), "Turn Right");
            break;
        default:
            snprintf(output, sizeof(output), "Unknown Action");
        }
        printf("[Path %d] %s \n", pos, output);
    }
}

int *createPath()
{
    int *path = (int *)malloc((rows + 1) * (cols + 1) * 4 * sizeof(int));
    int pos = 0;
    int dir = RIGHT;
    path[pos++] = MOVE_FORWARD;

    int x = 0, y = 0;
    while (x < cols && y < rows)
    {
        // printf("[PATH] POS: %i \n", pos);
        Cell *cell = &maze[y][x];
        bool moved = false;
        if (pos > ((rows + 1) * (cols + 1) * 8))
        {
            printf("[PATH] POSITION IS OUT OF BOUNDS %i \n", pos);
            exit(0);
        }

        //? Try Left
        switch (dir)
        {
        case (UP):
            if (!cell->left)
            {
                cell->dir = dir = LEFT;
                x--;
                path[pos++] = TURN_LEFT;
                path[pos++] = MOVE_FORWARD;
                moved = true;
            }
            break;
        case (RIGHT):
            if (!cell->top)
            {
                cell->dir = dir = UP;
                y--;
                path[pos++] = TURN_LEFT;
                path[pos++] = MOVE_FORWARD;
                moved = true;
            }
            break;
        case (DOWN):
            if (!cell->right)
            {
                cell->dir = dir = RIGHT;
                x++;
                path[pos++] = TURN_LEFT;
                path[pos++] = MOVE_FORWARD;
                moved = true;
            }
            break;
        case (LEFT):
            if (!cell->bottom)
            {
                cell->dir = dir = DOWN;
                y++;
                path[pos++] = TURN_LEFT;
                path[pos++] = MOVE_FORWARD;
                moved = true;
            }
            break;
        }
        if (moved)
            continue;

        //? Try Forward
        switch (dir)
        {
        case (UP):
            if (!cell->top)
            {
                cell->dir = dir;
                path[pos++] = MOVE_FORWARD;
                y--;
                moved = true;
            }
            break;
        case (RIGHT):
            if (!cell->right)
            {
                cell->dir = dir;
                path[pos++] = MOVE_FORWARD;
                x++;
                moved = true;
            }
            break;
        case (DOWN):
            if (!cell->bottom)
            {
                cell->dir = dir;
                path[pos++] = MOVE_FORWARD;
                y++;
                moved = true;
            }
            break;
        case (LEFT):
            if (!cell->left)
            {
                cell->dir = dir;
                path[pos++] = MOVE_FORWARD;
                x--;
                moved = true;
            }
            break;
        }

        if (moved)
            continue;
        //? Rotate Right
        switch (dir)
        {
        case (UP):
            cell->dir = dir = RIGHT;
            break;
        case (RIGHT):
            cell->dir = dir = DOWN;
            break;
        case (DOWN):
            cell->dir = dir = LEFT;
            break;
        case (LEFT):
            cell->dir = dir = UP;
            break;
        }
        path[pos++] = TURN_RIGHT;
    }

    path[pos++] = -1;
    printf("[SOLVED] FINAL POS: %d, %d : Size %i / %i \n", x, y, pos, ((rows + 1) * (cols + 1) * 4));
    return path;
}

int *createPathOpt()
{
    int *path = (int *)malloc((rows + 1) * (cols + 1) * 2 * sizeof(int));
    int pos = 0;
    int dir = RIGHT;
    path[pos++] = MOVE_FORWARD;

    int x = 0, y = 0;
    while (x < cols && y < rows)
    {
        // printf("[PATH] POS: %d, %d \n", x, y);
        Cell *cell = &maze[y][x];

        switch (dir)
        {
        case (UP):
            switch (cell->dir)
            {
            case (UP):
                y--;
                break;
            case (RIGHT):
                path[pos++] = TURN_RIGHT;
                x++;
                break;
            case (DOWN):
                y++;
                break;
            case (LEFT):
                path[pos++] = TURN_LEFT;
                x--;
                break;
            }
            break;
        case (RIGHT):
            switch (cell->dir)
            {
            case (UP):
                path[pos++] = TURN_LEFT;
                y--;
                break;
            case (RIGHT):
                x++;
                break;
            case (DOWN):
                path[pos++] = TURN_RIGHT;
                y++;
                break;
            case (LEFT):
                x--;
                break;
            }
            break;
        case (DOWN):
            switch (cell->dir)
            {
            case (UP):
                y--;
                break;
            case (RIGHT):
                path[pos++] = TURN_LEFT;
                x++;
                break;
            case (DOWN):
                y++;
                break;
            case (LEFT):
                path[pos++] = TURN_RIGHT;
                x--;
                break;
            }
            break;
        case (LEFT):
            switch (cell->dir)
            {
            case (UP):
                path[pos++] = TURN_RIGHT;
                y--;
                break;
            case (RIGHT):
                x++;
                break;
            case (DOWN):
                path[pos++] = TURN_LEFT;
                y++;
                break;
            case (LEFT):
                x--;
                break;
            }
            break;
        }
        path[pos++] = MOVE_FORWARD;
        dir = cell->dir;
    }

    path[pos++] = -1;
    printf("[OPT SOLVED] FINAL POS: %d, %d : Size %i / %i \n", x, y, pos, ((rows + 1) * (cols + 1) * 4));
    return path;
}

int *invertPath(int *path)
{
    // Find the length of the path
    int length = 0;
    while (path[length] != -1)
    {
        length++;
    }

    // Allocate memory for the inverted path
    int *invertedPath = (int *)malloc((length + 1) * sizeof(int));

    // Invert the path
    int invertedIndex = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        switch (path[i])
        {
        case TURN_LEFT:
            invertedPath[invertedIndex++] = TURN_RIGHT;
            break;
        case MOVE_FORWARD:
            invertedPath[invertedIndex++] = MOVE_FORWARD;
            break;
        case TURN_RIGHT:
            invertedPath[invertedIndex++] = TURN_LEFT;
            break;
        default:
            // Handle unknown action or end of path
            invertedPath[invertedIndex++] = path[i];
            break;
        }
    }

    // Mark the end of the inverted path
    invertedPath[invertedIndex] = -1;

    return invertedPath;
}
// < ---------------------------------[ Textures ]---------------------------------------->  \\

float tX = 0.5;
float tY = 0.333;
int tPos = 0;
extern vec2 *texs;

void addFloorTex()
{
    texs[tPos++] = (vec2){0, tY};      // Bottom Left 0,Y
    texs[tPos++] = (vec2){tX / 2, tY}; // Bottom Mid x/2, y
    texs[tPos++] = (vec2){0, tY / 2};  // Mid Left 0, y/2

    texs[tPos++] = (vec2){tX / 2, tY};     // Bottom Mid x/2, y
    texs[tPos++] = (vec2){tX / 2, tY / 2}; // Mid Mid x/2, y/2
    texs[tPos++] = (vec2){0, tY / 2};      // Mid Left 0, y/2
}

void addPillarTex()
{
    int numPillarFaces = (rows + 1) * (cols + 1) * 5;
    for (int i = 0; i < numPillarFaces; i++)
    {
        texs[tPos++] = (vec2){tX / 2, tY / 2};
        texs[tPos++] = (vec2){tX, tY / 2};
        texs[tPos++] = (vec2){tX / 2, 0.0};

        texs[tPos++] = (vec2){tX / 2, tY / 2};
        texs[tPos++] = (vec2){tX, 0.0};
        texs[tPos++] = (vec2){tX / 2, 0.0};
    }
}

void addWallTex()
{
    int numWalls = (2 * (rows + cols) - 2) + ((rows - 1) * (cols - 1));
    int numWallFaces = numWalls * 5;
    for (int i = 0; i < numWallFaces; i++)
    {
        texs[tPos++] = (vec2){0.0, tY / 2};
        texs[tPos++] = (vec2){tX / 2, tY / 2};
        texs[tPos++] = (vec2){tX / 2, 0.0};

        texs[tPos++] = (vec2){0.0, tY / 2};
        texs[tPos++] = (vec2){tX / 2, 0.0};
        texs[tPos++] = (vec2){0.0, 0.0};
    }
}

// < ---------------------------------[ CONVERSION ]---------------------------------------->  \\

float wallDepth = 0.1; //? HALF
float wallHeight = 1.0;
float cellSize = 1.0 / 2;

float const pillarLength = 0.15; //? HALF
float wallLength = 1.0 - (pillarLength * 2);

int midRow;
int midCol;
int pos;
int numSegments = 50;

int coinStart;

void makeCylinder()
{
    float angle = 2 * M_PI / numSegments;

    int coinStart = pos;

    float x1, x2, y1, y2, z1, z2;
    float center = 0.5;
    float rad = 0.4;
    float thick = 0.1;
    for (int i = 0; i < numSegments; i++)
    {
        float x1 = rad * cos(i * angle) + center;
        float x2 = rad * cos((i + 1) * angle) + center;

        float z1 = rad * sin(i * angle) + center;
        float z2 = rad * sin((i + 1) * angle) + center;

        verts[pos++] = (vec4){center, center, 0, 1.0};
        verts[pos++] = (vec4){x1, z1, 0, 1.0};
        verts[pos++] = (vec4){x2, z2, 0, 1.0};

        verts[pos++] = (vec4){center, center, -thick, 1.0};
        verts[pos++] = (vec4){x2, z2, -thick, 1.0};
        verts[pos++] = (vec4){x1, z1, -thick, 1.0};

        //? SIDES
        verts[pos++] = (vec4){x1, z1, 0, 1.0};
        verts[pos++] = (vec4){x1, z1, -thick, 1.0};
        verts[pos++] = (vec4){x2, z2, 0, 1.0};

        verts[pos++] = (vec4){x2, z2, 0, 1.0};
        verts[pos++] = (vec4){x1, z1, -thick, 1.0};
        verts[pos++] = (vec4){x2, z2, -thick, 1.0};

        float tx1 = tX / 2.0;
        float tx2 = 3.0 / 4.0 * tX;
        float ty1 = tY / 2.0;
        float ty2 = 3.0 / 4.0 * tY;
        float centerX = 5.0 / 8.0 * tX;
        float centerY = 5.0 / 8.0 * tY;

        x1 = centerX + cos(i * angle) * (tx2 - tx1) / 2.0;
        y1 = centerY + sin(i * angle) * (ty2 - ty1) / 2.0;

        x2 = centerX + cos((i + 1) * angle) * (tx2 - tx1) / 2.0;
        y2 = centerY + sin((i + 1) * angle) * (ty2 - ty1) / 2.0;

        //? Texture
        texs[tPos++] = (vec2){centerX, centerY};
        texs[tPos++] = (vec2){x1, y1};
        texs[tPos++] = (vec2){x2, y2};

        texs[tPos++] = (vec2){centerX, centerY};
        texs[tPos++] = (vec2){x1, y1};
        texs[tPos++] = (vec2){x2, y2};

        texs[tPos++] = (vec2){centerX, centerY};
        texs[tPos++] = (vec2){x1, y1};
        texs[tPos++] = (vec2){x2, y2};

        texs[tPos++] = (vec2){centerX, centerY};
        texs[tPos++] = (vec2){x1, y1};
        texs[tPos++] = (vec2){x2, y2};
    }

    //? Coin posiition
    int startPos = coinStart;
    while (startPos < pos)
    {
        verts[startPos] = mat4_MVM(mat4_translate(cols + .5, 0, rows), verts[startPos]);
        startPos++;
    }
}

/*
 * Front is from
 * x1 = x/2
 * x2 = 3/4 x
 * y1 = y/2
 * y2 = 3/4 y
 * centerX = (x2 - x1) / 2
 * centerX = (y2 - y1) / 2
 *
 * Back
 * x1 = 3/4 x
 * x2 = x
 * y1 = 3/5 y
 * y2 = y
 */

void makeSquareX(float y1, float y2, float z1, float z2, float x)
{
    verts[pos++] = (vec4){x, y1, z1, 1};
    verts[pos++] = (vec4){x, y1, z2, 1};
    verts[pos++] = (vec4){x, y2, z1, 1};

    verts[pos++] = (vec4){x, y1, z2, 1};
    verts[pos++] = (vec4){x, y2, z2, 1};
    verts[pos++] = (vec4){x, y2, z1, 1};
}

void makeSquareY(float x1, float x2, float z1, float z2, float y)
{
    verts[pos++] = (vec4){x1, y, z1, 1};
    verts[pos++] = (vec4){x2, y, z1, 1};
    verts[pos++] = (vec4){x1, y, z2, 1};

    verts[pos++] = (vec4){x2, y, z1, 1};
    verts[pos++] = (vec4){x2, y, z2, 1};
    verts[pos++] = (vec4){x1, y, z2, 1};
}

void makeSquareZ(float x1, float x2, float y1, float y2, float z)
{
    verts[pos++] = (vec4){x1, y1, z, 1};
    verts[pos++] = (vec4){x2, y1, z, 1};
    verts[pos++] = (vec4){x1, y2, z, 1};

    verts[pos++] = (vec4){x2, y1, z, 1};
    verts[pos++] = (vec4){x2, y2, z, 1};
    verts[pos++] = (vec4){x1, y2, z, 1};
}

void makeCube(float x1, float x2, float y1, float y2, float z1, float z2)
{
    makeSquareX(y1, y2, z2, z1, x1); //? Left
    makeSquareX(y1, y2, z1, z2, x2); //? Right
    makeSquareZ(x1, x2, y1, y2, z1); //? Front
    makeSquareZ(x2, x1, y1, y2, z2); //? Back
    makeSquareY(x1, x2, z1, z2, y2); //? TOP
}

void makeWallHori(int row, int col)
{
    //? Gen Positions
    float x1 = col + pillarLength + cellSize;
    float x2 = col + pillarLength + wallLength + cellSize;
    float z1 = row + wallDepth + cellSize; //? REMEMBER THAT Z+ is towards
    float z2 = row - wallDepth + cellSize;
    float y1 = 0;
    float y2 = wallHeight;

    // printf("MAKEING PILLAR %f %f %f %f %f %f \n", x1, x2, y1, y2, z1, z2);
    makeCube(x1, x2, y1, y2, z1, z2);
}

void makeWallVert(int row, int col)
{
    //? Gen Positions
    float x1 = col - wallDepth + cellSize;
    float x2 = col + wallDepth + cellSize;
    float z1 = row + pillarLength + wallLength + cellSize; //? REMEMBER THAT Z+ is towards
    float z2 = row + pillarLength + cellSize;
    float y1 = 0;
    float y2 = wallHeight;

    // printf("MAKEING PILLAR %f %f %f %f %f %f \n", x1, x2, y1, y2, z1, z2);
    makeCube(x1, x2, y1, y2, z1, z2);
}

void makePillar(int row, int col)
{
    //? Gen Positions
    float x1 = col - pillarLength + cellSize;
    float x2 = col + pillarLength + cellSize;
    float z1 = row + pillarLength + cellSize; //? REMEMBER THAT Z+ is towards
    float z2 = row - pillarLength + cellSize;
    float y1 = 0;
    float y2 = wallHeight;

    // printf("MAKEING PILLAR %f %f %f %f %f %f \n", x1, x2, y1, y2, z1, z2);
    makeCube(x1, x2, y1, y2, z1, z2);
}

void makeFloor()
{
    float x1 = -cols * 2;
    float x2 = +cols * 2;
    float z1 = +rows * 2;
    float z2 = -rows * 2;
    float y = 0;
    makeSquareY(x1, x2, z1, z2, y);
}

void convertMaze()
{
    midRow = rows / 2;
    midCol = cols / 2;

    int numPillars = (rows + 1) * (cols + 1);
    int numOutside = (rows + cols) * 2 - 2;
    int numInside = (rows - 1) * (cols - 1);
    int VertsPerSquare = 5 * 6; // 5 faces and 6 points
    int numFloor = 6;

    numVerts = (numPillars + numOutside + numInside + numFloor) * VertsPerSquare + (numSegments * 12);
    // printf("FOR A (%d, %d) size maze we need %d square and %d verts \n", cols, rows, (numPillars + numOutside + numInside), nuverts);
    verts = malloc(sizeof(vec4) * numVerts);
    texs = malloc(sizeof(vec2) * numVerts);

    makeFloor();
    addFloorTex();

    for (int r = 0; r < rows + 1; r++)
        for (int c = 0; c < cols + 1; c++)
            makePillar(r, c);
    addPillarTex();

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (maze[r][c].top)
                makeWallHori(r, c);

            if (maze[r][c].left)
                makeWallVert(r, c);

            if (c == cols - 1)
                if (maze[r][c].right)
                    makeWallVert(r, c + 1);

            if (r == rows - 1)
                if (maze[r][c].bottom)
                    makeWallHori(r + 1, c);
        }
    }
    addWallTex();

    makeCylinder();
}

// < ---------------------------------[ Collision ]---------------------------------------->  \\

Direction getDirection(Direction moveDir, Direction lookDir)
{
    switch (lookDir)
    {
    case (UP):
        switch (moveDir)
        {
        case (UP):
            return UP;
        case (RIGHT):
            return RIGHT;
        case (DOWN):
            return DOWN;
        case (LEFT):
            return LEFT;
        }
    case (RIGHT):
        switch (moveDir)
        {
        case (UP):
            return RIGHT;
        case (RIGHT):
            return DOWN;
        case (DOWN):
            return LEFT;
        case (LEFT):
            return UP;
        }
    case (DOWN):
        switch (moveDir)
        {
        case (UP):
            return DOWN;
        case (RIGHT):
            return LEFT;
        case (DOWN):
            return UP;
        case (LEFT):
            return RIGHT;
        }
    case (LEFT):
        switch (moveDir)
        {
        case (UP):
            return LEFT;
        case (RIGHT):
            return UP;
        case (DOWN):
            return RIGHT;
        case (LEFT):
            return DOWN;
        }
    }

    return -1;
}

bool moveDirection(vec4 eye, vec4 at, Direction moveDir)
{
    Direction lookDir;
    vec4 step = vec4_VVS(at, eye);
    if (step.x == 1)
        lookDir = RIGHT;
    else if (step.x == -1)
        lookDir = LEFT;
    else if (step.z == 1)
        lookDir = DOWN;
    else if (step.z == -1)
        lookDir = UP;

    moveDir = getDirection(moveDir, lookDir);

    int c1 = eye.x - 1;
    int r1 = eye.z - 1;

    int c2 = at.x - 1;
    int r2 = at.z - 1;

    bool ret = true;

    if (c1 >= 0 && c1 < cols)
        if (r1 >= 0 || r1 < rows)
        {
            printf("THIS SHOULD NOT TRIGGER \n");
            Cell cell = maze[r1][c1];
            switch (moveDir)
            {
            case (UP):
                ret = cell.bottom;
                break;
            case (RIGHT):
                ret = cell.right;
                break;
            case (DOWN):
                ret = cell.bottom;
                break;
            case (LEFT):
                ret = cell.left;
                break;
            }
            printf("[%i, %i] --> [%i, %i] is %i \n", c1, r1, c2, r2, ret);
            return ret;
        }

    if (c2 >= 0 && c2 < cols)
        if (r2 >= 0 || r2 < rows)
        {
            Cell cell = maze[r2][c1];
            switch (moveDir)
            {
            case (UP):
                ret = cell.top;
                break;
            case (RIGHT):
                ret = cell.right;
                break;
            case (DOWN):
                ret = cell.bottom;
                break;
            case (LEFT):
                ret = cell.left;
                break;
            }
        }

    printf("[%i, %i] --> [%i, %i] is %i \n", c1, r1, c2, r2, ret);
    return !ret;
}

bool canMoveDirection(vec4 eye, vec4 at, Direction moveDir)
{
    bool ret = true;
    Direction lookDir;
    vec4 step = vec4_VVS(at, eye);
    if (step.x == 1)
        lookDir = RIGHT;
    else if (step.x == -1)
        lookDir = LEFT;
    else if (step.z == 1)
        lookDir = DOWN;
    else if (step.z == -1)
        lookDir = UP;

    int c1 = eye.x - 1;
    int r1 = eye.z - 1;

    Cell cell;

    Direction trueDir = getDirection(moveDir, lookDir);
    if (c1 >= 0 && c1 < cols)
        if (r1 >= 0 && r1 < rows)
        {
            // printf("Checking EYE [%i, %i] \n", c1, r1);
            cell = maze[r1][c1];
            switch (trueDir)
            {
            case (UP):
                // printf("----- E TOP \n");
                ret = !cell.top;
                break;
            case (RIGHT):
                // printf("----- E RIGHT \n");
                ret = !cell.right;
                break;
            case (DOWN):
                // printf("----- E BOTTOM \n");
                ret = !cell.bottom;
                break;
            case (LEFT):
                // printf("----- E LEFT \n");
                ret = !cell.left;
                break;
            }
        }
    // printf("RET AFTER  EYE %i \n", ret);

    int c2 = c1;
    int r2 = r1;
    switch (trueDir)
    {
    case (UP):
        r2--;
        break;
    case (RIGHT):
        c2++;
        break;
    case (DOWN):
        r2++;
        break;
    case (LEFT):
        c2--;
        break;
    }
    if (c2 >= 0 && c2 < cols)
        if (r2 >= 0 && r2 < rows)
        {
            // printf("Checking AT [%i, %i] \n", c2, r2);
            cell = maze[r2][c2];
            switch (trueDir)
            {
            case (UP):
                // printf("----- A BOTTOM \n");
                ret = !cell.bottom;
                break;
            case (RIGHT):
                // printf("----- A LEFT %i \n", cell.left);
                ret = !cell.left;
                break;
            case (DOWN):
                // printf("----- A TOP \n");
                ret = !cell.top;
                break;
            case (LEFT):
                // printf("----- A RIGHT \n");
                ret = !cell.right;
                break;
            }
        }
    // printf("[%i, %i] --> [%i, %i] is %i \n", c1, r1, c2, r2, ret);
    return ret;
}