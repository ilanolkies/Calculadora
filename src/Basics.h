#ifndef SOLUCION_BASICS_H
#define SOLUCION_BASICS_H

#include <iostream>
using namespace std;

typedef string Variable;
typedef string Rutina;

enum Operacion {
    PUSH,
    ADD,
    SUB,
    MUL,
    READ,
    WRITE,
    JUMP,
    JUMPZ
};

#endif //SOLUCION_BASICS_H
