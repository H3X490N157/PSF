#pragma once 
#include "creation.h"

void add_factor_sorted(FactorNode **head, char factor) {
    FactorNode *new_factor = create_factor(factor);
    if (!*head || (*head)->factor > factor) {
        new_factor->next = *head;
        *head = new_factor;
        return;
    }
    FactorNode *current = *head;
    while (current->next && current->next->factor < factor) {
        current = current->next;
    }
    new_factor->next = current->next;
    current->next = new_factor;
}

void sort_terms(TermNode **head) {
    if (!*head || !(*head)->next) return;
    TermNode *sorted = NULL;
    TermNode *current = *head;

    while (current) {
        TermNode *next = current->next;
        if (!sorted || compare_factors(current->factors, sorted->factors) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            TermNode *temp = sorted;
            while (temp->next && compare_factors(temp->next->factors, current->factors) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}