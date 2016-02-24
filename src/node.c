#include <stdlib.h>
#include "node.h"

struct node *node_new(void *value) {
  struct node *node = malloc(sizeof(*node));
  node->value = value;
  node->next = 0;
  node->prev = 0;
  return node;
}
