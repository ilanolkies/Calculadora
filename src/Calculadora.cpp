#include "Calculadora.h"

// INSTRUCCION CALCULADORA

Calculadora::InstruccionCalculadora::InstruccionCalculadora(Instruccion i) :
    operacion(i.op()),
    num(i.constanteNumerica()),
    var(i.nombreVariable()),
    rutina(i.nombreRutina()) {}

Operacion Calculadora::InstruccionCalculadora::op() {
    return operacion;
}

int Calculadora::InstruccionCalculadora::constanteNumerica() {
    return num;
}

Variable& Calculadora::InstruccionCalculadora::nombreVariable() {
    return var;
}

Rutina& Calculadora::InstruccionCalculadora::nombreRutina() {
    return rutina;
}

void Calculadora::InstruccionCalculadora::agregarIteradorVariables(IteradorVariables it) {
    it_variable = it;
}

void Calculadora::InstruccionCalculadora::agregarIteradorRutinas(IteradorRutinas it) {
    it_rutina = it;
}

Calculadora::IteradorVariables Calculadora::InstruccionCalculadora::obtenerIteradorVariables() {
    return it_variable;
}

Calculadora::IteradorRutinas Calculadora::InstruccionCalculadora::obtenerIteradorRutinas() {
    return it_rutina;
}

// PILA

void Calculadora::Pila::push(int elem) {
    pila.push(elem);
}

int Calculadora::Pila::top() {
    return pila.top();
}

void Calculadora::Pila::pop() {
    pila.pop();
}

int Calculadora::Pila::size() {
    return pila.size();
}

const stack<int>& Calculadora::Pila::getStack() {
    return pila;
}

// CALCULADORA

Calculadora::Calculadora(Rutina rutina_inicial, int capacidad_de_ventana) {

}

bool Calculadora::finalizo() {
    return !ejecutando;
}

void Calculadora::ejeutar() {

}

void Calculadora::asignarVariable(Variable v, int valor) {

}

Instante Calculadora::instanteActual() {
    return instante_actual;
}

Rutina& Calculadora::rutinaActual() {
    return nombre_rutina_actual;
}

int Calculadora::indiceActual() {
    return indice_instruccion_actual;
}

int Calculadora::valorVariable(Variable v, Instante instante) {

}

int Calculadora::valorActual(Variable v) {

}

const stack<int>& Calculadora::pila() {
    return _pila.getStack();
}