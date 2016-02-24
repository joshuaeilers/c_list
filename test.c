#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "src/list.h"

void test_list_push() {
  struct list *list = list_new();
  int x = 1;
  int y = 2;
  int z = 3;

  assert(list->size == 0);

  list_push(list, &x);
  assert(list->size == 1);

  list_push(list, &y);
  assert(list->size == 2);

  list_push(list, &z);
  assert(list->size == 3);

  list_free(list);
}

void test_list_pop() {
  struct list *list = list_new();
  int x = 1;
  int y = 2;
  int z = 3;

  list_push(list, &x);
  list_push(list, &y);
  list_push(list, &z);

  assert(list_pop(list) == &z);
  assert(list->size == 2);

  assert(list_pop(list) == &y);
  assert(list->size == 1);

  assert(list_pop(list) == &x);
  assert(list->size == 0);

  assert(!list_pop(list));

  list_free(list);
}

void test_list_get() {
  struct list *list = list_new();
  int x = 1;
  int y = 2;
  int z = 3;

  assert(!list_get(list, 0));

  list_push(list, &x);
  list_push(list, &y);
  list_push(list, &z);

  assert(list_get(list, 0) == &x);
  assert(list_get(list, 1) == &y);
  assert(list_get(list, 2) == &z);

  list_free(list);
}

void test_list_remove() {
  struct list *list = list_new();
  int x = 1;
  int y = 2;
  int z = 3;

  assert(!list_remove(list, 0));

  list_push(list, &x);
  list_push(list, &y);
  list_push(list, &z);

  assert(list_remove(list, 2) == &z);
  assert(list->size == 2);

  assert(list_remove(list, 1) == &y);
  assert(list->size == 1);

  assert(list_remove(list, 0) == &x);
  assert(list->size == 0);

  list_free(list);
}

void lambda(void *value) {
  ++*(int *) value;
}

void test_list_each() {
  struct list *list = list_new();
  int x = 1;
  int y = 2;
  int z = 3;
  list_push(list, &x);
  list_push(list, &y);
  list_push(list, &z);
  list_each(list, lambda);
  assert(*(int *) list_get(list, 0) == 2);
  assert(*(int *) list_get(list, 1) == 3);
  assert(*(int *) list_get(list, 2) == 4);

  list_free(list);
}

void custom_list_free(void *value) {
  *(int *) value = 42;
}

void test_list_free() {
  struct list *list = list_new();
  int *x = malloc(sizeof(*x));
  *x = 1337;
  list_push(list, x);

  list->free = custom_list_free;

  list_free(list);

  assert(*x == 42);
}

int main() {
  test_list_push();
  test_list_pop();
  test_list_get();
  test_list_remove();
  test_list_each();
  test_list_free();

  puts("All tests succeded!");
  return 0;
}
