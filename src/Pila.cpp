#include "Pila.h"

void Pila::push(int elem) {
    pila.push(elem);
}

int Pila::pop() {
    if(pila.size()) {
        int top = pila.top();
        pila.pop();
        return top;
    }
    return 0;
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