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
    Instruccion(Operacion o) : operacion(o) {};
    Instruccion(Operacion o, int n) : operacion(o), num(n) {};
    Instruccion(Operacion o, string v) : operacion(o), var(v), rutina(v) {};
    Operacion op() const;
    int constanteNumerica() const;
    Variable nombreVariable() const;
    Rutina nombreRutina() const;
};

#endif //SOLUCION_INSTRUCCION_H
