#pragma once 
#include "nodes.h"

int compare_factors(FactorNode *f1, FactorNode *f2) {
    while (f1 && f2) {//пока есть элементы в обоих списках, будем перемещаться к их хвостам, при расхождении - возвращаем, что списки не совпадают
        if (f1->factor != f2->factor) {
            return f1->factor - f2->factor;
        }
        f1 = f1->next;
        f2 = f2->next;
    }
    return (f1 ? 1 : 0) - (f2 ? 1 : 0);//проверка на случай, если один список кончится раньше другого осуществляется через разность тернарных операторов
}