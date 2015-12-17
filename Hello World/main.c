#include <stdio.h>
#include <stdlib.h>
#include "filehandle.h"

int main() {
    char * fileName = "declaration.txt";
    char * sourceText = read_text_from_file(fileName);
    printf("%s\n", sourceText);

    free(sourceText);

    return 0;
}