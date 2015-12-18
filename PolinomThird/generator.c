//
// Created by Evgeny on 12/19/2015.
//

#include <time.h>
#include <stdlib.h>
#include "lexer.h"
#include <stdio.h>
#include "generator.h"

char * resultPolynom;

void g_tokenType(int type);
void g_var();

void g_tokenType(int type) {
    int variable;
    char * tempStr;
    switch (type) {
        case CARET_LEXEM:
            //printf("^");
            strcat(resultPolynom, "^");
            break;
        case PLUS_LEXEM:
            //printf(" + ");
            strcat(resultPolynom, " + ");
            break;
        case TIMES_LEXEM:
            //printf(" * ");
            strcat(resultPolynom, " * ");
            break;
        case VARIABLE_LEXEM:
            variable = rand() % 3 + 'x';
            tempStr = (char *)malloc(sizeof(char) * 2);
            tempStr[0] = variable;
            tempStr[1] = '\0';
            strcat(resultPolynom, tempStr);
            //printf("%c", variable);
            break;
        case NUMBER_LEXEM:
            variable = rand() % 2 + '2';
            tempStr = (char *)malloc(sizeof(char) * 2);
            tempStr[0] = variable;
            tempStr[1] = '\0';
            strcat(resultPolynom, tempStr);
            //printf("%c", variable);
            break;
    }
}

char * getPolynom() {
    resultPolynom = (char *)malloc(sizeof(char) * 1000);
    resultPolynom[0] = '\0';
    srand(time(NULL));
    polynomThird();
    g_polynom();
    return resultPolynom;
}

void polynomThird() {
    g_tokenType(NUMBER_LEXEM);
    g_tokenType(TIMES_LEXEM);
    g_tokenType(VARIABLE_LEXEM);
    g_tokenType(CARET_LEXEM);
    resultPolynom[6] = '3';
    //printf("3");
    g_tokenType(PLUS_LEXEM);
}

void g_polynom() {
    int way = rand() % 2;
    switch (way) {
        case 0:
            g_polynom1();
            break;
        case 1:
            g_polynom2();
            break;
    }
}

void g_polynom1() {
    g_monom();
    g_tokenType(PLUS_LEXEM);
    g_polynom();
}

void g_polynom2() {
    g_monom();
}

void g_monom() {
    int way = rand() % 3;
    switch (way) {
        case 0:
            g_monom1();
            break;
        case 1:
            g_monom2();
            break;
        case 2:
            g_monom3();
            break;
    }
}

void g_monom1() {
    g_tokenType(NUMBER_LEXEM);
    g_tokenType(TIMES);
    g_variableGroup();
}

void g_monom2() {
    g_variableGroup();
}

void g_monom3() {
    g_tokenType(NUMBER_LEXEM);
}

void g_variableGroup() {
    int way = rand() % 2;
    switch (way) {
        case 0:
            g_variableGroup1();
            break;
        case 1:
            g_variableGroup2();
            break;
    }
}

void g_variableGroup1() {
    g_varPower();
    g_tokenType(TIMES);
    g_variableGroup();
}

void g_variableGroup2() {
    g_varPower();
}

void g_varPower() {
    int way = rand() % 2;
    switch (way) {
        case 0:
            g_varPower1();
            break;
        case 1:
            g_varPower2();
            break;
    }
}

void g_varPower1() {
    g_var();
    g_tokenType(CARET_LEXEM);
    g_tokenType(NUMBER_LEXEM);
}

void g_varPower2();

void g_varPower2() {
    g_var();
}



void g_var() {
    g_tokenType(VARIABLE_LEXEM);
}
