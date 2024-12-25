#include "diskFile.h"

LinkedList *createList(DiskFile *head) {
  LinkedList *list = malloc(sizeof(LinkedList));

  list->head = head;
  list->tail = head;
  list->size = 1;

  return list;
}

void addFile(DiskFile *newFile, LinkedList *list) {
  newFile->prev = list->tail;
  newFile->prev->next = newFile;
  newFile->next = NULL;
  list->tail = newFile;

  list->size++;
}

DiskFile *getFile(int id, LinkedList *list) {
  DiskFile *ptr = list->head;

  while (ptr != NULL) {
    if (ptr->id == id)
      return ptr;

    ptr = ptr->next;
  }

  return NULL;
}
