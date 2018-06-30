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
    Instruccion();
    Operacion op();
    int constanteNumerica();
    Variable nombreVariable();
    Rutina nombreRutina();
};

#endif //SOLUCION_INSTRUCCION_H
