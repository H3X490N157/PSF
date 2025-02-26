#pragma once 
#include "add_terms.h"

void parse_psform(char *input, TermNode **head) {//приведение PS-форм к каноническому виду
    int sign = 1, coefficient;
    char *ptr = input;
    while (*ptr) {
        while (*ptr == ' ') {
            ptr++;
        }
        if (*ptr == '+' || *ptr == '-') {
            sign = (*ptr == '-') ? -1 : 1;
            ptr++;
        } 
        else {
            sign = 1;
        }

        while (*ptr == ' '){//пропуск пробелов в строке
            ptr++;
        }

        coefficient = sign;
        if (isdigit(*ptr)) {//получение числового коэффицент
            coefficient = sign * atoi(ptr);//чтение числа в коэффициент через atoi
            while (isdigit(*ptr)) {
                ptr++;//сдвиг до окончания цифр в числовом коэффициенте
            }
        }

        FactorNode *factor_list = NULL;
        while (*ptr && *ptr != '+' && *ptr != '-') {
            if (isalpha(*ptr)) {
                add_factor_sorted(&factor_list, *ptr);//добавление буквенных переменных в отсортированном виде 
                ptr++;
            } 
            else {
                ptr++;
            }
        }
        add_term(head, coefficient, factor_list);//добавленеи отсортированного одночлена в многочлен
    }
}