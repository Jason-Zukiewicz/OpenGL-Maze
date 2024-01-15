#include "mat4.h"

void mat4_print(mat4 M)
{
    printf("[%0.4f %0.4f %0.4f %0.4f]\n", M.X.x, M.Y.x, M.Z.x, M.W.x);
    printf("[%0.4f %0.4f %0.4f %0.4f]\n", M.X.y, M.Y.y, M.Z.y, M.W.y);
    printf("[%0.4f %0.4f %0.4f %0.4f]\n", M.X.z, M.Y.z, M.Z.z, M.W.z);
    printf("[%0.4f %0.4f %0.4f %0.4f]\n", M.X.w, M.Y.w, M.Z.w, M.W.w);
}

void mat3_print(mat3 M)
{
    printf("[%0.4f %0.4f %0.4f]\n", M.X.x, M.Y.x, M.Z.x);
    printf("[%0.4f %0.4f %0.4f]\n", M.X.y, M.Y.y, M.Z.y);
    printf("[%0.4f %0.4f %0.4f]\n", M.X.z, M.Y.z, M.Z.z);
}

/*
 * Scalar x Matrix Multiplication
 */
mat4 mat4_SMM(float S, mat4 M)
{
    mat4 result;
    result.X = vec4_SVM(S, M.X);
    result.Y = vec4_SVM(S, M.Y);
    result.Z = vec4_SVM(S, M.Z);
    result.W = vec4_SVM(S, M.W);
    return result;
}

/*
 * Matix x Matrix Addition
 */
mat4 mat4_MMA(mat4 M, mat4 N)
{
    mat4 result;
    result.X = vec4_VVA(M.X, N.X);
    result.Y = vec4_VVA(M.Y, N.Y);
    result.Z = vec4_VVA(M.Z, N.Z);
    result.W = vec4_VVA(M.W, N.W);
    return result;
}

/*
 * Matrix x Matrix Subtraction
 */
mat4 mat4_MMS(mat4 M, mat4 N)
{
    mat4 result;
    result.X = vec4_VVS(M.X, N.X);
    result.Y = vec4_VVS(M.Y, N.Y);
    result.Z = vec4_VVS(M.Z, N.Z);
    result.W = vec4_VVS(M.W, N.W);
    return result;
}

/*
 * Matrix x Matrix Multiplication
 * - A.{}.x * B.x.{}
 * - A Row * B Colum
 */
mat4 mat4_MMM(mat4 M, mat4 N)
{
    mat4 result;

    // Calculate the first row of the result matrix
    result.X.x = (M.X.x * N.X.x) + (M.Y.x * N.X.y) + (M.Z.x * N.X.z) + (M.W.x * N.X.w);
    result.Y.x = (M.X.x * N.Y.x) + (M.Y.x * N.Y.y) + (M.Z.x * N.Y.z) + (M.W.x * N.Y.w);
    result.Z.x = (M.X.x * N.Z.x) + (M.Y.x * N.Z.y) + (M.Z.x * N.Z.z) + (M.W.x * N.Z.w);
    result.W.x = (M.X.x * N.W.x) + (M.Y.x * N.W.y) + (M.Z.x * N.W.z) + (M.W.x * N.W.w);

    // Calculate the second row of the result matrix
    result.X.y = (M.X.y * N.X.x) + (M.Y.y * N.X.y) + (M.Z.y * N.X.z) + (M.W.y * N.X.w);
    result.Y.y = (M.X.y * N.Y.x) + (M.Y.y * N.Y.y) + (M.Z.y * N.Y.z) + (M.W.y * N.Y.w);
    result.Z.y = (M.X.y * N.Z.x) + (M.Y.y * N.Z.y) + (M.Z.y * N.Z.z) + (M.W.y * N.Z.w);
    result.W.y = (M.X.y * N.W.x) + (M.Y.y * N.W.y) + (M.Z.y * N.W.z) + (M.W.y * N.W.w);

    // Calculate the third row of the result matrix
    result.X.z = (M.X.z * N.X.x) + (M.Y.z * N.X.y) + (M.Z.z * N.X.z) + (M.W.z * N.X.w);
    result.Y.z = (M.X.z * N.Y.x) + (M.Y.z * N.Y.y) + (M.Z.z * N.Y.z) + (M.W.z * N.Y.w);
    result.Z.z = (M.X.z * N.Z.x) + (M.Y.z * N.Z.y) + (M.Z.z * N.Z.z) + (M.W.z * N.Z.w);
    result.W.z = (M.X.z * N.W.x) + (M.Y.z * N.W.y) + (M.Z.z * N.W.z) + (M.W.z * N.W.w);

    // Calculate the fourth row of the result matrix
    result.X.w = (M.X.w * N.X.x) + (M.Y.w * N.X.y) + (M.Z.w * N.X.z) + (M.W.w * N.X.w);
    result.Y.w = (M.X.w * N.Y.x) + (M.Y.w * N.Y.y) + (M.Z.w * N.Y.z) + (M.W.w * N.Y.w);
    result.Z.w = (M.X.w * N.Z.x) + (M.Y.w * N.Z.y) + (M.Z.w * N.Z.z) + (M.W.w * N.Z.w);
    result.W.w = (M.X.w * N.W.x) + (M.Y.w * N.W.y) + (M.Z.w * N.W.z) + (M.W.w * N.W.w);

    return result;
}

