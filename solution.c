#include "comparison.h"
#include "printer.h"
#include "sorters.h"
#include "parsing.h"
#include "simplification.h"
#include "memory_free.h"
#include "equation.h"
#include "operations.h"


int main() {
    char operation;
    char input1[10000], input2[10000]; //память беру с запасом, в принципе, можно оптимизировать с учётом того, что всего всего 100 слагаемых и 26 множителей

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