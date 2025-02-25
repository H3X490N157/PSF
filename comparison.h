#pragma once 
#include "nodes.h"

int compare_factors(FactorNode *f1, FactorNode *f2) {
    while (f1 && f2) {
        if (f1->factor != f2->factor) return f1->factor - f2->factor;
        f1 = f1->next;
        f2 = f2->next;
    }
    return (f1 ? 1 : 0) - (f2 ? 1 : 0);
}