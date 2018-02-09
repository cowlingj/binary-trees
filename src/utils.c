#include <stdlib.h>
#include <string.h>

/**
 * A simple compare function to make sure things compile.
 */

int cmp(void* left, size_t left_size, void* right, size_t right_size){
  return strcmp((char*) left, (char*) right);
}

char*stringify(void* data, size_t data_size){
  return (char*) data;
}
