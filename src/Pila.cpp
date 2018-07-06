#include "Pila.h"

void Pila::push(int elem) {
    pila.push(elem);
}

int Pila::pop() {
    int ret = pila.top();
    pila.pop();
    return ret;
}

int Pila::size() const {
    return pila.size();
}

const stack<int>& Pila::getStack() const {
    return pila;
}

int Pila::top() const {
    return pila.size() ? pila.top() : 0;
}