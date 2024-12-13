#include "../../lib/fileReaderLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findXMAS(char **wordSearch, int count) {
  char *regex = "XMAS";
  int sum = 0;

  // Left to right
  for (int i = 0; i < count; i++) {
    char *tmp = strdup(wordSearch[i]);

    char *ptr = strstr(tmp, regex);
    while (ptr) {
      sum++;
      ptr[0] = '.';
      tmp = ptr;
      ptr = strstr(tmp, regex);
    }
  }

  // Right to left
  for (int i = 0; i < count; i++) {
    char *tmp = strdup(wordSearch[i]);
    strrev(tmp);

    char *ptr = strstr(tmp, regex);
    while (ptr) {
      sum++;
      ptr[0] = '.';
      tmp = ptr;
      ptr = strstr(tmp, regex);
    }
  }

  return sum;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Please include the input file");
    exit(EXIT_FAILURE);
  }

  char *path = "../resources/";
  char filepath[64];
  strcpy(filepath, path);
  strcat(filepath, argv[1]);

  char *data = readFileData(filepath);
  printf("WORD SEARCH:\n\n%s\n", data);

  char *token = strtok(data, "\n");
  char **wordSearch = malloc(sizeof(char *));

  int lineCounter = 0;
  while (token != NULL) {
    if (lineCounter > 0)
      wordSearch = realloc(wordSearch, sizeof(char *) * (lineCounter + 1));

    wordSearch[lineCounter] = strdup(token);

    lineCounter++;
    token = strtok(NULL, "\n");
  }

  int sum = 0;

  // Horizontal
  sum += findXMAS(wordSearch, lineCounter);

  // Vertical
  int lineLen = strlen(wordSearch[0]);

  char **vertical = malloc(sizeof(char *) * lineLen);
  for (int i = 0; i < lineLen; i++) {
    vertical[i] = malloc(sizeof(char) * (lineCounter + 1));
    for (int j = 0; j < lineCounter; j++) {
      vertical[i][j] = wordSearch[j][i];
    }
    vertical[i][lineCounter] = '\0';
  }

  sum += findXMAS(vertical, lineLen);

  // Diagonal Left-to-Right
  int dLRCounter = 0;
  char **diagonalLR = malloc(sizeof(char *) * (lineCounter + lineLen));

  for (int i = 0; i < lineCounter; i++) {
    int x = i, y = 0;
    char tmp[lineLen + 1];
    int k = 0;

    while (x < lineCounter && y < lineLen) {
      tmp[k++] = wordSearch[x++][y++];
    }
    tmp[k] = '\0';

    if (k >= 4) {
      diagonalLR[dLRCounter] = strdup(tmp);
      dLRCounter++;
    }
  }

  for (int i = 1; i < lineLen; i++) {
    int x = 0, y = i;
    char tmp[lineLen + 1];
    int k = 0;

    while (x < lineCounter && y < lineLen) {
      tmp[k++] = wordSearch[x++][y++];
    }
    tmp[k] = '\0';

    if (k >= 4) {
      diagonalLR[dLRCounter] = strdup(tmp);
      dLRCounter++;
    }
  }

  sum += findXMAS(diagonalLR, dLRCounter);

  // Diagonal Right-to-Left
  int dRLCounter = 0;
  char **diagonalRL = malloc(sizeof(char *) * lineCounter * lineLen);

  for (int i = 0; i < lineCounter; i++) {
    int x = i, y = lineLen - 1;
    char tmp[lineLen + 1];
    int k = 0;

    while (x < lineCounter && y >= 0) {
      tmp[k++] = wordSearch[x++][y--];
    }
    tmp[k] = '\0';

    if (k >= 4) {
      diagonalRL[dRLCounter] = strdup(tmp);
      dRLCounter++;
    }
  }

  for (int j = lineLen - 2; j >= 0; j--) {
    int x = 0, y = j;
    char tmp[lineCounter + 1];
    int k = 0;

    while (x < lineCounter && y >= 0) {
      tmp[k++] = wordSearch[x++][y--];
    }
    tmp[k] = '\0';

    if (k >= 4) {
      diagonalRL[dRLCounter] = strdup(tmp);
      dRLCounter++;
    }
  }

  sum += findXMAS(diagonalRL, dRLCounter);

  // Output
  printf("Total 'XMAS' apperances: %d\n", sum);

  return EXIT_SUCCESS;
}