/*
 * Input: 4x4 matrix: M
 * Output: 4x4 matrix: R
 * Function: R(i,j) = M(j,i)
 */
mat4 mat4_transpose(mat4 M)
{
    mat4 result;
    result.X.x = M.X.x;
    result.X.y = M.Y.x;
    result.X.z = M.Z.x;
    result.X.w = M.W.x;
    result.Y.x = M.X.y;
    result.Y.y = M.Y.y;
    result.Y.z = M.Z.y;
    result.Y.w = M.W.y;
    result.Z.x = M.X.z;
    result.Z.y = M.Y.z;
    result.Z.z = M.Z.z;
    result.Z.w = M.W.z;
    result.W.x = M.X.w;
    result.W.y = M.Y.w;
    result.W.z = M.Z.w;
    result.W.w = M.W.w;
    return result;
}

/*
 * Input: 4x4 matrix: M
 *        4x1 vector: V
 * Output: 4x1 vector: R
 * Function: R(i) = M(i,j)V(j) + M(i,j+1)V(j+1) + M(i,j+2)V(j+2) + M(i,j+3)V(j+3)
 */
vec4 mat4_MVM(mat4 M, vec4 V)
{
    vec4 result;
    result.x = (M.X.x * V.x) + (M.Y.x * V.y) + (M.Z.x * V.z) + (M.W.x * V.w);
    result.y = (M.X.y * V.x) + (M.Y.y * V.y) + (M.Z.y * V.z) + (M.W.y * V.w);
    result.z = (M.X.z * V.x) + (M.Y.z * V.y) + (M.Z.z * V.z) + (M.W.z * V.w);
    result.w = (M.X.w * V.x) + (M.Y.w * V.y) + (M.Z.w * V.z) + (M.W.w * V.w);
    return result;
}

/* ----------------------------------- [ INVERSE ] ----------------------------------------------- */
/*
 * The output should result in mat4_MMM(M, inv) = identity matrix
 */
mat4 mat4_inverse(mat4 M)
{

    mat4 minor = mat4_minor(M);
    mat4 cofactor = mat4_cofactor(minor);
    mat4 transpose = mat4_transpose(cofactor);
    GLfloat determinant = mat4_determinant(M, minor);
    if (determinant == 0)
    {
        // return mat4_identity();
    }

    mat4 a_inv = mat4_SMM(1 / determinant, transpose);

    // Test Printing
    if (0)
    {
        printf("--------------------------------\n");
        printf("Input: \n");
        mat4_print(M);

        printf("Minor: \n");
        mat4_print(minor);

        printf("Cofactor: \n");
        mat4_print(cofactor);

        printf("Transpose: \n");
        mat4_print(transpose);

        printf("Determinant: %f\n", determinant);

        printf("Inverse: \n");
        mat4_print(a_inv);

        printf("--------------------------------\n");
    }

    return a_inv;
}

/*
 * Input: 4x4 matrix: M
 * Output: 4x4 matrix: R
 * Function: R(i,j) = determinant(M with row i removed and column j removed)
 */
