#pragma once
#include "nodes.h"

void free_psform(TermNode *head) {
    while (head) {
        FactorNode *factor = head->factors;
        while (factor) {
            FactorNode *tmp_factor = factor;
            factor = factor->next;
            free(tmp_factor);
        }
        TermNode *tmp_term = head;
        head = head->next;
        free(tmp_term);
    }
}