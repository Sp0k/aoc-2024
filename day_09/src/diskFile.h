#ifndef DISK_FILE_H
#define DISK_FILE_H

#include <stdlib.h>

typedef struct DiskFile {
  int id;
  int size;
  struct DiskFile *prev;
  struct DiskFile *next;
} DiskFile;

typedef struct {
  DiskFile *head;
  DiskFile *tail;
  int size;
} LinkedList;

LinkedList *createList(DiskFile *head);
void addFile(DiskFile *newFile, LinkedList *list);
DiskFile *getFile(int id, LinkedList *list);

#endif // !DISK_FILE_H
