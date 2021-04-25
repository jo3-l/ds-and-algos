#include "singly_linked_list.h"

#include <stdbool.h>
#include <stdlib.h>

LinkedList* ll_new() {
  LinkedList* list = malloc(sizeof(LinkedList));
  if (!list) return NULL;
  list->head = NULL;
  list->size = 0;
  return list;
}

bool ll_insert_after(LinkedList* list, LinkedListNode* node, void* element) {
  LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
  if (!new_node) return false;

  new_node->value = element;
  new_node->next = node->next;
  node->next = new_node;
  ++list->size;
  return true;
}

bool ll_push_front(LinkedList* list, void* element) {
  LinkedListNode* node = malloc(sizeof(LinkedListNode));
  if (!node) return false;

  node->value = element;
  node->next = list->head;
  list->head = node;
  ++list->size;

  return true;
}

void* ll_get_first(LinkedList* list) {
  if (!list->head) return NULL;
  return list->head->value;
}

void* ll_remove_first(LinkedList* list) {
  LinkedListNode* head = list->head;
  if (!head) return;
  list->head = head->next;
  --list->size;
  void* value = head->value;
  free(head);
  return value;
}

void* ll_remove_after(LinkedList* list, LinkedListNode* node) {
  if (!node->next) return NULL;
  void* value = node->next->value;
  LinkedListNode* next_next_node = node->next->next;
  free(node->next);
  node->next = next_next_node;
  --list->size;
  return value;
}

void ll_foreach(LinkedList* list, bool iteratee(void* element)) {
  for (LinkedListNode* node = list->head; node != NULL; node = node->next) {
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