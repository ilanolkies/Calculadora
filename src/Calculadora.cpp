#include "Calculadora.h"

// INSTRUCCION CALCULADORA

Calculadora::InstruccionCaculadora::InstruccionCaculadora(Instruccion i) :
    operacion(i.op()),
    num(i.constanteNumerica()),
    var(i.nombreVariable()),
    rutina(i.nombreRutina()) {}

Operacion Calculadora::InstruccionCaculadora::op() {
    return operacion;
}

int Calculadora::InstruccionCaculadora::constanteNumerica() {
    return num;
}

Variable& Calculadora::InstruccionCaculadora::nombreVariable() {
    return var;
}

Rutina& Calculadora::InstruccionCaculadora::nombreRutina() {
    return rutina;
}

void Calculadora::InstruccionCaculadora::agregarIteradorVariables(IteradorVariables it) {
    it_variable = it;
}

void Calculadora::InstruccionCaculadora::agregarIteradorRutinas(IteradorRutinas it) {
    it_rutina = it;
}

IteradorVariables Calculadora::InstruccionCaculadora::obtenerIteradorVariables() {
    return it_variable;
}

IteradorRutinas Calculadora::InstruccionCaculadora::obtenerIteradorRutinas() {
    return it_rutina;
}