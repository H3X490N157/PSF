#include "comparison.h"
#include "printer.h"
#include "sorters.h"
#include "parsing.h"
#include "simplification.h"
#include "memory_free.h"
#include "equation.h"
#include "operations.h"
//все нужны библиотеки импортировались в nodes.h, а через nodes.h - во все другие хэдеры, постарался везде расставить pragma once для пресечения ромбовидного наследования
//здесь простой консольный UI для ручного тестирования; если нужны какие-либо тесты, пишите на email - добавлю, сам прогонял на наборе из 20 разных - везде сработало (если сломаете код - буду удивлён, но рад доработать); могу также сделать простой генератор тест-форм, но на плюсах 

int main() {
    char operation;
    char form_a[10000], form_b[10000]; //память беру с запасом, в принципе, можно оптимизировать с учётом того, что всего всего 100 слагаемых и 26 множителей

    scanf(" %c", &operation);
    scanf(" %[^\n]", form_a);
    scanf(" %[^\n]", form_b);

    TermNode *ps1 = NULL, *ps2 = NULL;
    parse_psform(form_a, &ps1);
    parse_psform(form_b, &ps2);

    simplify(&ps1);
    simplify(&ps2);

    if (operation == '+') {
        TermNode *sum = add_psforms(ps1, ps2, 1);
        print_psform(sum);
        free_psform(sum);
    } 
    else if (operation == '-') {
        TermNode *diff = add_psforms(ps1, ps2, -1);
        print_psform(diff);
        free_psform(diff);
    } 
    else if (operation == '*') {
        TermNode *prod = multiply_psforms(ps1, ps2);
        print_psform(prod);
        free_psform(prod);
    } 
    else if (operation == '=') {
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