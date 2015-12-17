//
// Created by Evgeny on 12/17/2015.
//

#ifndef PASCALVARIABLEDECLARATION_PARSER_H
#define PASCALVARIABLEDECLARATION_PARSER_H

#endif //PASCALVARIABLEDECLARATION_PARSER_H

#include "lexer.h"
int checkSourceCode(TOKENS sourceTokens);
void init(TOKENS sourceTokens);
int declarationSection();
int declarationGroup();
int declaration();
int tokenType(int type);
int type();
int type1();
int type2();
int declarationGroup1();
int declarationGroup2();
int declaration1();
int declaration2();
int dimensionGroup();
int dimensionGroup1();
int dimensionGroup2();
void createVariables();