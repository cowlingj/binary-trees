#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary-tree.h"

struct tree {
  void* data;
  size_t data_size;
  struct tree *left;
  struct tree *right;
  struct tree *parent;
  size_t size;
};

size_t get_size(tree_t *tree){
  if (tree == NULL){
    return 0;
  } else {
    return tree->size;
  }
}

tree_t* insert(void* data, size_t data_size, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t)){
  if (tree == NULL){
    tree_t *ret = malloc(sizeof(tree_t));
    ret->data = data;
    ret->data_size = data_size;
    ret->left = NULL;
    ret->right = NULL;
    ret->size = 1;
    return ret;
  }

  int result = cmp(data, data_size, tree->data, tree->data_size);
  if (result < 0){
    size_t old_subtree_size = get_size(tree->left);
    tree->left = insert(data, data_size, tree->left, cmp);
    tree->left->parent = tree;
    if (old_subtree_size != get_size(tree->left)){
      tree->size = 1 + get_size(tree->left) + get_size(tree->right);
    }
  }
  if (result > 0){
    size_t old_subtree_size = get_size(tree->right);
    tree->right = insert(data, data_size, tree->right, cmp);
    tree->right->parent = tree;
    if (old_subtree_size != get_size(tree->right)){
      tree->size = 1 + get_size(tree->left) + get_size(tree->right);
    }
  }
  // if result == 0, ignore
  return tree;
}

tree_t* insert_subtree(tree_t *subtree, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t)){
  if (subtree == NULL){
    return tree;
  }
  if (tree == NULL){
    return subtree;
  }

  int result = cmp(subtree->data, subtree->data_size, tree->data, tree->data_size);
  if (result < 0){
    size_t old_subtree_size = get_size(tree->left);
    tree->left = insert_subtree(subtree, tree->left, cmp);
    tree->left->parent = tree;
    if (old_subtree_size != get_size(tree->left)){
      tree->size = 1 + get_size(tree->left) + get_size(tree->right);
    }
  }
  if (result > 0){
    size_t old_subtree_size = get_size(tree->right);
    tree->right = insert_subtree(subtree, tree->right, cmp);
    tree->right->parent = tree;
    if (old_subtree_size != get_size(tree->right)){
      tree->size = 1 + get_size(tree->left) + get_size(tree->right);
    }
  }
  // if result == 0, ignore
  return tree;
}

tree_t* get(void* data, size_t data_size, tree_t* tree, int (*cmp)(void*, size_t, void*, size_t)){
  if (tree == NULL){
    return NULL;
  }
  
  int result = cmp(data, data_size, tree->data, tree->data_size);
  if (result < 0){
    return get(data, data_size, tree->left, cmp);
  }
  if (result > 0){
    return get(data, data_size, tree->right, cmp);
  }
  // if result == 0, we found the item
  return tree;
}

bool find(void* data, size_t data_size, tree_t* tree, int (*cmp)(void*, size_t, void*, size_t)){
  return get(data, data_size, tree, cmp) != NULL;
}

int ftree_printf(FILE *file, tree_t *tree, char* (*stringify)(void*, size_t)){
  if (tree == NULL) { return 0; }

  fprintf(file,"tree[%p]: { data: \"%s\", left[%p], right[%p], parent[%p], size[%lu] }\n",
          (void *) tree, stringify(tree->data, tree->data_size),
          (void *) tree->left, (void *)  tree->right, (void *)  tree->parent,
          tree->size);
  return ftree_printf(file, tree->left, stringify)
    || ftree_printf(file, tree->right, stringify);
}

int tree_printf(tree_t *tree, char* (*stringify)(void*, size_t)){
  return ftree_printf(stdout, tree, stringify);
}

tree_t* tree_remove(void* data, size_t data_size, tree_t* tree, int (*cmp)(void*, size_t, void*, size_t)){
  tree_t *to_remove = get(data, data_size, tree, cmp);
  if (to_remove == NULL){
    return NULL;
  }
  
  size_t left_size = get_size(to_remove->left);
  size_t right_size = get_size(to_remove->right);

  if (to_remove->parent == NULL){
    if (left_size >= right_size){
      *tree = *to_remove->left;
      *tree = *insert_subtree(to_remove->right, tree, cmp);
    }
    if (left_size < right_size){
      *tree = *to_remove->right;
      *tree = *insert_subtree(to_remove->right, tree, cmp);
    }

    to_remove->left = NULL;
    to_remove->right = NULL;
    to_remove->parent = NULL;
    to_remove->size = 1;

    return to_remove;
  }

  // to remove tree t, we need to disconnect it from its parent p,
  // so we must find out which child of p is t
  bool left_child = to_remove->parent->left == to_remove;

  // move the larger tree up and insert the smaller one into the larger one
  if (left_child && left_size >= right_size){
    to_remove->parent->left = to_remove->left;
    to_remove->left = insert_subtree(to_remove->right, to_remove->left, cmp);
  } else if (left_child && left_size < right_size){
    to_remove->parent->left = to_remove->right;
    to_remove->right = insert_subtree(to_remove->left, to_remove->right, cmp);
  } else if (!left_child && left_size >= right_size){
    to_remove->parent->right = to_remove->left;
    to_remove->left = insert_subtree(to_remove->right, to_remove->left, cmp);
  } else {
    to_remove->parent->right = to_remove->right;
    to_remove->right = insert_subtree(to_remove->left, to_remove->right, cmp);
  }

  to_remove->left = NULL;
  to_remove->right = NULL;
  to_remove->parent = NULL;
  to_remove->size = 1;

  return to_remove;
}

int tree_free(tree_t *tree){
  if (tree == NULL){
    return 0;
  }
  int ret = tree_free(tree->left) || tree_free(tree->right);
  free(tree->data);
  free(tree);
  return ret;
}
