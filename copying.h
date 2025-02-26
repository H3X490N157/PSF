#pragma once
#include "nodes.h"

FactorNode* copy_factors(FactorNode *factors) {//копирование здесь выполняется путём создания нового списка, а не с помощью конструкторов копирования и/или rvalue, как в плюсах
    if (!factors) {
        return NULL;
    }
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
