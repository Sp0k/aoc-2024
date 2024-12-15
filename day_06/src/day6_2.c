#include "../../lib/fileReaderLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int dir;    // 0: up, 1: left, 2: down, 3: right
  int pos[2]; // x, y coordinate
  int onMap;  // Flag
  int isLooping;
} Guard;

typedef struct {
  char c;
  int visited;
  int dir;
} Cell;

Guard *guard;
Cell **map;

void initGuard(int x, int y) {
  guard = malloc(sizeof(Guard));

  guard->pos[0] = x;
  guard->pos[1] = y;

  guard->onMap = 1;
  guard->dir = 0;
  guard->isLooping = 0;
}

void moveUp(Cell **m) {
  if (guard->pos[1] == 0) {
    guard->onMap = 0;
    return;
  }

  Cell *nextCell = &m[guard->pos[1] - 1][guard->pos[0]];
  Cell *currCell = &m[guard->pos[1]][guard->pos[0]];

  if (nextCell->c == '#' || nextCell->c == 'O') {
    currCell->c = '+';
    guard->dir = (guard->dir + 1) % 4;
  } else {
    guard->pos[1]--;
    if (nextCell->c != '^') 
      nextCell->c = (nextCell->c == '.' || nextCell->c == '|') ? '|' : '+';

    if (nextCell->visited && nextCell->dir == guard->dir) {
      guard->isLooping = 1;
      return;
    }

    nextCell->visited = 1;
    nextCell->dir = guard->dir;
  }
}

void moveRight(Cell **m, int cols) {
  if (guard->pos[0] == cols - 1) {
    guard->onMap = 0;
    return;
  }

  Cell *nextCell = &m[guard->pos[1]][guard->pos[0] + 1];
  Cell *currCell = &m[guard->pos[1]][guard->pos[0]];

  if (nextCell->c == '#' || nextCell->c == 'O') {
    currCell->c = '+';
    guard->dir = (guard->dir + 1) % 4;
  } else {
    guard->pos[0]++;
    if (nextCell->c != '^')
      nextCell->c = (nextCell->c == '.' || nextCell->c == '-') ? '-' : '+';

    if (nextCell->visited && nextCell->dir == guard->dir) {
      guard->isLooping = 1;
      return;
    }

    nextCell->visited = 1;
    nextCell->dir = guard->dir;
  }
}

void moveDown(Cell **m, int rows) {
  if (guard->pos[1] == rows - 1) {
    guard->onMap = 0;
    return;
  }

  Cell *nextCell = &m[guard->pos[1] + 1][guard->pos[0]];
  Cell *currCell = &m[guard->pos[1]][guard->pos[0]];

  if (nextCell->c == '#' || nextCell->c == 'O') {
    currCell->c = '+';
    guard->dir = (guard->dir + 1) % 4;
  } else {
    guard->pos[1]++;
    if (nextCell->c != '^')
      nextCell->c = (nextCell->c == '.' || nextCell->c == '|') ? '|' : '+';

    if (nextCell->visited && nextCell->dir == guard->dir) {
      guard->isLooping = 1;
      return;
    }

    nextCell->visited = 1;
    nextCell->dir = guard->dir;
  }
}

void moveLeft(Cell **m) {
  if (guard->pos[0] == 0) {
    guard->onMap = 0;
    return;
  }

  Cell *nextCell = &m[guard->pos[1]][guard->pos[0] - 1];
  Cell *currCell = &m[guard->pos[1]][guard->pos[0]];

  if (nextCell->c == '#' || nextCell->c == 'O') {
    currCell->c = (currCell->c != '^') ? '+' : '^';
    guard->dir = (guard->dir + 1) % 4;
  } else {
    guard->pos[0]--;
    if (nextCell->c != '^')
      nextCell->c = (nextCell->c == '.' || nextCell->c == '-') ? '-' : '+';

    if (nextCell->visited && nextCell->dir == guard->dir) {
      guard->isLooping = 1;
      return;
    }

    nextCell->visited = 1;
    nextCell->dir = guard->dir;
  }
}

Cell **copyMap(int rows, int cols) {
  Cell **tmp = malloc(sizeof(Cell *) * rows);

  for (int i = 0; i < rows; i++) {
    tmp[i] = malloc(sizeof(Cell) * cols);
    for (int j = 0; j < cols; j++) {
      tmp[i][j] = map[i][j];
    }
  }

  return tmp;
}

void resetGuard(int x, int y) {
  guard->isLooping = 0;
  guard->onMap = 1;
  guard->dir = 0;
  guard->pos[0] = x;
  guard->pos[1] = y;
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
  map = malloc(sizeof(Cell *));
  int rows = 0;
  char *token = strtok(data, "\n");
  int cols = strlen(token);
  int guardInitialPos[2];
  while (token != NULL) {
    if (rows > 1)
      map = realloc(map, sizeof(Cell *) * (rows + 1));

    map[rows] = malloc(sizeof(Cell) * cols);
    for (int i = 0; i < cols; i++) {
      map[rows][i].c = token[i];

      // Assume the guard starts facing up (my case)
      if (map[rows][i].c == '^') {
        initGuard(i, rows);
        guardInitialPos[0] = i;
        guardInitialPos[1] = rows;
      }

      map[rows][i].dir = -1;
      map[rows][i].visited = 0;
    }

    token = strtok(NULL, "\n");
    rows++;
  }

  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (map[i][j].c == '#' || map[i][j].c == '^')
        continue;

      Cell **tmpMap = copyMap(rows, cols);
      resetGuard(guardInitialPos[0], guardInitialPos[1]);

      tmpMap[i][j].c = 'O';

      while (guard->onMap && !guard->isLooping) {
        switch (guard->dir) {
          case 0: moveUp(tmpMap); break;
          case 1: moveRight(tmpMap, cols); break;
          case 2: moveDown(tmpMap, rows); break;
          case 3: moveLeft(tmpMap); break;
        }
      }

      if (guard->isLooping) {
        printf("(%d,%d):\n", j, i);
        for (int k = 0; k < rows; k++) {
          for (int l = 0; l < cols; l++) {
            printf("%c", tmpMap[k][l].c);
          }
          printf("\n");
        }
        printf("\n");
        count++;
      }

      for (int k = 0; k < rows; k++)
        free(tmpMap[k]);
      free(tmpMap);
    }
  }

  printf("There is %d different positions for the obstruction!\n", count);

  return EXIT_SUCCESS;
}
