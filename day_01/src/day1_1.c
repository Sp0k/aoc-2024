#include "heapsort.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to pass parameters to the threads
typedef struct {
  int *arr;
  int counter;
  int startIndex;
  int endIndex;
} parameters;

// Thread function
void *sorter(void *params);

// List declarations
#define DEFAULT_LIST_SIZE 256
int *listA, *listB;
int counter = 0;

/**
 * @brief Reads in the input file
 *
 * This function reads in the input file from the file path passed in. It then
 * places each integers into the correct list before closing the file.
 */
void readFile(char *filepath) {
  // Open input file
  FILE *input = fopen(filepath, "r");
  if (!input) {
    perror("Failed to read input file");
    exit(EXIT_FAILURE);
  }

  // Read input
  char line[32];
  while (fgets(line, sizeof(line), input)) {
    // Reallocate the lists if the lists are longer than expected
    if (counter >= DEFAULT_LIST_SIZE) {
      int newSize = counter + 1;

      int *tmpListA = realloc(listA, sizeof(int) * newSize);
      if (!tmpListA) {
        perror("Failed to realloc list A");
        free(listA);
        free(listB);
        exit(EXIT_FAILURE);
      }
      listA = tmpListA;

      int *tmpListB = realloc(listB, sizeof(int) * newSize);
      if (!tmpListB) {
        perror("Failed to realloc list B");
        free(listA);
        free(listB);
        exit(EXIT_FAILURE);
      }
      listB = tmpListB;
    }

    // Read the lists
    sscanf(line, "%d\t%d", &listA[counter], &listB[counter]);
    counter++;
  }

  fclose(input);
}

/**
 * @brief Main function of the program
 *
 * The main functions builds the two lists from the input, sets their parameters
 * up and creates two threads to simultaneously sort the lists. It then
 * calculates the total distance between each pair of smallest integers before
 * printing the result.
 */
int main(int argc, char **argv) {
  // Allocate memory for the lists
  listA = malloc(sizeof(int) * DEFAULT_LIST_SIZE);
  listB = malloc(sizeof(int) * DEFAULT_LIST_SIZE);

  char *file = argv[1];
  char *pathStart = "../resources/";
  char filepath[32];
  strcpy(filepath, pathStart);
  strcat(filepath, file);

  // Read the input file
  readFile(filepath);

  // Set the parameters for threading the lists
  parameters *pA = malloc(sizeof(parameters));
  pA->arr = listA;
  pA->counter = counter;

  parameters *pB = malloc(sizeof(parameters));
  pB->arr = listB;
  pB->counter = counter;

  pthread_t tidA, tidB;

  // Create the threads to sort the lists
  pthread_create(&tidA, NULL, sorter, (void *)pA);
  pthread_create(&tidB, NULL, sorter, (void *)pB);

  // Wait for the threads to finish
  pthread_join(tidA, NULL);
  pthread_join(tidB, NULL);

  // Free parameters' memory after use
  free(pA);
  free(pB);

  // Calculate total distance between each pair
  int totalDistances = 0;
  for (int i = 0; i < counter; i++)
    totalDistances += abs(listA[i] - listB[i]);

  // Result
  printf("The total distance between both lists is: %d!\n", totalDistances);

  // Free memory
  free(listA);
  free(listB);

  return EXIT_SUCCESS;
}

/**
 * @brief Thread function to sort the lists
 *
 * This function is assigned to each thread and used to simultaneously sort the
 * lists using heap sort.
 *
 * @param params A void variable used to pass the parameters to the thread
 */
void *sorter(void *params) {
  // Classify the params as parameters
  parameters *p = (parameters *)params;

  // Sort the list
  heapsort(p->arr, p->counter);

  pthread_exit(EXIT_SUCCESS);
}
