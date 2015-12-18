#include <stdio.h>
#include "parser.h"
#include "generator.h"

int main() {
    //char * polynom = "3 *x^4*y^2 + x^2";
    char * polynom = getPolynom();
    printf("\n%s\n", polynom);
    TOKENS sourceTokens = getTokens(polynom);
    int check = checkPolynom(sourceTokens);
    if (check) {
        printf("\nACCEPT");
    }
    else {
        printf("\nREJECT");
    }

    return 0;
}