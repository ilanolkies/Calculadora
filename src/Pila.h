#ifndef SOLUCION_PILA_H
#define SOLUCION_PILA_H

#include "Basics.h"

class Pila {
private:
    vector<int> _pila;
    int _size = 0;
public:
    void push(int i);
    int pop();
    int size();
};

#endif //SOLUCION_PILA_H
