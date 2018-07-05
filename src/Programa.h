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
    vector<Instruccion>& obtenerInstrucciones(Rutina r);
    int longitudPrograma();
    int longitudRutina(Rutina r);
    int longitudTotal();
    Rutina obtenerRutina(int i);
    Iterator begin();
    Iterator end();

    class Iterator {
    private:
        friend class Programa;

        vector<EstructuraRutina> *rutinas;
        int rutina;

        Iterator(vector<EstructuraRutina> *rutinas, int rutina);
    public:
        EstructuraRutina& operator++();
        EstructuraRutina& operator--();
        EstructuraRutina& operator*();
    };
};

#endif //SOLUCION_PROGRAMA_H
