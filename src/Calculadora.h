//
// Created by dylan on 30 jun 2018.
//

#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H

#include "Basics.h"
#include "Programa.h"
#include "DiccionarioString.h"
#include "Ventana.h"
#include "Instruccion.h"

class Calculadora {
private:
    class InstruccionCalculadora;

    class Pila {
    private:
        stack<int> pila;
    public:
        void push(int elem);
        int top();
        void pop();
        int size();
        const stack<int>& getStack();
    };

    typedef vector<InstruccionCalculadora> ConjInstrucciones;

    struct ValorVariable {
        Instante instante;
        int valor;

        ValorVariable(Instante i, int v) : instante(i), valor(v) {}
    };

    struct InfoVariables {
        Ventana<ValorVariable> ventana;
        list<ValorVariable> lista;

        InfoVariables(Ventana<ValorVariable> v, list<ValorVariable> l) : ventana(v), lista(l) {}
        InfoVariables(const InfoVariables& copia) : ventana(copia.ventana), lista(copia.lista) {};
    };

    typedef DiccionarioString<ConjInstrucciones> DiccionarioRutinas;
    typedef DiccionarioString<InfoVariables> DiccionarioVariables;
    typedef DiccionarioRutinas::Iterator IteradorRutinas;
    typedef DiccionarioVariables::Iterator IteradorVariables;

    typedef Programa::Iterator IteradorPrograma;

    Programa programa;
    DiccionarioRutinas rutinas;
    DiccionarioVariables variables;
    Pila _pila;
    IteradorRutinas rutina_actual;
    int indice_instruccion_actual;
    Instante instante_actual;
    Rutina nombre_rutina_actual;
    bool ejecutando;

    class InstruccionCalculadora {
    private:
        Operacion operacion;
        int num;
        Variable var;
        Rutina rutina;
        IteradorVariables it_variable;
        IteradorRutinas it_rutina;
    public:
        InstruccionCalculadora(Instruccion i);
        Operacion op();
        int constanteNumerica();
        Variable& nombreVariable();
        Rutina& nombreRutina();
        void agregarIteradorVariables(IteradorVariables it);
        void agregarIteradorRutinas(IteradorRutinas it);
        IteradorVariables obtenerIteradorVariables();
        IteradorRutinas obtenerIteradorRutinas();
    };
public:
    Calculadora(Programa p, Rutina rutina_inicial, int capacidad_de_ventana);
    bool finalizo();
    void ejeutar();
    void asignarVariable(Variable v, int valor);
    Instante instanteActual();
    Rutina& rutinaActual();
    int indiceActual();
    int valorVariable(Variable v, Instante instante);
    int valorActual(Variable v);
    const stack<int>& pila();
};

#endif //SOLUCION_CALCULADORA_H
