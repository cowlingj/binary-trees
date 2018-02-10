#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary-tree.h"
#include "../utils.h"

typedef enum color { RED, BLACK } color_t;
char* colour_t_print(color_t color){
  switch (color){
    case RED: return "RED";
    case BLACK: return "BLACK";
    default: return "UNKNOWN";
  }
}
typedef enum derection { LEFT, RIGHT } direction_t;

struct tree {
  void* data;
  size_t data_size;
  struct tree *left;
  struct tree *right;
  struct tree *parent;
  size_t size;
  color_t color;
};

size_t get_size(tree_t *tree){
  if (tree == NULL){
    return 0;
  } else {
    return tree->size;
  }
}

bool is_red(tree_t *tree){
  return tree != NULL && tree->color == RED;
}

bool is_black(tree_t *tree){
  return tree == NULL || tree->color == BLACK;
}

size_t _get_black_height(tree_t *tree, bool root){
  
  size_t black_height = _get_black_height(tree->left, false)
    + _get_black_height(tree->right, false);
  
  if (is_black(tree) && !root){
    return black_height + 1;
  }
  return black_height; 
}

size_t get_black_height(tree_t *tree){
  return _get_black_height(tree, true); 
}

tree_t* rotate(tree_t *tree, direction_t direction){
  printf("ROTATE: will print tree...\n");
  tree_printf(tree, stringify);
  tree_t *new_parent, *demoted_child, *new_grandchild;
  bool left_parent = tree->parent != NULL && tree->parent->left == tree;

  demoted_child = tree;
  if (direction == LEFT){
    new_parent = tree->right;
    new_grandchild = new_parent->left;

    new_parent->left = demoted_child;
    demoted_child->right = new_grandchild;

  } else {
    new_parent = tree->left;
    new_grandchild = new_parent->right;

    new_parent->right = demoted_child;
    demoted_child->left = new_grandchild;
  }

  new_parent->parent = demoted_child->parent;
  demoted_child->parent = new_parent;

  if (new_parent->parent == NULL){
    return new_parent;
  }

  if (left_parent){
    new_parent->parent->left = new_parent;
  } else {
    new_parent->parent->right = new_parent;
  }

  return new_parent;

}

tree_t* fix(tree_t *tree){
  if(tree == NULL){
    return tree;
  }

  tree->left = fix(tree->left);
  tree->right = fix(tree->right);

  if(tree->parent == NULL){
    fprintf(stderr, "FIX: tree is root\n");
    tree->color = BLACK;
  }

  tree_t *new_root;

  if (is_red(tree->left) && is_red(tree->left->right)){
    printf("LR\n");
    if (is_red(tree->right)){
      tree->left->color = BLACK;
      tree->right->color = BLACK;
    } else {
      new_root = rotate((rotate(tree->left, LEFT)->parent), RIGHT);
      new_root->right->color = RED;
    }
  } else if (is_red(tree->left) && is_red(tree->left->left)){
    printf("LL\n");
    new_root = rotate(tree->parent, RIGHT);
    new_root->right->color = RED;
  } else if (is_red(tree->right) && is_red(tree->right->right)){
    printf("RR\n");
    new_root = rotate(tree->parent, LEFT);
    new_root->left->color = RED;
  } else if (is_red(tree->right) && is_red(tree->right->left)){
    printf("RL\n");
    if (is_red(tree->left)){
      tree->left->color = BLACK;
      tree->right->color = BLACK;
    } else {
      new_root = rotate((rotate(tree->right, RIGHT)->parent), LEFT);
      new_root->left->color = RED;
    }
  } else {
    tree->size = get_size(tree->left) + get_size(tree->right) + 1;
    return tree;
  }
  new_root->color = BLACK;

  // recalc size
  if (new_root->left != NULL){
    new_root->left->size = get_size(new_root->left->left) + get_size(new_root->left->right) + 1;  
  }
  if (new_root->right != NULL){
    new_root->right->size = get_size(new_root->right->left) + get_size(new_root->right->right) + 1;  
  }
  new_root->size = get_size(new_root->left) + get_size(new_root->right) + 1;
  
  return new_root;
}

tree_t* _insert(void* data, size_t data_size, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t)){
  if (tree == NULL){
    tree_t *ret = malloc(sizeof(tree_t));
    ret->data = data;
    ret->data_size = data_size;
    ret->left = NULL;
    ret->right = NULL;
    ret->size = 1;
    ret->color = BLACK;
    ret->parent = NULL;
    return ret;
  }

  int result = cmp(data, data_size, tree->data, tree->data_size);
  if (result < 0){
    size_t old_subtree_size = get_size(tree->left);
    tree->left = _insert(data, data_size, tree->left, cmp);
    tree->left->parent = tree;
    if (tree->left->left == NULL && tree->left->right == NULL){
      tree->left->color = RED;
    }
    if (old_subtree_size != get_size(tree->left)){
      tree->size = 1 + get_size(tree->left) + get_size(tree->right);
    }
  }
  if (result > 0){
    size_t old_subtree_size = get_size(tree->right);
    tree->right = _insert(data, data_size, tree->right, cmp);
    tree->right->parent = tree;
    if (tree->right->left == NULL && tree->right->right == NULL){
      tree->right->color = RED;
    }
    if (old_subtree_size != get_size(tree->right)){
      tree->size = 1 + get_size(tree->left) + get_size(tree->right);
    }
  }
  // if result == 0, ignore
  return tree;
}

tree_t* insert(void* data, size_t data_size, tree_t *tree, int (*cmp)(void*, size_t, void*, size_t)){
    return fix(_insert(data, data_size, tree, cmp));
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

  fprintf(file,"tree[%p]: { data: \"%s\", left[%p], right[%p], parent[%p],"
          " size[%lu], color[%s] }\n",
          (void *) tree, stringify(tree->data, tree->data_size),
          (void *) tree->left, (void *)  tree->right, (void *)  tree->parent,
          tree->size, colour_t_print(tree->color));
  return ftree_printf(file, tree->left, stringify)
    || ftree_printf(file, tree->right, stringify);
}

int tree_printf(tree_t *tree, char* (*stringify)(void*, size_t)){
  return ftree_printf(stdout, tree, stringify);
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
