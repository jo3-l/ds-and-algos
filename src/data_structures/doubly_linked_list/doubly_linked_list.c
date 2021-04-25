#include "doubly_linked_list.h"

#include <stdbool.h>
#include <stdlib.h>

LinkedList* ll_new() {
  LinkedList* list = malloc(sizeof(LinkedList));
  if (!list) return NULL;

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

bool ll_insert_before(LinkedList* list, LinkedListNode* node, void* element) {
  LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
  if (!new_node) return false;

  new_node->next = node;
  new_node->prev = node->prev;
  new_node->value = element;

  if (node->prev && node->prev->prev) node->prev->prev->next = new_node;
  node->prev = new_node;

  ++list->size;
  return true;
}

bool ll_insert_after(LinkedList* list, LinkedListNode* node, void* element) {
  LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
  if (!new_node) return false;

  new_node->prev = node;
  new_node->next = node->next;
  new_node->value = element;

  if (node->next && node->next->next) node->next->next->prev = new_node;
  node->next = new_node;

  ++list->size;
  return true;
}

bool ll_push_back(LinkedList* list, void* element) {
  LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
  if (!new_node) return false;

  new_node->prev = list->tail;
  new_node->next = NULL;
  new_node->value = element;

  if (list->tail) list->tail->next = new_node;
  list->tail = new_node;

  ++list->size;
  return true;
}

bool ll_push_front(LinkedList* list, void* element) {
  LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
  if (!new_node) return false;

  new_node->next = list->head;
  new_node->prev = NULL;
  new_node->value = element;

  if (list->head) list->head->prev = new_node;
  list->head = new_node;

  ++list->size;
  return true;
}

void* ll_get_first(LinkedList* list) {
  if (!list->head) return NULL;
  return list->head->value;
}

void* ll_remove_first(LinkedList* list) {
  if (!list->head) return NULL;
  void* value = list->head->value;
  LinkedListNode* next_node = list->head->next;

  free(list->head);
  list->head = next_node;
  if (next_node) next_node->prev = NULL;

  --list->size;
  return value;
}

void* ll_get_last(LinkedList* list) {
  if (!list->tail) return NULL;
  return list->tail->value;
}

void* ll_remove_last(LinkedList* list) {
  if (!list->tail) return NULL;
  void* value = list->tail->value;
  LinkedListNode* prev_node = list->tail->prev;

  free(list->tail);
  list->tail = prev_node;
  if (prev_node) prev_node->next = NULL;

  --list->size;
  return value;
}

void* ll_remove_after(LinkedList* list, LinkedListNode* node) {
  if (!node->next) return NULL;
  void* value = node->next->value;
  LinkedListNode* next_next_node = node->next->next;

  free(node->next);
  if (next_next_node) next_next_node->prev = node;
  node->next = next_next_node;

  --list->size;
  return value;
}

void* ll_remove_before(LinkedList* list, LinkedListNode* node) {
  if (!node->prev) return NULL;
  void* value = node->prev->value;
  LinkedListNode* prev_prev_node = node->prev->prev;

  free(node->prev);
  if (prev_prev_node) prev_prev_node->next = node;
  node->prev = prev_prev_node;

  --list->size;
  return value;
}

void ll_foreach(LinkedList* list, bool iteratee(void* element)) {
  for (LinkedListNode* node = list->head; node != NULL; node = node->next) {
    bool should_break = iteratee(node->value);
    if (should_break) break;
  }
}

void ll_foreach_reverse(LinkedList* list, bool iteratee(void* element)) {
  for (LinkedListNode* node = list->tail; node != NULL; node = node->prev) {
    bool should_break = iteratee(node->value);
    if (should_break) break;
  }
}

void ll_free(LinkedList* list) {
  LinkedListNode* node = list->head;
  while (node) {
    LinkedListNode* target = node;
    node = node->next;
    free(target);
  }

  free(list);
}