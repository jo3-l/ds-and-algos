#include <stdbool.h>

typedef struct linked_list_node {
  struct linked_list_node* next;
  struct linked_list_node* prev;
  void* value;
} LinkedListNode;

typedef struct linked_list {
  LinkedListNode* head;
  LinkedListNode* tail;
  int size;
} LinkedList;

LinkedList* ll_new();

bool ll_insert_before(LinkedList* list, LinkedListNode* node, void* element);

bool ll_insert_after(LinkedList* list, LinkedListNode* node, void* element);

bool ll_push_back(LinkedList* list, void* element);

bool ll_push_front(LinkedList* list, void* element);

void* ll_get_first(LinkedList* list);

void* ll_remove_first(LinkedList* list);

void* ll_get_last(LinkedList* list);

void* ll_remove_last(LinkedList* list);

void* ll_remove_after(LinkedList* list, LinkedListNode* node);

void* ll_remove_before(LinkedList* list, LinkedListNode* node);

void ll_foreach(LinkedList* list, bool iteratee(void* element));

void ll_foreach_reverse(LinkedList* list, bool iteratee(void* element));

void ll_free(LinkedList* list);
