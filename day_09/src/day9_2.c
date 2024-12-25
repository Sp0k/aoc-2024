#include "../../lib/fileReaderLib.h"
#include "diskFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  // Check the input is included
  if (argc != 2) {
    fprintf(stderr, "Please include your input file");
    exit(EXIT_FAILURE);
  }

  // Get file path
  char *filename = argv[1];
  char *path = "../resources/";
  char filepath[32];
  strcpy(filepath, path);
  strcat(filepath, filename);

  // Read file
  char *data = readFileData(filepath);

  // Initialize the file counter to 0
  int fileCounter = 0;

  // Create the List of disk files
  DiskFile *head = malloc(sizeof(DiskFile));
  head->id = fileCounter;
  head->size = data[0] - '0';
  head->prev = NULL;
  head->next = NULL;
  LinkedList *list = createList(head);

  // Update file counter
  fileCounter++;

  // Fill the list
  for (int i = 1; i < strlen(data); i++) {
    DiskFile *tmp = malloc(sizeof(DiskFile));

    if (i % 2 == 0) {
      tmp->id = fileCounter;
      fileCounter++;
    } else {
      tmp->id = -1;
    }

    tmp->size = data[i] - '0';
    tmp->prev = tmp->next = NULL;

    addFile(tmp, list);
  }

  // Reorganize the disk
  DiskFile *currFile = list->tail;
  while (currFile != NULL && currFile->id != 0) {
    if (currFile->id != -1) {
      DiskFile *filePtr = list->head;
      DiskFile *nextFile = currFile->prev;

      while (filePtr != NULL && filePtr != currFile) {
        if (filePtr->id == -1) {
          if (currFile->size < filePtr->size) {
            DiskFile *newSpace = malloc(sizeof(DiskFile));
            newSpace->id = -1;
            newSpace->size = currFile->size;

            newSpace->prev = currFile->prev;
            newSpace->next = currFile->next;

            if (currFile == list->tail) {
              list->tail = newSpace;
            }

            if (newSpace->prev != NULL)
              newSpace->prev->next = newSpace;

            if (newSpace->next != NULL)
              newSpace->next->prev = newSpace;

            filePtr->size -= currFile->size;
            currFile->prev = filePtr->prev;

            if (currFile->prev != NULL)
              currFile->prev->next = currFile;

            currFile->next = filePtr;
            filePtr->prev = currFile;

            currFile = nextFile->next;
            break;
          } else if (currFile->size == filePtr->size) {
            DiskFile *tmpPrev = currFile->prev;
            DiskFile *tmpNext = currFile->next;

            currFile->prev = filePtr->prev;
            if (currFile->prev != NULL)
              currFile->prev->next = currFile;

            currFile->next = filePtr->next;
            if (currFile->next != NULL)
              currFile->next->prev = currFile;

            filePtr->prev = tmpPrev;
            if (filePtr->prev != NULL)
              filePtr->prev->next = filePtr;

            filePtr->next = tmpNext;
            if (filePtr->next != NULL)
              filePtr->next->prev = filePtr;

            if (currFile == list->tail)
              list->tail = filePtr;

            currFile = nextFile->next;
            break;
          }
        }

        filePtr = filePtr->next;
      }
    }

    currFile = currFile->prev;
    printf(".");
    fflush(stdout);
  }
  printf("\n\n");

  // Checksum Calculation
  int sum = 0;
  int idx = 0;

  DiskFile *ptr = list->head;
  while (ptr != NULL) {
    if (ptr->id != -1) {
      for (int i = 0; i < ptr->size; i++) {
        sum += (ptr->id * idx);
        idx++;
      }
    } else {
      idx += ptr->size;
    }

    ptr = ptr->next;
  }

  // Output
  printf("The resulting filesystem checksum is %d\n", sum);

  return EXIT_SUCCESS;
}
