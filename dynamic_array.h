//dynamic_array.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SOME_HEADER_GUARD_WITH_UNIQUE_NAME
#define SOME_HEADER_GUARD_WITH_UNIQUE_NAME

struct Array{
  char *array;
  size_t used;
  size_t size;
};

void initArray(struct Array *a, size_t initialSize);
void insertArray(struct Array *a, char element);
void freeArray(struct Array *a);

#endif