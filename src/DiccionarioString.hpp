
template <typename T>
DiccionarioString<T>::Nodo::Nodo() {
    definicion = NULL;
    siguientes = new Nodo*[SIZE]();
    for (int x = 0; x < SIZE; x++) {
        siguientes[x] = NULL;
    }
}

template <typename T>
DiccionarioString<T>::Nodo::Nodo(const T &def) {
    definicion = new T(def);
    siguientes = new Nodo*[SIZE];
    for (int x = 0; x < SIZE; x++) {
        siguientes[x] = NULL;
    }
}

template <typename T>
DiccionarioString<T>::DiccionarioString() {
    _size = 0;
    raiz = new Nodo();
}

template <typename T>
DiccionarioString<T>::Iterator DiccionarioString<T>::agregar(string clave, T &valor){
    stack p = buscar_pila(clave);
    Nodo* res = p.back();
    p.pop_back();
    if (res != NULL && res->definicion != NULL) {
        *(res->definicion) = valor;
        return Iterator(res);
    } else {
        if (res == NULL) {
            res = p.back();
            p.pop_back();
        }
        int key_pos = p.size();
        while (key_pos < clave.size()) {
            res->siguientes[int(clave[key_pos])] = new Nodo();
            res = res->siguientes[int(clave[key_pos])];
            key_pos++;
        }
        res->definicion = new T();
        _size++;
        *(res->definicion) = valor;
        return Iterator(res);
    }
}

template <typename T>
DiccionarioString<T>::Iterator DiccionarioString<T>::buscar(string clave) {
    stack p = buscar_pila(clave);
    Nodo* res = p.back();
    return Iterator(res);
}

template <typename T>
DiccionarioString::Iterator::Iterator(Nodo *nodo) : nodo(nodo) {}

template <typename T>
DiccionarioString::Iterator::Iterator() : nodo(NULL) {}

template <typename T>
T& DiccionarioString::Iterator::operator*() {
    return nodo->definicion;
}

template <typename T>
stack DiccionarioString<T>::buscar_pila(const string& word){
    Nodo* actual = raiz;
    int pos_actual = 0;
    stack p;
    p.push_back(actual);
    while (actual != NULL && pos_actual < word.size()) {
        actual = actual->siguientes[int(word[pos_actual])];
        p.push_back(actual);
        pos_actual++;
    }
    return p;
}