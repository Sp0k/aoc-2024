#ifndef FILE_READER_LIB_H
#define FILE_READER_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline char *readFileData(char *filename) {
    char path[] = "../resources/";
    char filepath[32];
    strcpy(filepath, path);
    strcat(filepath, filename);

    FILE *input = fopen(filepath, "r");
    if (!input) {
        fprintf(stderr, "Could not open input file");
        exit(EXIT_FAILURE);
    }

    char *buffer;

    fseek(input, 0, SEEK_END);
    int length = ftell(input);
    fseek(input, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);
    fread(buffer, 1, length, input);
    buffer[length] = '\0';

    fclose(input);

    return buffer;
}

#ifdef __cplusplus
}
#endif

#endif // !FILE_READER_LIB_H

