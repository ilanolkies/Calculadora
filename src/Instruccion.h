#ifndef SOLUCION_INSTRUCCION_H
#define SOLUCION_INSTRUCCION_H

#include "Basics.h"

class Instruccion {
private:
    Operacion operacion;
    int num;
    Variable var;
    Rutina rutina;
public:
    Instruccion(Operacion o, int n, Variable v, Rutina r);
    Operacion op();
    int constanteNumerica();
    Variable nombreVariable();
    Rutina nombreRutina();
};

#endif //SOLUCION_INSTRUCCION_H
