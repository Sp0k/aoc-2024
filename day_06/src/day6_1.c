#include "../../lib/fileReaderLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int dir;    // 0: up, 1: left, 2: down, 3: right
  int pos[2]; // x, y coordinate
  int onMap;  // Flag
} Guard;

Guard *guard;

void initGuard(int x, int y) {
  guard = malloc(sizeof(Guard));

  guard->pos[0] = x;
  guard->pos[1] = y;

  guard->onMap = 1;
  guard->dir = 0;
}

void moveUp(char **map) {
  if (guard->pos[1] == 0) {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->onMap = 0;
    return;
  }

  if (map[guard->pos[1] - 1][guard->pos[0]] == '#')
    guard->dir = (guard->dir + 1) % 4;
  else {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->pos[1]--;
  }
}

void moveRight(char **map, int cols) {
  if (guard->pos[0] == cols - 1) {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->onMap = 0;
    return;
  }

  if (map[guard->pos[1]][guard->pos[0] + 1] == '#')
    guard->dir = (guard->dir + 1) % 4;
  else {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->pos[0]++;
  }
}

void moveDown(char **map, int rows) {
  if (guard->pos[1] == rows - 1) {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->onMap = 0;
    return;
  }

  if (map[guard->pos[1] + 1][guard->pos[0]] == '#')
    guard->dir = (guard->dir + 1) % 4;
  else {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->pos[1]++;
  }
}

void moveLeft(char **map) {
  if (guard->pos[1] == 0) {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->onMap = 0;
    return;
  }

  if (map[guard->pos[1]][guard->pos[0] - 1] == '#')
    guard->dir = (guard->dir + 1) % 4;
  else {
    map[guard->pos[1]][guard->pos[0]] = 'X';
    guard->pos[0]--;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Please include the input file");
    exit(EXIT_FAILURE);
  }

  // File reading
  char *path = "../resources/";
  char filename[32];
  strcpy(filename, path);
  strcat(filename, argv[1]);
  char *data = readFileData(filename);

  // Create map
  char **map = malloc(sizeof(char *));
  int rows = 0;
  char *token = strtok(data, "\n");
  while (token != NULL) {
    if (rows > 1)
      map = realloc(map, sizeof(char *) * (rows + 1));

    map[rows] = strdup(token);

    token = strtok(NULL, "\n");

    rows++;
  }
  int cols = strlen(map[0]);

  // Assume the guard is facing up upon initialization (my case)
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (map[i][j] == '^') {
        initGuard(j, i);
        break;
      }
    }
    if (guard)
      break;
  }

  while (guard->onMap) {
    switch (guard->dir) {
      case 0: moveUp(map); break;
      case 1: moveRight(map, cols); break;
      case 2: moveDown(map, rows); break;
      case 3: moveLeft(map); break;
    }
  } 

  int count = 0;
  for (int i = 0; i < rows; i++) {
    printf("%s\n", map[i]);
    for (int j = 0; j < cols; j++) {
      if (map[i][j] == 'X')
        count++;
    }
  }

  printf("\nThe guard will visit %d distinct positions!\n", count);

  return EXIT_SUCCESS;
}
