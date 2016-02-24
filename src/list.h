#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

struct node {
  struct node *next;
  struct node *prev;
  void *value;
};

struct list {
  struct node *head;
  struct node *tail;
  void (*free)(void *value);
  size_t size;
};

struct list *list_new();
void list_push(struct list *this, void *value);
void *list_pop(struct list *this);
void *list_get(struct list *this, size_t index);
void *list_remove(struct list *this, size_t index);
void list_each(struct list *this, void (*lambda)(void *value));
void list_free(struct list *this);

#endif