mat4 mat4_minor(mat4 M)
{
    mat4 result = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    result.X.x = mat3_determinant((mat3){{M.Y.y, M.Y.z, M.Y.w}, {M.Z.y, M.Z.z, M.Z.w}, {M.W.y, M.W.z, M.W.w}});
    result.X.y = mat3_determinant((mat3){{M.Y.x, M.Y.z, M.Y.w}, {M.Z.x, M.Z.z, M.Z.w}, {M.W.x, M.W.z, M.W.w}});
    result.X.z = mat3_determinant((mat3){{M.Y.x, M.Y.y, M.Y.w}, {M.Z.x, M.Z.y, M.Z.w}, {M.W.x, M.W.y, M.W.w}});
    result.X.w = mat3_determinant((mat3){{M.Y.x, M.Y.y, M.Y.z}, {M.Z.x, M.Z.y, M.Z.z}, {M.W.x, M.W.y, M.W.z}});

    result.Y.x = mat3_determinant((mat3){{M.X.y, M.X.z, M.X.w}, {M.Z.y, M.Z.z, M.Z.w}, {M.W.y, M.W.z, M.W.w}});
    result.Y.y = mat3_determinant((mat3){{M.X.x, M.X.z, M.X.w}, {M.Z.x, M.Z.z, M.Z.w}, {M.W.x, M.W.z, M.W.w}});
    result.Y.z = mat3_determinant((mat3){{M.X.x, M.X.y, M.X.w}, {M.Z.x, M.Z.y, M.Z.w}, {M.W.x, M.W.y, M.W.w}});
    result.Y.w = mat3_determinant((mat3){{M.X.x, M.X.y, M.X.z}, {M.Z.x, M.Z.y, M.Z.z}, {M.W.x, M.W.y, M.W.z}});

    result.Z.x = mat3_determinant((mat3){{M.X.y, M.X.z, M.X.w}, {M.Y.y, M.Y.z, M.Y.w}, {M.W.y, M.W.z, M.W.w}});
    result.Z.y = mat3_determinant((mat3){{M.X.x, M.X.z, M.X.w}, {M.Y.x, M.Y.z, M.Y.w}, {M.W.x, M.W.z, M.W.w}});
    result.Z.z = mat3_determinant((mat3){{M.X.x, M.X.y, M.X.w}, {M.Y.x, M.Y.y, M.Y.w}, {M.W.x, M.W.y, M.W.w}});
    result.Z.w = mat3_determinant((mat3){{M.X.x, M.X.y, M.X.z}, {M.Y.x, M.Y.y, M.Y.z}, {M.W.x, M.W.y, M.W.z}});

    result.W.x = mat3_determinant((mat3){{M.X.y, M.X.z, M.X.w}, {M.Y.y, M.Y.z, M.Y.w}, {M.Z.y, M.Z.z, M.Z.w}});
    result.W.y = mat3_determinant((mat3){{M.X.x, M.X.z, M.X.w}, {M.Y.x, M.Y.z, M.Y.w}, {M.Z.x, M.Z.z, M.Z.w}});
    result.W.z = mat3_determinant((mat3){{M.X.x, M.X.y, M.X.w}, {M.Y.x, M.Y.y, M.Y.w}, {M.Z.x, M.Z.y, M.Z.w}});
    result.W.w = mat3_determinant((mat3){{M.X.x, M.X.y, M.X.z}, {M.Y.x, M.Y.y, M.Y.z}, {M.Z.x, M.Z.y, M.Z.z}});

    return result;
}

/*
 * Input: 4x4 matrix: M
 * Output: 4x4 matrix: C
 * Function: C(i,j) = Negate every other element of M
 */
mat4 mat4_cofactor(mat4 M)
{
    mat4 result;
    result.X.x = M.X.x;
    result.X.y = -M.X.y;
    result.X.z = M.X.z;
    result.X.w = -M.X.w;

    result.Y.x = -M.Y.x;
    result.Y.y = M.Y.y;
    result.Y.z = -M.Y.z;
    result.Y.w = M.Y.w;

    result.Z.x = M.Z.x;
    result.Z.y = -M.Z.y;
    result.Z.z = M.Z.z;
    result.Z.w = -M.Z.w;

    result.W.x = -M.W.x;
    result.W.y = M.W.y;
    result.W.z = -M.W.z;
    result.W.w = M.W.w;

    return result;
}

/*
 * Input: 4x4 matrix: M
 *        4x4 matrix: N = minor(M)
 * Output: GLfloat: R = M(0,j)N(0,j) - M(0,j+1)N(0,j+1) + M(0,j+2)N(0,j+2) - M(0,j+3)N(0,j+3)
 */
GLfloat mat4_determinant(mat4 M, mat4 N)
{
    GLfloat result = 0;
    result = M.X.x * N.X.x - M.Y.x * N.Y.x + M.Z.x * N.Z.x - M.W.x * N.W.x;
    return result;
}

GLfloat mat3_determinant(mat3 M)
{
    GLfloat result;
    result = (M.X.x * M.Y.y * M.Z.z) + (M.Y.x * M.Z.y * M.X.z) + (M.Z.x * M.X.y * M.Y.z) - (M.X.z * M.Y.y * M.Z.x) - (M.Y.z * M.Z.y * M.X.x) - (M.Z.z * M.X.y * M.Y.x);
    return result;
}

mat4 mat4_identity()
{
    mat4 result;
    result.X = (vec4){1, 0, 0, 0};
    result.Y = (vec4){0, 1, 0, 0};
    result.Z = (vec4){0, 0, 1, 0};
    result.W = (vec4){0, 0, 0, 1};
    return result;
}
