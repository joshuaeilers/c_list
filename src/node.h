#ifndef _NODE_H_
#define _NODE_H_

struct node {
  struct node *next;
  struct node *prev;
  void *value;
};

struct node *node_new(void *value);

#endif