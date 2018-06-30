#ifndef SOLUCION_INSTRUCCIONCALCULADORA_H
#define SOLUCION_INSTRUCCIONCALCULADORA_H

#include "Basics.h"

class InstruccionCaculadora {
    Operacion operacion;
    int num;
    Variable var;
    Rutina rutina;
    iteradorVariables it_variable;
    iteradorRutinas it_rutina;

    InstruccionCaculadora();
    Operacion op();
    int constanteNumerica();
    Variable nombreVariable();
    Rutina nombreRutina();
    void agregarIteradorVariables(iteradorVariables it);
    void agregarIteradorRutinas(iteradorRutinas it);
    iteradorVariables obtenerIteradorVariables();
    iteradorRutinas obtenerIteradorRutinas();
};

#endif //SOLUCION_INSTRUCCIONCALCULADORA_H
