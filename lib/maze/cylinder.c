#include "cylinder.h"




/*
* For the cylinder we take the code to make a code
* We use the button circle and move it to the height to make the top & bottom
* Then we connect the outer points of the top and bottom to make the sides

*/
vec4* makeCylinder(int numSegments, float h, float w, float b) {
    int num_vertices = 0;
    vec4* verts = (vec4 *)malloc(numSegments * 12 * sizeof(vec4));
    
    
    int i;
    float angle = 2 * M_PI / numSegments;

    h = h + b;
    
    for (i = 0; i < numSegments; i++) {
        float x1 = w * cos(i * angle);
        float z1 = w * sin(i * angle);
        float x2 = w * cos((i + 1) * angle);
        float z2 = w * sin((i + 1) * angle);


        // Bottom-Circle
        verts[num_vertices++] = (vec4){0.0, b, 0.0, 1.0};
        verts[num_vertices++] = (vec4){x1, b, z1, 1.0};
        verts[num_vertices++] = (vec4){x2, b, z2, 1.0};
        
        
        // Top-Circle
        verts[num_vertices++] = (vec4){0.0, h, 0.0, 1.0};
        verts[num_vertices++] = (vec4){x1, h, z1, 1.0};
        verts[num_vertices++] = (vec4){x2, h, z2, 1.0};

        // Side-1
        verts[num_vertices++] = (vec4){x1, b, z1, 1.0};
        verts[num_vertices++] = (vec4){x1, h, z1, 1.0};
        verts[num_vertices++] = (vec4){x2, b, z2, 1.0};
        

        // Side-2
        verts[num_vertices++] = (vec4){x1, h, z1, 1.0};
        verts[num_vertices++] = (vec4){x2, h, z2, 1.0};
        verts[num_vertices++] = (vec4){x2, b, z2, 1.0};
        
    }
    return verts;
}

