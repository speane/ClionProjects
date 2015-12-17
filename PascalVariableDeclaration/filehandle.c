//
// Created by Evgeny on 12/16/2015.
//

#include "filehandle.h"

#include "filehandle.h"
#include <stdio.h>
#include "stdlib.h"

char * read_text_from_file(char * fileName) {
    FILE * readFile = fopen(fileName, "r");

    int bufSize = 1000;
    int currentTextSize = bufSize;

    char * result = (char *)malloc(sizeof(char) * currentTextSize);
    int i = 0;

    while ((result[i] = fgetc(readFile)) != EOF) {
        //i++;
        if (++i == bufSize) {
            currentTextSize += bufSize;
            result = (char *)realloc(result, sizeof(char) * currentTextSize);
        }
    }
    fclose(readFile);
    result[i] = '\0';

    return result;
}
