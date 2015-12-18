//
// Created by Evgeny on 12/18/2015.
//

#include "parser.h"
//#include "lexer.h"

int currentTokenIndex;
TOKENS sourceTokens;

void init(TOKENS tokens);
int polynom();
int tokenType(int type);
int variable();

void init(TOKENS tokens) {
    sourceTokens = tokens;
    currentTokenIndex = 0;
}

int checkPolynom(TOKENS tokens) {
    init(tokens);
    int result = polynom() && (currentTokenIndex >= tokens.size);
    return result;
}

int tokenType(int type) {
    int result;
    if ((currentTokenIndex + 1) <= sourceTokens.size) {
        result = sourceTokens.tokens[currentTokenIndex++].type == type;
    }
    else {
        result = 0;
    }
    return result;
}

int polynom() {
    int saveIndex = currentTokenIndex;
    int result = polynom1()
                || (currentTokenIndex = saveIndex, polynom2());
    return result;
}

int polynom1() {
    int result = monom() && tokenType(PLUS_LEXEM) && polynom();
    return result;
}

int polynom2() {
    int result = monom();
    return result;
}

int monom() {
    int saveIndex = currentTokenIndex;
    int result = monom1()
                || (currentTokenIndex = saveIndex, monom2())
                   || (currentTokenIndex = saveIndex, monom3());
    return result;
}

int monom1() {
    int result = tokenType(NUMBER_LEXEM) && tokenType(TIMES) && variableGroup();
    return result;
}

int monom2() {
    int result = variableGroup();
    return result;
}

int monom3() {
    int result = tokenType(NUMBER_LEXEM);
    return result;
}

int variableGroup() {
    int saveIndex = currentTokenIndex;
    int result = variableGroup1()
                || (currentTokenIndex = saveIndex, variableGroup2());
    return result;
}

int variableGroup1() {
    int result = varPower() && tokenType(TIMES) && variableGroup();
    return result;
}

int variableGroup2() {
    int result = varPower();
    return result;
}

int varPower() {
    int saveIndex = currentTokenIndex;
    int result = varPower1()
                || (currentTokenIndex = saveIndex, varPower2());
    return result;
}

int varPower1() {
    int result = var() && tokenType(CARET_LEXEM) && tokenType(NUMBER_LEXEM);
    return result;
}

int varPower2() {
    int result = var();
    return result;
}

int var() {
    int result = tokenType(VARIABLE_LEXEM);
    return result;
}

