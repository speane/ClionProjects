//
// Created by Evgeny on 12/16/2015.
//

#include "lexer.h"

TOKEN colon();
TOKEN semiColon();
TOKEN comma();
TOKEN identifier(char startSymbol);
symbolType getSymbolType(char symbol);
int isDigit(char symbol);
void getNextSymbol();
char * toUpperCase(char * lexem);
lexemType getIdentifierType(char * lexem);
TOKEN number();
TOKEN range();
TOKEN closeSquare();
TOKEN openSquare();
int dimension();

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
            case COLON:
                result[index++] = colon();
                break;
            case SEMICOLON:
                result[index++] = semiColon();
                break;
            case COMMA:
                result[index++] = comma();
                break;
            case OPEN_SQUARE:
                result[index++] = openSquare();
                break;
            case CLOSE_SQURE:
                result[index++] = closeSquare();
                break;
            case IDENTIFIER_SYMBOL:
                result[index++] = identifier(currentSymbol);
                //getNextSymbol();
                break;
            case DIGIT:
                result[index++] = number();
                break;
            case DOT:
                if (getSymbolType(nextSymbol) == DOT) {
                    result[index++] = range();
                }
                break;
            default:
                //getNextSymbol();
                break;
        }
        getNextSymbol();
    }
    resultTokens.tokens = result;
    resultTokens.size = index + 1;
    return resultTokens;
}

TOKEN range() {
    TOKEN result;
    result.lexem = "..";
    result.type = RANGE_LEXEM;
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

TOKEN closeSquare() {
    TOKEN result;
    result.lexem = "]";
    result.type = CLOSE_SQUARE_LEXEM;
    //getNextSymbol();
    return result;
}

TOKEN openSquare() {
    TOKEN result;
    result.lexem = "[";
    result.type = OPEN_SQUARE_LEXEM;
    //getNextSymbol();
    return result;
}

TOKEN colon() {
    TOKEN result;
    result.lexem = ":";
    result.type = COLON_LEXEM;
    //getNextSymbol();
    return result;
}

TOKEN semiColon() {
    TOKEN result;
    result.lexem = ";";
    result.type = SEMICOLON_LEXEM;
    //getNextSymbol();
    return result;
}

TOKEN comma() {
    TOKEN result;
    result.lexem = ",";
    result.type = COMMA_LEXEM;
    //getNextSymbol();
    return result;
}

TOKEN identifier(char startSymbol) {
    TOKEN result;
    char * lexem = (char *)malloc(sizeof(char) * 255);
    int index = 0;
    lexem[index++] = startSymbol;

    while (getSymbolType(nextSymbol) == IDENTIFIER_SYMBOL) {
        getNextSymbol();
        lexem[index++] = currentSymbol;
    }

    lexem[index] = '\0';

    lexem = toUpperCase(lexem);
    result.lexem = lexem;
    result.type = getIdentifierType(lexem);

    return result;
}



symbolType getSymbolType(char symbol) {
    switch (symbol) {
        case '[':
            return OPEN_SQUARE;
        case ']':
            return CLOSE_SQURE;
        case '.':
            return DOT;
        case ':':
            return COLON;
        case ';':
            return SEMICOLON;
        case ',':
            return COMMA;
        default:
            if (isDigit(symbol)) {
                return DIGIT;
            }
            else if (isIdentifierSymbol(symbol)) {
                return IDENTIFIER_SYMBOL;
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

int isIdentifierSymbol(char symbol) {
    char * startSymbols = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size = strlen(startSymbols);

    int i;
    for (i = 0; i < size; i++) {
        if (startSymbols[i] == symbol) {
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

lexemType getIdentifierType(char * lexem) {
    //char * upperLine = toUpperCase(lexem);

    if (!(strcmp(lexem, "INTEGER") && (strcmp(lexem, "REAL") && (strcmp(lexem, "CHAR"))))) {
        return DATA_TYPE_LEXEM;
    }
    else if (!strcmp(lexem, "VAR")) {
        return VAR_LEXEM;
    } else if (!strcmp(lexem, "ARRAY")) {
        return ARRAY_LEXEM;
    } else if (!strcmp(lexem, "OF")) {
        return OF_LEXEM;
    }
    else {
        return IDENTIFIER_LEXEM;
    }
}

char *toUpperCase(char * lexem) {
    char * upperLine;
    upperLine = (char *)malloc(sizeof(char) * 255);

    int i = 0;
    while (lexem[i] != '\0') {
        upperLine[i] = toupper(lexem[i]);
        i++;
    }

    upperLine[i] = '\0';

    return upperLine;
}