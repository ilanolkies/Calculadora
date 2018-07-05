
#include "Instruccion.h"

Instruccion::Instruccion(Operacion o, int n, Variable v, Rutina r) : operacion(o), num(n), var(v), rutina(r) {}

Operacion Instruccion::op() {
    return operacion;
}

int Instruccion::constanteNumerica() {
    return num;
}

Variable Instruccion::nombreVariable() {
    return var;
}

Rutina Instruccion::nombreRutina() {
    return rutina;
}