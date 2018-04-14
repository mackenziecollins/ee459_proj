//dynamic_array.c
#include "dynamic_array.h"

// typedef struct {
//   int *array;
//   size_t used;
//   size_t size;
// } Array;

void initArray(struct Array *a, size_t initialSize) {
  a->array = (char *)malloc(initialSize * sizeof(char));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(struct Array *a, char element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (char *)realloc(a->array, a->size * sizeof(char));
  }
  a->array[a->used++] = element;
}

void freeArray(struct Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}