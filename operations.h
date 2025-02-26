#pragma once 
#include "add_terms.h"
#include "copying.h"

TermNode* add_psforms(TermNode *head1, TermNode *head2, int sign) {//функция сложения полиномов, используется также для релизации вычитания (тогда int sign = -1, а не 1)
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
    return result;//возвращает указатель на 3 полином, который является суммой/разностью двух предыдущх (можно и сделать возврат внутри первого полинома)
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
    return result;//возвращает указатель на 3 полином, который является произведением двух предыдущх (можно и сделать возврат внутри первого полинома)
}

TermNode* divide_psforms(TermNode *head1, TermNode *head2) {
    if (!head2 || !head2->next) {//проверка на то, что во втором полиноме у нас только одно слагаемое
        TermNode *result = NULL;
        for (TermNode *t1 = head1; t1; t1 = t1->next) {//проход по каждому слагаемому
            if (t1->coefficient % head2->coefficient != 0) {//проверка делимости
                printf("error\n");
                return NULL;
            }
            int new_coeff = t1->coefficient / head2->coefficient;
            FactorNode *new_factors = NULL;

            FactorNode *f1 = t1->factors;//множители делимого
            FactorNode *f2 = head2->factors;//множители делителя
            while (f1) {//копируем все множители  в новый список
                add_factor_sorted(&new_factors, f1->factor);
                f1 = f1->next;
            }
            while (f2) {//удаление лишних множителей
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