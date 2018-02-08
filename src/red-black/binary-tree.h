#ifndef BINARY_TREE__
#define BINARY_TREE__
#include <stdbool.h>
#include <stdio.h>

typedef struct tree tree_t;
tree_t* insert(void* data, size_t data_size, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t));
tree_t* insert_subtree(tree_t *subtree, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t));
tree_t* get(void* data, size_t data_size, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t));
bool find(void* data, size_t data_size, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t));
int ftree_printf(FILE *file, tree_t *tree, char* (*stringify)(void*, size_t));
int tree_printf(tree_t *tree, char* (*stringify)(void*, size_t));
tree_t* tree_remove(void* data, size_t data_size, tree_t* tree, int (*cmp)(void*, size_t, void*, size_t));
int tree_free(tree_t *tree);

#endif