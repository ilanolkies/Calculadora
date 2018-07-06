
#include "Instruccion.h"

Operacion Instruccion::op() const {
    return operacion;
}

int Instruccion::constanteNumerica() const {
    return num;
}

Variable Instruccion::nombreVariable() const {
    return var;
}

Rutina Instruccion::nombreRutina() const {
    return rutina;
}