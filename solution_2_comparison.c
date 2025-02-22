#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TERMS 100
#define MAX_FACTORS 26
#define MAX_LENGTH 1000

typedef struct {
    int coefficient;
    char factors[MAX_FACTORS][2];  
    int factor_count;
} Term;

typedef struct {
    Term terms[MAX_TERMS];
    int term_count;
} PSForm;

// Функция сортировки множителей внутри слагаемого
int compare_factors(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

// Функция сортировки слагаемых
int compare_terms(const void *a, const void *b) {
    if (a == b) return 0;
    Term *termA = (Term *)a;
    Term *termB = (Term *)b;

    if (termA->factor_count != termB->factor_count)
        return termA->factor_count - termB->factor_count;

    return strcmp((char *)termA->factors, (char *)termB->factors);
}

// Функция парсинга PS-формы
void parse_psform(char *input, PSForm *psf) {
    psf->term_count = 0;
    int sign = 1; 
    char *ptr = input;

    while (*ptr) {
        while (*ptr == ' ') ptr++;

        if (*ptr == '+' || *ptr == '-') {  
            sign = (*ptr == '-') ? -1 : 1;
            ptr++;
        } else {
            sign = 1;  
        }

        while (*ptr == ' ') ptr++;

        Term term = {sign, {}, 0};  

        if (isdigit(*ptr)) {
            term.coefficient = sign * atoi(ptr);
            while (isdigit(*ptr)) ptr++;
        } else {
            term.coefficient = sign;
        }

        while (*ptr) {
            if (*ptr == ' ') {
                ptr++;
                continue;
            }

            if (isalpha(*ptr)) {
                term.factors[term.factor_count][0] = *ptr;
                term.factors[term.factor_count][1] = '\0';
                term.factor_count++;
                ptr++;
            } else if (*ptr == '+' || *ptr == '-') {
                break;
            } else {
                ptr++;
            }
        }

        if (term.coefficient == 0) continue;  

        qsort(term.factors, term.factor_count, sizeof(term.factors[0]), compare_factors);

        psf->terms[psf->term_count++] = term;
    }
}

// Функция минимизации PS-формы (объединение одинаковых слагаемых)
void simplify_psform(PSForm *psf) {
    qsort(psf->terms, psf->term_count, sizeof(Term), compare_terms);

    int new_count = 0;
    for (int i = 0; i < psf->term_count; i++) {
        if (new_count > 0 &&
            strcmp((char *)psf->terms[new_count - 1].factors, (char *)psf->terms[i].factors) == 0 &&
            psf->terms[new_count - 1].factor_count == psf->terms[i].factor_count) {
            psf->terms[new_count - 1].coefficient += psf->terms[i].coefficient;
        } else {
            psf->terms[new_count++] = psf->terms[i];
        }
    }

    psf->term_count = 0;
    for (int i = 0; i < new_count; i++) {
        if (psf->terms[i].coefficient != 0)
            psf->terms[psf->term_count++] = psf->terms[i];
    }
}

// Функция вывода PS-формы
void print_psform(PSForm *psf) {
    if (psf->term_count == 0) {
        printf("0\n");
        return;
    }

    for (int i = 0; i < psf->term_count; i++) {
        if (i > 0) {
            if (psf->terms[i].coefficient < 0) {
                printf(" - ");
            } else {
                printf(" + ");
            }
        } else {
            if (psf->terms[i].coefficient < 0) {
                printf("-");
            }
        }

        int abs_coeff = abs(psf->terms[i].coefficient);
        if (abs_coeff != 1 || psf->terms[i].factor_count == 0)
            printf("%d", abs_coeff);
        
        for (int j = 0; j < psf->terms[i].factor_count; j++) {
            printf("%s", psf->terms[i].factors[j]);
        }
    }
    printf("\n");
}

// Функция проверки равенства PS-форм
int are_equal(PSForm *psf1, PSForm *psf2) {
    if (psf1->term_count != psf2->term_count)
        return 0;

    for (int i = 0; i < psf1->term_count; i++) {
        if (psf1->terms[i].coefficient != psf2->terms[i].coefficient)
            return 0;
        if (strcmp((char *)psf1->terms[i].factors, (char *)psf2->terms[i].factors) != 0)
            return 0;
    }
    return 1;
}

// Основная программа
int main() {
    char operation;
    char input1[MAX_LENGTH], input2[MAX_LENGTH];

    scanf(" %c", &operation);
    scanf(" %[^\n]", input1);
    scanf(" %[^\n]", input2);

    PSForm ps1, ps2;
    parse_psform(input1, &ps1);
    parse_psform(input2, &ps2);

    simplify_psform(&ps1);
    simplify_psform(&ps2);

    print_psform(&ps1);
    print_psform(&ps2);

    if (operation == '=') {
        if (are_equal(&ps1, &ps2))
            printf("equal\n");
        else
            printf("not equal\n");
    }

    return 0;
}
