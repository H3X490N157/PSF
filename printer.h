#pragma once 
#include "nodes.h"

void print_psform(TermNode *head) {
    if (!head) {
        printf("0\n");
        return;
    }

    TermNode *current = head;
    while (current) {
        if (current != head) {
            printf(current->coefficient < 0 ? " - " : " + ");
        } else if (current->coefficient < 0) {
            printf("-");
        }

        int abs_coeff = abs(current->coefficient);
        if (abs_coeff != 1 || !current->factors) {
            printf("%d", abs_coeff);
        }

        FactorNode *factor = current->factors;
        if (factor && abs_coeff != 1) printf("*");  // * перед переменными, если коэффициент != 1

        while (factor) {
            printf("%c", factor->factor);
            if (factor->next) printf("*"); // Разделяем множители *
            factor = factor->next;
        }

        current = current->next;
    }
    printf("\n");
}