#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct FactorNode { //односвязный список для хранения множителей в одном слагаемом
    char factor;
    struct FactorNode *next;
} FactorNode;

typedef struct TermNode { //список для хранение слагаемых в одном полиноме
    int coefficient;
    FactorNode *factors;
    struct TermNode *next;
} TermNode;