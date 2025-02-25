#pragma once
#include "nodes.h"

FactorNode* create_factor(char factor) {
    FactorNode *new_factor = (FactorNode *)malloc(sizeof(FactorNode));
    new_factor->factor = factor;
    new_factor->next = NULL;
    return new_factor;
}

TermNode* create_term(int coefficient) {
    TermNode *new_term = (TermNode *)malloc(sizeof(TermNode));
    new_term->coefficient = coefficient;
    new_term->factors = NULL;
    new_term->next = NULL;
    return new_term;
}