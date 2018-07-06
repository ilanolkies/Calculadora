#include "Driver.h"

Driver::Driver() {
    rutina_actual = "";
}

Driver::~Driver() {
	// COMPLETAR
}

// Operaciones para agregar instrucciones

void Driver::begin(string rutina) {
    rutina_actual = rutina;
}

void Driver::end(string rutina) {
    rutina_actual = "";
}

void Driver::push(int n) {
    p.agregarInstruccion(rutina_actual, Instruccion(PUSH, n));
}

void Driver::add() {
    p.agregarInstruccion(rutina_actual, Instruccion(ADD));
}

void Driver::sub() {
    p.agregarInstruccion(rutina_actual, Instruccion(SUB));
}

void Driver::mul() {
    p.agregarInstruccion(rutina_actual, Instruccion(MUL));
}

void Driver::read(string variable) {
    p.agregarInstruccion(rutina_actual, Instruccion(READ, variable));
}

void Driver::write(string variable) {
    p.agregarInstruccion(rutina_actual, Instruccion(WRITE, variable));
}

void Driver::jump(string rutina) {
    p.agregarInstruccion(rutina_actual, Instruccion(JUMP, rutina));
}

void Driver::jumpz(string rutina) {
    p.agregarInstruccion(rutina_actual, Instruccion(JUMPZ, rutina));
}

// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {
	// COMPLETAR
}

void Driver::asignarVariable(string x, int valor) {
	// COMPLETAR
}

bool Driver::ejecucionFinalizada() const {
	// COMPLETAR
}

void Driver::ejecutarInstruccionActual() {
	// COMPLETAR
}

int Driver::topePila() const {
	// COMPLETAR
}

int Driver::valorVariable(string x) const {
	// COMPLETAR
}

int Driver::valorHistoricoVariable(string x, int t) const {
	// COMPLETAR
}

int Driver::instanteActual() const {
	// COMPLETAR
}

