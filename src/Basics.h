#ifndef SOLUCION_BASICS_H
#define SOLUCION_BASICS_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

typedef string Variable;
typedef string Rutina;
typedef int Instante;

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
