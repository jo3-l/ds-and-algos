#include <stdbool.h>

typedef struct linked_list_node {
  struct linked_list_node* next;
  void* value;
} LinkedListNode;

typedef struct linked_list {
  LinkedListNode* head;
  int size;
} LinkedList;

LinkedList* ll_new();

bool ll_insert_after(LinkedList* list, LinkedListNode* node, void* element);

bool ll_push_front(LinkedList* list, void* element);

void* ll_get_first(LinkedList* list);

void* ll_remove_first(LinkedList* list);

void* ll_remove_after(LinkedList* list, LinkedListNode* node);

void ll_foreach(LinkedList* list, bool iteratee(void* element));

void ll_free(LinkedList* list);