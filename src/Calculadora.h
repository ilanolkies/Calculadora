//
// Created by dylan on 30 jun 2018.
//

#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H

#include "Basics.h"
#include "Programa.h"
#include "DiccionarioString.h"
#include "Ventana.h"

class Calculadora {
private:
    typedef vector<InstruccionCaculadora> ConjInstrucciones;

    struct ValorVariable {
        Instante instante;
        int valor;
    };

    struct InfoVariables {
        Ventana<ValorVariable> ventana;
        list<ValorVariable> lista;
    };

    typedef DiccionarioString<ConjInstrucciones> DiccionarioRutinas;
    typedef DiccionarioString<InfoVariables> DiccionarioVariables;
    typedef DiccionarioRutinas::Iterator IteradorRutinas;
    typedef DiccionarioVariables::Iterator IteradorVariables;

    Programa programa;
    DiccionarioRutinas rutinas;
    DiccionarioVariables variables;
    Pila _pila;
    IteradorRutinas rutina_actual;
    int indice_instruccion_actual;
    Instante instante_actual;
    Rutina nombre_rutina_actual;
    bool ejecutando;

    class InstruccionCaculadora {
    private:
        Operacion operacion;
        int num;
        Variable var;
        Rutina rutina;
        IteradorVariables it_variable;
        IteradorRutinas it_rutina;
    public:
        InstruccionCaculadora();
        Operacion op();
        int constanteNumerica();
        Variable& nombreVariable();
        Rutina& nombreRutina();
        void agregarIteradorVariables(IteradorVariables it);
        void agregarIteradorRutinas(IteradorRutinas it);
        IteradorVariables obtenerIteradorVariables();
        IteradorRutinas obtenerIteradorRutinas();
    };

    class Pila {
    private:
        stack pila;
    public:
        void push();
        void top();
        void pop();
        int size();
        const stack& getStack();
    };
public:
    Calculadora(Rutina rutina_inicial, int capacidad_de_ventana);
    bool finalizo();
    void ejeutar();
    void asignarVariable(Variable v, int valor);
    Instante instanteActual();
    Rutina& rutinaActual();
    int indiceActual();
    int valorVariable(Variable v, Instante instante);
    int valorActual(Variable v);
    const stack& pila();
};

#endif //SOLUCION_CALCULADORA_H
