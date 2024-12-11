#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Please specify the input file\n");
    return EXIT_FAILURE;
  }

  char *filename = argv[1];
  char *path = "../resources/";
  char filepath[32];
  strcpy(filepath, path);
  strcat(filepath, filename);

  FILE *input = fopen(filepath, "r");
  if (!input) {
    fprintf(stderr, "Could not open input file");
    return EXIT_FAILURE;
  }

  char *buffer = 0;

  fseek(input, 0, SEEK_END);
  int length = ftell(input);
  fseek(input, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * (length + 1));
  fread(buffer, 1, length, input);
  buffer[length] = '\0';

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
  for (int i = 0; i < lineCounter; i++) {
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
  }

  printf("%d reports are safe!\n", safeCounter);

  return EXIT_SUCCESS;
}
