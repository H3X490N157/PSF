#pragma once
#include "nodes.h"

FactorNode* copy_factors(FactorNode *factors) {
    if (!factors) return NULL;
    FactorNode *new_head = create_factor(factors->factor);
    FactorNode *current = new_head;
    factors = factors->next;
    
    while (factors) {
        current->next = create_factor(factors->factor);
        current = current->next;
        factors = factors->next;
    }
    return new_head;
}
