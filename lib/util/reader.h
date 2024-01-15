#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include "../math/vec4.h"
#include "util.h"

int ReaderSize(char *filename);
vec4 *ReaderVerts(char *filename);

#endif