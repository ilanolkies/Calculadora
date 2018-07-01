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

    class Pila {
    private:
        vector<Nodo*> p;

    public:
        void push(Nodo* item) {
            p.push_back(item);
        }

        Nodo* pop() {
            Nodo* item = p.back();
            p.pop_back();
            return item;
        }

        int size() {
            return p.size();
        }
    };

    Nodo* raiz;
    int _size;
public:
    DiccionarioString();
    iterator agregar(string clave, T& valor);
    iterator buscar(string clave);

    class iterator {
    private:
        Nodo* nodo;
        iterator(Nodo* nodo);
    public:
        T& operator*();
    };
};

#include "DiccionarioString.hpp"

#endif //SOLUCION_DICCIONARIOSTRING_H
