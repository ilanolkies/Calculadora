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
#include "Pila.h"

class Calculadora {
public:
    Calculadora(Programa p, Rutina rutina_inicial, int capacidad_de_ventana);

    bool finalizo() const;
    void ejeutar();
    void asignarVariable(Variable v, int valor);

    Instante instanteActual() const;
    const Rutina& rutinaActual() const;
    int indiceActual() const;
    int valorVariable(Variable v, Instante instante) const;
    int valorActual(Variable v) const;
    const Pila & pila() const;
private:
    class InstruccionCalculadora;

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
        InfoVariables(const InfoVariables& copia) : ventana(copia.ventana), lista(copia.lista) {}
        InfoVariables(const int& capacidad_de_ventana) : ventana(Ventana<ValorVariable>(capacidad_de_ventana)) {
            ventana.registrar(ValorVariable(0, 0));
        }
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
    int cap_de_ventana;

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
        Operacion op() const;
        int constanteNumerica() const;
        const Variable& nombreVariable() const;
        const Rutina& nombreRutina() const;
        void agregarIteradorVariables(IteradorVariables it);
        void agregarIteradorRutinas(IteradorRutinas it);
        IteradorVariables obtenerIteradorVariables() const;
        IteradorRutinas obtenerIteradorRutinas() const;
    };

    int busqueda_binaria(const Ventana<ValorVariable>& ventana, Instante instante) const;
};

#endif //SOLUCION_CALCULADORA_H
