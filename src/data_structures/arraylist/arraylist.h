#include <stdbool.h>

typedef struct arraylist {
  void** buckets;
  int capacity;
  int size;
} ArrayList;

ArrayList* arraylist_new(int initial_size);

bool arraylist_insert_before(ArrayList* list, int index, void* element);

bool arraylist_push_back(ArrayList* list, void* element);

bool arraylist_push_front(ArrayList* list, void* element);

bool arraylist_remove_at(ArrayList* list, int index);

bool arraylist_remove_back(ArrayList* list);

bool arraylist_remove_front(ArrayList* list);

void arraylist_foreach(ArrayList* list, bool iteratee(void* element));

void arraylist_free(ArrayList* list);

bool arraylist_realloc(ArrayList* list);