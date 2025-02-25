#pragma once 
#include "add_terms.h"

void parse_psform(char *input, TermNode **head) {
    int sign = 1, coefficient;
    char *ptr = input;
    while (*ptr) {
        while (*ptr == ' ') ptr++;
        if (*ptr == '+' || *ptr == '-') {
            sign = (*ptr == '-') ? -1 : 1;
            ptr++;
        } else sign = 1;

        while (*ptr == ' ') ptr++;

        coefficient = sign;
        if (isdigit(*ptr)) {
            coefficient = sign * atoi(ptr);
            while (isdigit(*ptr)) ptr++;
        }

        FactorNode *factor_list = NULL;
        while (*ptr && *ptr != '+' && *ptr != '-') {
            if (isalpha(*ptr)) {
                add_factor_sorted(&factor_list, *ptr);
                ptr++;
            } else ptr++;
        }

        add_term(head, coefficient, factor_list);
    }
}