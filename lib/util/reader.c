
#include "reader.h"
#include <string.h>
int SCALE = 100;


int ReaderSize(char *filename)
{
    FILE *file;

    // Open the file for reading
    file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Unable to open the file");
        return -1;
    }

    int num_verts;

    // Read the number of vertices from the file (assuming it's in the first line)
    if (fscanf(file, "%d", &num_verts) != 1)
    {
        fprintf(stderr, "Failed to read the number of vertices from the file\n");
        fclose(file);
        return -1;
    }
    fclose(file);
    return num_verts;
}

vec4 *ReaderVerts(char *filename) {
    vec4 *verts;
    FILE *file;

    // Open the file for reading
    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Unable to open the file");
        return NULL;
    }

    int num_verts;

    char line[256]; // Adjust the buffer size as needed

    // Read the number of vertices from the file (assuming it's in the first line)
    fgets(line, sizeof(line), file);
    sscanf(line, "%i ", &num_verts);

    // Allocate memory for the array of vec4 based on the number of vertices
    verts = (vec4 *)malloc(num_verts * sizeof(vec4));

    if (verts == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }


    // Read and process lines from the file
    float x, y, z, w;
    for (int i = 0; i < num_verts; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "%f,%f,%f,%f", &x, &y, &z, &w) == 4) {
                verts[i].x = x ;
                verts[i].y = y ;
                verts[i].z = z ;
                verts[i].w = w;
            } else {
                printf("Failed to parse data in line %d\n", i);
            }
        } else {
            printf("Failed to read line %d\n", i);
        }
    }

    // Determine the object's dimensions
    float min_x = verts[0].x, max_x = verts[0].x;
    float min_y = verts[0].y, max_y = verts[0].y;
    float min_z = verts[0].z, max_z = verts[0].z;

    for (int i = 1; i < num_verts; i++) {
        float x = verts[i].x;
        float y = verts[i].y;
        float z = verts[i].z;

        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
        if (z < min_z) min_z = z;
        if (z > max_z) max_z = z;
    }

    // Calculate scaling factors for each dimension (x, y, z)
    float scaleX = 2.0 / (max_x - min_x);
    float scaleY = 2.0 / (max_y - min_y);
    float scaleZ = 2.0 / (max_z - min_z);

    // Choose the minimum scaling factor to ensure the entire object fits in the display
    float scale = fminf(fminf(scaleX, scaleY), scaleZ);

    // Translate the object to the center of the display
    float translateX = -(max_x + min_x) / 2.0;
    float translateY = -(max_y + min_y) / 2.0;
    float translateZ = -(max_z + min_z) / 2.0;

    for (int i = 0; i < num_verts; i++) {
        verts[i].x = (verts[i].x + translateX) * scale;
        verts[i].y = (verts[i].y + translateY) * scale;
        verts[i].z = (verts[i].z + translateZ) * scale;
    }

    // Close the file
    fclose(file);

    for (int i = 0; i < num_verts; i++)
        verts[i] = mat4_MVM(mat4_translate(0, 0, -0.33), verts[i]);

    return verts;
}


