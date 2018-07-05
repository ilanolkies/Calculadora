//
// Created by dylan on 30 jun 2018.
//

#ifndef SOLUCION_DICCIONARIOSTRING_H
#define SOLUCION_DICCIONARIOSTRING_H

#include "Basics.h"

template <typename T>
class DiccionarioString {
private:
    struct Nodo {
        Nodo();
        Nodo(const T& def);

        Nodo** siguientes;
        T* definicion;
    };

    stack buscar_pila(const string& clave);

    Nodo* raiz;
    int _size;
public:
    DiccionarioString();
    Iterator agregar(string clave, T& valor);
    Iterator buscar(string clave);

    class Iterator {
    private:
        friend class DiccionarioString<T>;

        Nodo* nodo;
        Iterator(Nodo* nodo);
    public:
        Iterator();
        T& operator*();
    };
};

#include "DiccionarioString.hpp"

#endif //SOLUCION_DICCIONARIOSTRING_H
