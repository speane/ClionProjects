#include "filehandle.h"
#include <stdio.h>
#include "stdlib.h"

char * read_text_from_file(char * fileName) {
    FILE * readFile = fopen(fileName, "r");

    int bufSize = 10;
    int currentTextSize = bufSize;

    char * result = (char *)malloc(sizeof(char) * currentTextSize);
    int i = 0;

    while ((result[i] = fgetc(readFile)) != EOF) {
        if (++i == bufSize) {
            result = (char *)realloc(result, sizeof(char) * bufSize);
        }
    }

    result[i] = '\0';

    return result;
}