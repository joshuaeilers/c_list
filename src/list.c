#include <stdlib.h>
#include "list.h"

static struct node *node_new(void *value);
static struct node *list_find_node(struct list *this, int index);

static struct node *node_new(void *value) {
  struct node *node = malloc(sizeof(*node));
  node->value = value;
  node->next = 0;
  node->prev = 0;
  return node;
}

struct list *list_new() {
  struct list *this = malloc(sizeof(*this));
  this->head = 0;
  this->tail = 0;
  this->size = 0;
  return this;
}

static struct node *list_find_node(struct list *this, int index) {
  if (index >= this->size || index < 0) {
    return 0;
  }

  struct node *node = this->head;
  int mid = this->size >> 1;

  if (index > mid) {
    index = this->size - index - 1;
    node = this->tail;
    while (index--) {
      node = node->prev;
    }
  } else {
    while (index--) {
      node = node->next;
    }
  }

  return node;
}

void list_push(struct list *this, void *value) {
  struct node *node = node_new(value);

  if (this->size) {
    node->prev = this->tail;
    this->tail->next = node;
  } else {
    this->head = node;
  }

  this->tail = node;
  ++this->size;
}

void *list_pop(struct list *this) {
  if (!this->size) {
    return 0;
  }

  struct node *n = this->tail;
  void *value = n->value;

  if (--this->size) {
    this->tail = n->prev;
    this->tail->next = 0;
  } else {
    this->head = 0;
    this->tail = 0;
  }

  free(n);

  return value;
}

void *list_get(struct list *this, int index) {
  struct node *node = list_find_node(this, index);

  if (!node) {
    return 0;
  }

  return node->value;
}

void *list_remove(struct list *this, int index) {
  struct node *node = list_find_node(this, index);

  if (!node) {
    return 0;
  }

  void *value = node->value;

  if (node->prev) {
    node->prev->next = node->next;
  } else {
    this->head = node->next;
  }

  if (node->next) {
    node->next->prev = node->prev;
  } else {
    this->tail = node->prev;
  }

  --this->size;
  free(node);
  return value;
}

void list_each(struct list *this, void lambda(void *value)) {
  if (!this->size) {
    return;
  }

  struct node *cur = this->head;

  while (cur) {
    lambda(cur->value);
    cur = cur->next;
  }
}

void list_free(struct list *this) {
  struct node *cur = this->head;
  struct node *next;

  while (cur) {
    next = cur->next;
    free(cur);
    cur = next;
  }

  free(this);
}
