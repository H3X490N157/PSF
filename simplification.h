#pragma once 
#include "nodes.h"

void simplify(TermNode **head) {
    if (!*head) return;
    sort_terms(head);

    TermNode *current = *head, *prev = NULL;
    while (current) {
        TermNode *runner = current->next, *runner_prev = current;
        while (runner) {
            if (compare_factors(current->factors, runner->factors) == 0) {
                current->coefficient += runner->coefficient;
                runner_prev->next = runner->next;
                free(runner);
                runner = runner_prev->next;
            } else {
                runner_prev = runner;
                runner = runner->next;
            }
        }
        if (current->coefficient == 0) {
            if (prev) prev->next = current->next;
            else *head = current->next;
            free(current);
            current = (prev ? prev->next : *head);
        } else {
            prev = current;
            current = current->next;
        }
    }
}