//
// Created by Evgeny on 12/17/2015.
//

#include "parser.h"
#include <stdio.h>

typedef struct {
    char * name;
    char * type;
} VARIABLE;

typedef struct {
    VARIABLE * variables;
    int size;
} VARIABLES;

TOKENS tokens;
VARIABLES variables;

int currentIndex;
int currentIdentifierIndex;


void createVariables() {

    int i = 0;
    i = currentIdentifierIndex;
    int endIndex;
    int currentVariableIndex = 0;
    int variableSize;


        while ((i < tokens.size - 1) && (tokens.tokens[i].type != COLON_LEXEM)) {
            if (tokens.tokens[i].type == IDENTIFIER_LEXEM) {
                VARIABLE newVariable;
                newVariable.name = tokens.tokens[i].lexem;
                variables.variables[currentVariableIndex++] = newVariable;
            }
            i++;
        }
        variableSize = currentVariableIndex;
        endIndex = i++;

        int j;
        for (j = 0; j < variableSize; j++) {
            printf("%s", variables.variables[j].name);
            i = endIndex;
            while (tokens.tokens[i].type != SEMICOLON_LEXEM) {
                if ((tokens.tokens[i].type == OF_LEXEM) || (tokens.tokens[i].type == COLON_LEXEM)) {
                    printf(" ");
                }
                printf("%s", tokens.tokens[i].lexem);
                if ((tokens.tokens[i].type == OF_LEXEM) || (tokens.tokens[i].type == COLON_LEXEM)) {
                    printf(" ");
                }
                i++;
            }
            printf("\n");
        }
        currentIdentifierIndex = i;

}

int checkSourceCode(TOKENS sourceTokens) {
    init(sourceTokens);
    int result = declarationSection();
    return result;
}

void init(TOKENS sourceTokens) {
    tokens = sourceTokens;
    currentIndex = 0;
    currentIdentifierIndex = 0;
    VARIABLE * variableArray = (VARIABLE *)malloc(sizeof(VARIABLE) * 255);
    variables.variables = variableArray;
}

int declarationSection() {
    int result = tokenType(VAR_LEXEM) && declarationGroup();
    return result;
}

int declarationGroup() {

    int saveIndex = currentIndex;

    int result = (declarationGroup1())
                 || (currentIndex = saveIndex, declarationGroup2());
    return result;
}

int declarationGroup1() {
    int tempDecl = declaration();

    if (tempDecl) {
        createVariables();
    }

    int result = tempDecl && declarationGroup();
    return result;
}

int declarationGroup2() {
    int result = declaration();
    if (result) {
        createVariables();
    }
    return result;
}

int declaration() {
    int saveIndex = currentIndex;

    int result = (declaration1())
           || (currentIndex = saveIndex, declaration2());
    return result;
}

int declaration1() {
    int result = tokenType(IDENTIFIER_LEXEM) && tokenType(COMMA_LEXEM) && declaration();
    return result;
}

int declaration2() {
    int result = tokenType(IDENTIFIER_LEXEM) && tokenType(COLON_LEXEM)
                  && type() && tokenType(SEMICOLON_LEXEM);
    return result;
}

int dimensionGroup() {
    int saveIndex = currentIndex;

    int result = dimensionGroup1()
                 || (currentIndex = saveIndex, dimensionGroup2());

    return result;
}

int dimensionGroup1() {
    int result = dimension() && tokenType(COMMA_LEXEM) && dimensionGroup();
    return result;
}

int dimensionGroup2() {
    int result = dimension();
    return result;
}

int dimension() {
    int result = tokenType(NUMBER_LEXEM) && tokenType(RANGE_LEXEM) && tokenType(NUMBER_LEXEM);
    return result;
}

int type() {
    int saveIndex = currentIndex;

    int result = type1()
                 || (currentIndex = saveIndex, type2());
    return result;
}

int type1() {
    int result = tokenType(ARRAY_LEXEM) && tokenType(OPEN_SQUARE_LEXEM)
                  && dimensionGroup() && tokenType(CLOSE_SQUARE_LEXEM) && tokenType(OF_LEXEM) && type();

    return result;
}

int type2() {
    int result = tokenType(DATA_TYPE_LEXEM);
    return result;
}

int tokenType(int type) {
    int result;
    if ((currentIndex + 1) <= tokens.size) {
        result = tokens.tokens[currentIndex++].type == type;
    }
    else {
        result = 0;
    }
    return result;
}