#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct FactorNode {
    char factor;
    struct FactorNode *next;
} FactorNode;

typedef struct TermNode {
    int coefficient;
    FactorNode *factors;
    struct TermNode *next;
} TermNode;

FactorNode* create_factor(char factor) {
    FactorNode *new_factor = (FactorNode *)malloc(sizeof(FactorNode));
    new_factor->factor = factor;
    new_factor->next = NULL;
    return new_factor;
}

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

TermNode* create_term(int coefficient) {
    TermNode *new_term = (TermNode *)malloc(sizeof(TermNode));
    new_term->coefficient = coefficient;
    new_term->factors = NULL;
    new_term->next = NULL;
    return new_term;
}

void add_term(TermNode **head, int coefficient, FactorNode *factors) {
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

int compare_factors(FactorNode *f1, FactorNode *f2) {
    while (f1 && f2) {
        if (f1->factor != f2->factor) return f1->factor - f2->factor;
        f1 = f1->next;
        f2 = f2->next;
    }
    return (f1 ? 1 : 0) - (f2 ? 1 : 0);
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
        if (abs_coeff != 1 || !current->factors)
            printf("%d", abs_coeff);

        FactorNode *factor = current->factors;
        while (factor) {
            printf("%c", factor->factor);
            factor = factor->next;
        }

        current = current->next;
    }
    printf("\n");
}

TermNode* add_psforms(TermNode *head1, TermNode *head2, int sign) {
    TermNode *result = NULL;

    while (head1) {
        add_term(&result, head1->coefficient, copy_factors(head1->factors));
        head1 = head1->next;
    }
    while (head2) {
        add_term(&result, sign * head2->coefficient, copy_factors(head2->factors));
        head2 = head2->next;
    }

    simplify(&result);
    return result;
}

int are_equal(TermNode *head1, TermNode *head2) {
    while (head1 && head2) {
        if (head1->coefficient != head2->coefficient ||
            compare_factors(head1->factors, head2->factors) != 0)
            return 0;
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1 == head2;
}

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
TermNode* multiply_psforms(TermNode *head1, TermNode *head2) {
    TermNode *result = NULL;
    for (TermNode *t1 = head1; t1; t1 = t1->next) {
        for (TermNode *t2 = head2; t2; t2 = t2->next) {
            int new_coeff = t1->coefficient * t2->coefficient;
            FactorNode *new_factors = NULL;
            
            FactorNode *f1 = t1->factors;
            FactorNode *f2 = t2->factors;
            
            while (f1) {
                add_factor_sorted(&new_factors, f1->factor);
                f1 = f1->next;
            }
            while (f2) {
                add_factor_sorted(&new_factors, f2->factor);
                f2 = f2->next;
            }
            
            add_term(&result, new_coeff, new_factors);
        }
    }
    simplify(&result);
    return result;
}

TermNode* divide_psforms(TermNode *head1, TermNode *head2) {
    if (!head2 || !head2->next) {
        TermNode *result = NULL;
        for (TermNode *t1 = head1; t1; t1 = t1->next) {
            if (t1->coefficient % head2->coefficient != 0) {
                printf("error\n");
                return NULL;
            }
            int new_coeff = t1->coefficient / head2->coefficient;
            FactorNode *new_factors = NULL;

            FactorNode *f1 = t1->factors;
            FactorNode *f2 = head2->factors;
            while (f1) {
                add_factor_sorted(&new_factors, f1->factor);
                f1 = f1->next;
            }
            while (f2) {
                if (!new_factors || new_factors->factor != f2->factor) {
                    printf("error\n");
                    return NULL;
                }
                FactorNode *tmp = new_factors;
                new_factors = new_factors->next;
                free(tmp);
                f2 = f2->next;
            }
            add_term(&result, new_coeff, new_factors);
        }
        return result;
    }
    printf("error\n");
    return NULL;
}



int main() {
    char operation;
    char input1[1000], input2[1000];

    scanf(" %c", &operation);
    scanf(" %[^\n]", input1);
    scanf(" %[^\n]", input2);

    TermNode *ps1 = NULL, *ps2 = NULL;
    parse_psform(input1, &ps1);
    parse_psform(input2, &ps2);

    simplify(&ps1);
    simplify(&ps2);

    if (operation == '+') {
        TermNode *sum = add_psforms(ps1, ps2, 1);
        print_psform(sum);
        free_psform(sum);
    } else if (operation == '-') {
        TermNode *diff = add_psforms(ps1, ps2, -1);
        print_psform(diff);
        free_psform(diff);
    } else if (operation == '*') {
        TermNode *prod = multiply_psforms(ps1, ps2);
        print_psform(prod);
        free_psform(prod);
    } else if (operation == '=') {
        printf(are_equal(ps1, ps2) ? "equal\n" : "not equal\n");
    } 
     else if (operation == '/') {
        TermNode *quot = divide_psforms(ps1, ps2);
        if (quot) print_psform(quot);
        free_psform(quot);
    }
    else {
        printf("error\n");
    }

    free_psform(ps1);
    free_psform(ps2);
    return 0;
}