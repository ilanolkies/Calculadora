//
// Created by dylan on 30 jun 2018.
//

#ifndef SOLUCION_PILA_H
#define SOLUCION_PILA_H

#include "Basics.h"

class Pila {
private:
    vector<int> pila;
public:
    void push();
    void top();
    void pop();
    int size();
};

#endif //SOLUCION_PILA_H
