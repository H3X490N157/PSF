#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct FactorNode {
    char factor;
    struct FactorNode *next;
} FactorNode;

typedef struct TermNode {
    int coefficient;
    FactorNode *factors;
    struct TermNode *next;
} TermNode;