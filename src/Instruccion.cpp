
#include "Instruccion.h"

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