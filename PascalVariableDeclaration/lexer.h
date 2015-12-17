//
// Created by Evgeny on 12/16/2015.
//

#ifndef PASCALVARIABLEDECLARATION_LEXER_H
#define PASCALVARIABLEDECLARATION_LEXER_H

#endif //PASCALVARIABLEDECLARATION_LEXER_H

typedef enum {IDENTIFIER_SYMBOL, DIGIT, COLON, COMMA, SEMICOLON, RUBBISH, DOT, OPEN_SQUARE, CLOSE_SQURE} symbolType;
typedef enum {IDENTIFIER_LEXEM, DATA_TYPE_LEXEM, VAR_LEXEM, COLON_LEXEM, SEMICOLON_LEXEM, COMMA_LEXEM,
              NUMBER_LEXEM, ARRAY_LEXEM, RANGE_LEXEM, OPEN_SQUARE_LEXEM, CLOSE_SQUARE_LEXEM, OF_LEXEM} lexemType;

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

int isIdentifierStartSymbol(char symbol);
int isIdentifierSymbol(char symbol);
int isColon(char symbol);
int isBreaker(char symbol);
int isComma(char symbol);
TOKENS getTokens(char * sourceCode);
