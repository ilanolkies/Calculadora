//
// Created by Ilan on 06/07/2018.
//

#ifndef SOLUCION_PILA_H
#define SOLUCION_PILA_H

#include "Basics.h"


class Pila {
public:
    void push(int elem);
    int pop();
    int size() const;
    const stack<int>& getStack() const;
    int top() const;
private:
    stack<int> pila;
};

#endif //SOLUCION_PILA_H
