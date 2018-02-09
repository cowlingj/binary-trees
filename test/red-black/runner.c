#include <stdio.h>
#include "../../src/red-black/binary-tree.h"
#include "../../src/utils.h"

tree_t *tree = NULL;

int main(int argc, char** argv){
  tree = insert("hello", sizeof(char*), tree, cmp);
  tree = insert("world", sizeof(char*), tree, cmp);
  tree = insert("here's jonny", sizeof(char*), tree, cmp);
  get("blah", sizeof(char*), tree, cmp);
  tree_printf(tree, stringify);

  printf("REMOVE \"world\"\n");
  tree_remove("world", sizeof(char*), tree, cmp);
  tree_printf(tree, stringify);

  printf("REMOVE \"hello\"\n");
  tree_remove("hello", sizeof(char*), tree, cmp);
  tree_printf(tree, stringify);
}
