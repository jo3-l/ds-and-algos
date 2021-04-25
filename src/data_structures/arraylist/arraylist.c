#include "arraylist.h"

#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

ArrayList* arraylist_new(int initial_capacity) {
  void** buckets = malloc(initial_capacity * sizeof(void*));
  ArrayList* list = malloc(sizeof(ArrayList));
  list->buckets = buckets;
  list->capacity = initial_capacity;
  list->size = 0;
  return list;
}

bool arraylist_insert_before(ArrayList* list, int index, void* element) {
  if (list->capacity == list->size) {
    list->capacity *= 2;
    bool ok = arraylist_realloc(list);
    if (!ok) return false;
  }

  ++list->size;
  // originally empty array / index -1 (set last element)
  if (list->size == 1 || index == -1) {
    list->buckets[list->size - 1] = element;
    // nothing else to do.
    return true;
  }

  // otherwise, shift the array forward.
  memmove(list->buckets + index + 1, list->buckets + index,
          (list->size - index - 1) * sizeof(void*));
  list->buckets[index] = element;
  return true;
}

bool arraylist_push_back(ArrayList* list, void* element) {
  return arraylist_insert_before(list, -1, element);
}

bool arraylist_push_front(ArrayList* list, void* element) {
  return arraylist_insert_before(list, 0, element);
}

bool arraylist_remove_at(ArrayList* list, int index) {
  list->buckets[index] = NULL;
  --list->size;
  // nothing more to do if it's the last index
  if (index == list->size) {
    return true;
  }

  memmove(list->buckets + index, list->buckets + index + 1,
          list->size * sizeof(void*));

  // resize array if the number of used buckets is less than half the total.
  // don't resize if the array capacity is less than 4, to combat constant
  // resizing.
  if (list->capacity > 8 && list->size < (list->capacity / 2)) {
    list->capacity /= 2;
    return arraylist_realloc(list);
  }

  return true;
}

bool arraylist_remove_back(ArrayList* list) {
  return arraylist_remove_at(list, list->size - 1);
}

bool arraylist_remove_front(ArrayList* list) {
  return arraylist_remove_at(list, 0);
}

void arraylist_foreach(ArrayList* list, bool iteratee(void* element)) {
  for (int i = 0; i < list->size; i++) {
    bool should_break = iteratee(list->buckets[i]);
    if (should_break) break;
  }
}

void arraylist_free(ArrayList* list) { free(list); }

bool arraylist_realloc(ArrayList* list) {
  void** new_buckets = realloc(list->buckets, list->capacity * sizeof(void*));
  if (!new_buckets) {
    // If realloc failed, free the original pointer
    free(list->buckets);
    return false;
  }
  list->buckets = new_buckets;
  return true;
}
