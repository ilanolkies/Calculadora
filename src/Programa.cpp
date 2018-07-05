#include "Programa.h"

Programa::Programa() {

}

void Programa::agregarInstruccion(Rutina r, Instruccion i) {
    bool agregado = false;
    for(int x = 0; x < longitudPrograma() && !agregado; x++) {
        if (rutinas[x].rutina == r) {
            rutinas[x].instrucciones.push_back(i);
            agregado = true;
        }
    }
    if (!agregado) {
        EstructuraRutina nueva_rutina;
        nueva_rutina.rutina = r;
        nueva_rutina.instrucciones.push_back(i);
        rutinas.push_back(nueva_rutina);
    }
}

vector<Instruccion>& Programa::obtenerInstrucciones(Rutina r) {
    for(int i = 0; i < longitudPrograma(); i++) {
        if (rutinas[i].rutina == r) {
            return rutinas[i].instrucciones;
        }
    }
}

int Programa::longitudPrograma() {
    return (int)rutinas.size();
}

int Programa::longitudRutina(Rutina r) {
    for(int i = 0; i < longitudPrograma(); i++) {
        if (rutinas[i].rutina == r) {
            return (int)rutinas[i].instrucciones.size();
        }
    }
}

int Programa::longitudTotal() {
    int res = 0;
    for(int i = 0; i < longitudPrograma(); i++) {
        res += rutinas[i].instrucciones.size();
    }
}

Rutina Programa::obtenerRutina(int i) {
    return rutinas[i].rutina;
}

Programa::Iterator Programa::begin() {
    return Iterator(&rutinas, 0);
}

Programa::Iterator Programa::end() {
    return Iterator(&rutinas, (int)rutinas.size());
}

Programa::Iterator::Iterator(vector<EstructuraRutina> *rutinas, int rutina) : rutinas(rutinas), rutina(rutina) {}

EstructuraRutina& Programa::Iterator::operator++() {
    rutina++;
    return (*rutinas)[rutina];
}

EstructuraRutina& Programa::Iterator::operator--() {
    rutina--;
    return (*rutinas)[rutina];
}

EstructuraRutina& Programa::Iterator::operator*() {
    return (*rutinas)[rutina];
}