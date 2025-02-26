#pragma once 
#include "nodes.h"

void add_term(TermNode **head, int coefficient, FactorNode *factors) {//добавление слагаемого в конец имеющегося списка, нужно для реализации сложения и вычитания
    TermNode *new_term = create_term(coefficient);
    new_term->factors = factors;
    if (!*head) {
        *head = new_term;
        return;
    }
    TermNode *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_term;
}