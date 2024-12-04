#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to keep track of repeating integers
typedef struct {
  int num;
  int numOfAppearance;
} Number;

// Number variables
Number *numbers;
int diffCounter = 0;

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
        free(numbers);
        exit(EXIT_FAILURE);
      }
      listA = tmpListA;

      int *tmpListB = realloc(listB, sizeof(int) * newSize);
      if (!tmpListB) {
        perror("Failed to realloc list B");
        free(listA);
        free(listB);
        free(numbers);
        exit(EXIT_FAILURE);
      }
      listB = tmpListB;
    }

    // Read the lists
    sscanf(line, "%d\t%d", &listA[counter], &listB[counter]);

    // Check if this is the first integer seen
    if (diffCounter <= 0) {
      // Add the first to the number array
      Number firstNumber = {listB[0], 1};
      numbers[0] = firstNumber;
      diffCounter++;
    } else {
      // Check if the integer has already been seen
      int foundFlag = 0;
      for (int i = 0; i < diffCounter; i++) {
        // Update the number of appearances
        if (listB[counter] == numbers[i].num) {
          numbers[i].numOfAppearance++;
          foundFlag = 1;
          break;
        }
      }

      // Check if the integer has been found
      if (!foundFlag) {
        // Reallocate the number array for the new integer
        Number *tmpNumbers =
            realloc(numbers, sizeof(Number) * (diffCounter + 1));
        if (!tmpNumbers) {
          perror("Failed to realloc numbers");
          fclose(input);
          free(listA);
          free(listB);
          free(numbers);
        }
        numbers = tmpNumbers;

        // Add the new integer to the array
        Number newNumber = {listB[counter], 1};
        numbers[diffCounter] = newNumber;
        diffCounter++;
      }
    }

    counter++;
  }

  fclose(input);
}

/**
 * @brief Main function of the program
 *
 * The main functions builds the two lists from the input and tracks how many
 * time each integers in list B is seen. Then it sets up parameters to split
 * List A to calculate the total amount of time each integers has been seen and
 * displaying the result.
 */
int main(int argc, char **argv) {
  // Allocate memory for the lists
  listA = malloc(sizeof(int) * DEFAULT_LIST_SIZE);
  listB = malloc(sizeof(int) * DEFAULT_LIST_SIZE);
  numbers = malloc(sizeof(Number));

  // Fetch and build the file path from the program's argument
  char *file = argv[1];
  char *pathStart = "../resources/";
  char filepath[32];
  strcpy(filepath, pathStart);
  strcat(filepath, file);

  // Read the input file
  readFile(filepath);

  // Calculate the total similarity score
  int total = 0;
  for (int i = 0; i < counter; i++) {
    int numOfAppearances = 0;

    for (int j = 0; j < diffCounter; j++) {
      if (listA[i] == numbers[j].num) {
        numOfAppearances = numbers[j].numOfAppearance;
        break;
      }
    }

    total += (listA[i] * numOfAppearances);
  }
  printf("The similarity score is: %d!\n", total);

  // Free memory
  free(numbers);
  free(listB);
  free(listA);

  return EXIT_SUCCESS;
}
