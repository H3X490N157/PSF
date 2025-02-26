#pragma once
#include "nodes.h"

int are_equal(TermNode *head1, TermNode *head2) {//проверка равенства путём поочерёдного сравнения всех одночленов обоих многочленов до первого несовпадения
    while (head1 && head2) {
        if (head1->coefficient != head2->coefficient ||
            compare_factors(head1->factors, head2->factors) != 0)
            return 0;
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1 == head2;
}