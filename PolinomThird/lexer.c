//
// Created by Evgeny on 12/18/2015.
//

#include "lexer.h"

//
// Created by Evgeny on 12/16/2015.
//

//#include "lexer.h"


TOKEN identifier(char startSymbol);
symbolType getSymbolType(char symbol);
int isDigit(char symbol);
void getNextSymbol();
TOKEN number();
TOKEN times();
TOKEN plus();
TOKEN caret();
TOKEN variable();

char currentSymbol;
char nextSymbol;
int currentSymbolIndex;
char * sourceCode;

void initLexer(char * text);

void initLexer(char * text) {
    currentSymbolIndex = 0;
    sourceCode = text;
    currentSymbol = sourceCode[currentSymbolIndex];
    if (currentSymbol != '\0') {
        nextSymbol = sourceCode[++currentSymbolIndex];
    }
    else {
        nextSymbol = '\0';
    }
}


TOKENS getTokens(char * sourceCode) {
    TOKENS resultTokens;
    int bufSize = 255;
    int currentSize = bufSize;
    TOKEN * result = (TOKEN *)malloc(sizeof(TOKEN) * currentSize);
    int index = 0;

    initLexer(sourceCode);

    while (currentSymbol != '\0') {
        switch (getSymbolType(currentSymbol)) {
            case CARET:
                result[index++] = caret();
                break;
            case VARIABLE:
                result[index++] = variable();
                break;
            case PLUS:
                result[index++] = plus();
                break;
            case TIMES:
                result[index++] = times();
                break;
            case DIGIT:
                result[index++] = number();
                break;
            default:
                //getNextSymbol();
                break;
        }
        getNextSymbol();
    }
    resultTokens.tokens = result;
    resultTokens.size = index;
    return resultTokens;
}

TOKEN times() {
    TOKEN result;
    result.lexem = "*";
    result.type = TIMES_LEXEM;
    return result;
}

TOKEN plus() {
    TOKEN result;
    result.lexem = "+";
    result.type = PLUS_LEXEM;
    return result;
}

TOKEN caret() {
    TOKEN result;
    result.lexem = "^";
    result.type = CARET_LEXEM;
    return result;
}

TOKEN variable() {
    TOKEN result;
    char * lexem = (char *) malloc(sizeof(char) * 5);
    lexem[0] = currentSymbol;
    lexem[1] = '\0';
    result.lexem = lexem;
    result.type = VARIABLE_LEXEM;
    return result;
}

TOKEN number() {
    TOKEN result;
    char * lexem = (char *)malloc(sizeof(char) * 255);
    int index = 0;

    lexem[index++] = currentSymbol;
    while (getSymbolType(nextSymbol) == DIGIT) {
        getNextSymbol();
        lexem[index++] = currentSymbol;
    }

    lexem[index] = '\0';

    result.lexem = lexem;
    result.type = NUMBER_LEXEM;

    return result;
}

symbolType getSymbolType(char symbol) {
    switch (symbol) {
        case '*':
            return TIMES;
        case '+':
            return PLUS;
        case '^':
            return CARET;
        default:
            if (isDigit(symbol)) {
                return DIGIT;
            }
            else if (((symbol >= 'a') && (symbol <= 'z')) || ((symbol >= 'A') && (symbol <= 'Z'))) {
                return VARIABLE;
            }
            else {
                return RUBBISH;
            }
    }
}

int isDigit(char symbol) {
    char * digits = "0123456789";
    int size = strlen(digits);

    int i;
    for (i = 0; i < size; i++) {
        if (digits[i] == symbol) {
            return 1;
        }
    }

    return 0;
}


void getNextSymbol() {
    currentSymbol = nextSymbol;

    if (currentSymbol != '\0') {
        nextSymbol = sourceCode[++currentSymbolIndex];
    }
}

