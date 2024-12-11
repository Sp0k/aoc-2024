#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  // Check input is specified
  if (argc < 2) {
    fprintf(stderr, "Please specify the input file\n");
    return EXIT_FAILURE;
  }

  // Create file path
  char *filename = argv[1];
  char *path = "../resources/";
  char filepath[32];
  strcpy(filepath, path);
  strcat(filepath, filename);

  // Open file
  FILE *input = fopen(filepath, "r");
  if (!input) {
    fprintf(stderr, "Could not open input file");
    return EXIT_FAILURE;
  }

  // Read file
  char *buffer = 0;
  fseek(input, 0, SEEK_END);
  int length = ftell(input);
  fseek(input, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * (length + 1));
  fread(buffer, 1, length, input);
  buffer[length] = '\0';

  // Close file when done
  fclose(input);


  char *token = strtok(buffer, "\n");
  char **lines = malloc(sizeof(char *));
  int lineCounter = 0;
  while (token != NULL) {
    if (lineCounter > 0)
      lines = realloc(lines, sizeof(char *) * (lineCounter + 1));
    
    lines[lineCounter] = strdup(token);
    lineCounter++;

    token = strtok(NULL, "\n");
  }

  int safeCounter = 0;
  char **unsafeReports = malloc(sizeof(char *) * lineCounter);
  int unsafeCounter;
  for (int i = 0; i < lineCounter; i++) {
    unsafeReports[unsafeCounter] = strdup(lines[i]);
    token = strtok(lines[i], " ");
    int prevNum = atoi(token);
    token = strtok(NULL, " ");
    
    int diff = 0;
    int isValid = 1;
    int change = 0; // 1: increase, 2: decrease

    while (token != NULL) {
      int nextNum = atoi(token);
      diff = prevNum - nextNum;
      prevNum = nextNum;

      if (abs(diff) > 3 || diff == 0) {
        isValid = 0;
        break;
      }

      if (change == 0)
        change = (diff < 0) ? 1 : 2;
      else if ((change == 1 && diff > 0) || (change == 2 && diff < 0)) {
        isValid = 0;
        break;
      }

      token = strtok(NULL, " ");
    }

    if (isValid)
      safeCounter++;
    else
      unsafeCounter++;
  }

  for (int i = 0; i < unsafeCounter; i++) {
    int *arr = malloc(sizeof(int));
    int arrCounter = 0;

    token = strtok(unsafeReports[i], " ");
    while (token != NULL) {
      if (arrCounter >= 1)
        arr = realloc(arr, sizeof(int) * (arrCounter + 1));

      arr[arrCounter] = atoi(token);
      arrCounter++;

      token = strtok(NULL, " ");
    }

    for (int j = 0; j < arrCounter; j++) {
      int diff = 0;
      int isValid = 1;
      int change = 0; // 1: increase, 2: decrease
      int prevNum = -1;

      for (int k = 0; k < arrCounter; k++) {
        if (k == j)
          continue;

        if (prevNum == -1) {
          prevNum = arr[k];
          continue;
        }

        int nextNum = arr[k];
        diff = prevNum - nextNum;
        prevNum = nextNum;

        if (abs(diff) > 3 || diff == 0) {
          isValid = 0;
          break;
        }

        if (change == 0)
          change = (diff < 0) ? 1 : 2;
        else if ((change == 1 && diff > 0) || (change == 2 && diff < 0)) {
          isValid = 0;
          break;
        }
      }

      if (isValid) {
        safeCounter++;
        break;
      }
    }
  }

  printf("%d reports are safe!\n", safeCounter);

  return EXIT_SUCCESS;
}
