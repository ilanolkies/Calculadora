
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
DiccionarioString<T>::~DiccionarioString() {
    borrar_nodo(raiz);
}

template <typename T>
typename DiccionarioString<T>::Iterator DiccionarioString<T>::agregar(string clave, T &valor){
    stack<Nodo*> p = buscar_pila(clave);
    Nodo* res = p.top();
    p.pop();
    if (res != NULL && res->definicion != NULL) {
        *(res->definicion) = valor;
        return Iterator(res);
    } else {
        if (res == NULL) {
            res = p.top();
            p.pop();
        }
        int key_pos = p.size();
        while (key_pos < clave.size()) {
            res->siguientes[int(clave[key_pos])] = new Nodo();
            res = res->siguientes[int(clave[key_pos])];
            key_pos++;
        }
        res->definicion = new T(valor);
        _size++;
        return Iterator(res);
    }
}

template <typename T>
typename DiccionarioString<T>::Iterator DiccionarioString<T>::buscar(string clave) {
    stack<Nodo*> p = buscar_pila(clave);
    Nodo* res = p.top();
    return Iterator(res);
}

template <typename T>
DiccionarioString<T>::Iterator::Iterator(Nodo *nodo) : nodo(nodo) {}

template <typename T>
DiccionarioString<T>::Iterator::Iterator() : nodo(NULL) {}

template <typename T>
T& DiccionarioString<T>::Iterator::operator*() {
    return *(nodo->definicion);
}

template <typename T>
stack< typename DiccionarioString<T>::Nodo* > DiccionarioString<T>::buscar_pila(const string& word){
    Nodo* actual = raiz;
    int pos_actual = 0;
    stack<Nodo*> p;
    p.push(actual);
    while (actual != NULL && pos_actual < word.size()) {
        actual = actual->siguientes[int(word[pos_actual])];
        p.push(actual);
        pos_actual++;
    }
    return p;
}

template <typename T>
void DiccionarioString<T>::borrar_nodo(DiccionarioString<T>::Nodo *nodo) {
    for (int x = 0; x < SIZE; ++x) {
        if (nodo->siguientes[x] != NULL) {
            borrar_nodo(nodo->siguientes[x]);
            nodo->siguientes[x] = NULL;
        }
    }
    if (nodo->definicion != NULL)
        delete nodo->definicion;
    delete[] nodo->siguientes;
    delete nodo;
}