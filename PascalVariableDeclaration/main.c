#include <stdio.h>
#include <stdlib.h>
#include "filehandle.h"
#include "parser.h"

int main() {
    char * fileName = "test.txt";
    char * sourceCode = read_text_from_file(fileName);

    TOKENS tokens = getTokens(sourceCode);

    if (checkSourceCode(tokens)) {
        printf("\n\nACCEPT\n");
    }
    else {
        printf("\n\nREJECT\n");
    }

    free(sourceCode);
    getchar();

    return 0;
}