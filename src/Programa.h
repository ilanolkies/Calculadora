//
// Created by dylan on 30 jun 2018.
//

#ifndef SOLUCION_PROGRAMA_H
#define SOLUCION_PROGRAMA_H

#include "Basics.h"
#include "Instruccion.h"

struct EstructuraRutina {
    Rutina rutina;
    vector<Instruccion> instrucciones;
};

class Programa {
private:
    vector<EstructuraRutina> rutinas;
public:
    Programa();
    void agregarInstruccion(Rutina r, Instruccion i);
    vector<Instruccion> obtenerInstrucciones(Rutina r);
    int longitudPrograma();
    int longitudRutina(Rutina r);
    int longitudTotal();
    Rutina obtenerRutina(int i);
    iterator begin();
    iterator end();

    class iterator {
    private:
        vector<EstructuraRutina> *rutinas;
        int rutina;

        iterator(vector<EstructuraRutina> *rutinas, int rutina);
    public:
        void operator++();
        void operator--();
        void operator*();
    };
};

#endif //SOLUCION_PROGRAMA_H
