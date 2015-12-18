//
// Created by Evgeny on 12/18/2015.
//

#ifndef POLINOMTHIRD_LEXER_H
#define POLINOMTHIRD_LEXER_H

#endif //POLINOMTHIRD_LEXER_H

typedef enum {DIGIT, RUBBISH, VARIABLE, TIMES, PLUS, CARET} symbolType;
typedef enum {NUMBER_LEXEM, VARIABLE_LEXEM, PLUS_LEXEM, TIMES_LEXEM, CARET_LEXEM} lexemType;

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char * lexem;
    symbolType type;
} TOKEN;

typedef struct {
    TOKEN * tokens;
    int size;
} TOKENS;

int isIdentifierSymbol(char symbol);
TOKENS getTokens(char * sourceCode);
