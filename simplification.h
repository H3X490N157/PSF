#pragma once 
#include "nodes.h"

void simplify(TermNode **head) {//функция для объединения слагаемых с одинаковыми множителями и удаления слагаемых с нулевыми коэффициентами
    if (!*head) {
        return;
    }
    sort_terms(head);

    TermNode *current = *head, *prev = NULL;
    while (current) {
        TermNode *pseudo_iterator = current->next, *pseudo_iterator_prev = current;
        while (pseudo_iterator) {//цикл для поиска и сложения одинаковых слагаемых 
            if (compare_factors(current->factors, pseudo_iterator->factors) == 0) {
                current->coefficient += pseudo_iterator->coefficient;
                pseudo_iterator_prev->next = pseudo_iterator->next;
                free(pseudo_iterator);
                pseudo_iterator = pseudo_iterator_prev->next;
            } 
            else {
                pseudo_iterator_prev = pseudo_iterator;
                pseudo_iterator = pseudo_iterator->next;
            }
        }
        if (current->coefficient == 0) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                *head = current->next;
            }
            free(current);
            current = (prev ? prev->next : *head);
        } 
        else {
            prev = current;
            current = current->next;
        }
    }
}