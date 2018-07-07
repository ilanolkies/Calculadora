#include "Calculadora.h"
#include "Pila.h"

// INSTRUCCION CALCULADORA

Calculadora::InstruccionCalculadora::InstruccionCalculadora(Instruccion i) :
    operacion(i.op()),
    num(i.constanteNumerica()),
    var(i.nombreVariable()),
    rutina(i.nombreRutina()) {}

Operacion Calculadora::InstruccionCalculadora::op() const {
    return operacion;
}

int Calculadora::InstruccionCalculadora::constanteNumerica() const {
    return num;
}

const Variable& Calculadora::InstruccionCalculadora::nombreVariable() const {
    return var;
}

const Rutina& Calculadora::InstruccionCalculadora::nombreRutina() const {
    return rutina;
}

void Calculadora::InstruccionCalculadora::agregarIteradorVariables(IteradorVariables it) {
    it_variable = it;
}

void Calculadora::InstruccionCalculadora::agregarIteradorRutinas(IteradorRutinas it) {
    it_rutina = it;
}

Calculadora::IteradorVariables Calculadora::InstruccionCalculadora::obtenerIteradorVariables() const {
    return it_variable;
}

Calculadora::IteradorRutinas Calculadora::InstruccionCalculadora::obtenerIteradorRutinas() const {
    return it_rutina;
}

// CALCULADORA

Calculadora::Calculadora(Programa p, Rutina rutina_inicial, int capacidad_de_ventana) {
    //Inicializaciones basicas
    instante_actual = 0;
    indice_instruccion_actual = 0;
    nombre_rutina_actual = rutina_inicial;
    programa = p;
    ejecutando = p.longitudTotal() > 0 && p.longitudRutina(rutina_inicial) > 0;
    cap_de_ventana = capacidad_de_ventana;

    //Inicializamos las rutinas
    IteradorPrograma it_programa = p.begin();
    //Recorremos el programa (esto se repite #p veces)
    while (it_programa != p.end()) {
        ConjInstrucciones por_defecto;
        //Definimos el default de todas las rutinas para poder agregarles elementos, esto cuesta O(|R|)
        IteradorRutinas it = rutinas.agregar((*it_programa).rutina, por_defecto);
        //Definimos la rutina_actual si la rutina es la seleccionada para iniciar la ejecucion
        if ((*it_programa).rutina == nombre_rutina_actual) {
            rutina_actual = it;
        }
        ++it_programa;
    }

    //Comenzamos a recorrer las rutinas del programa...
    it_programa  = p.begin();
    while (it_programa != p.end()) {
        //Busco la rutina en el diccionario para poder agregarle las instrucciones (esto cuesta O(|R|))
        IteradorRutinas rutina_act = rutinas.buscar((*it_programa).rutina);
        //Para cada rutina recorremos las instrucciones
        for(int i = 0; i < (*it_programa).instrucciones.size(); i++) {
            //Esto se va a repetir #p veces
            Instruccion instruccion = (*it_programa).instrucciones[i];
            InstruccionCalculadora nueva_instruccion = InstruccionCalculadora(instruccion);
            if (instruccion.op() == READ || instruccion.op() == WRITE) {
                // Si son instrucciones que utilizan variables:
                // - Agregamos las variables al trie con un valor inicial en cero
                //(Esto cuesta O(|V|))
                // - Guardamos en la instruccion el iterador a esa variable
                //asi consultarla es O(1)
                InfoVariables Nodo = InfoVariables(capacidad_de_ventana);
                IteradorVariables it_variables = variables.agregar(instruccion.nombreVariable(), Nodo);
                nueva_instruccion.agregarIteradorVariables(it_variables);
            }
            if (instruccion.op() == JUMP || instruccion.op() == JUMPZ) {
                // Si son instrucciones que utilizan rutinas:
                // Guardamos en la instruccion el iterador a la rutina correspondiente
                // (Esto cuesta O(|R|) porque hay que buscarla)
                // Si la rutina no existe, el iterador es el end(p)
                Rutina r = instruccion.nombreRutina();
                IteradorRutinas it_rutina = rutinas.buscar(r);
                nueva_instruccion.agregarIteradorRutinas(it_rutina);
            }
            // Agregar al vector es O(1) amortizado
            // Pero como agregamos todas las instrucciones juntas, es O(#instrucciones) en total
            (*rutina_act).push_back(nueva_instruccion);
        }
        ++it_programa;
    }
}

bool Calculadora::finalizo() const {
    return !ejecutando;
}

void Calculadora::ejeutar() {
    InstruccionCalculadora i = (*rutina_actual)[indice_instruccion_actual];
    switch(i.op()) {
        case PUSH: {
            _pila.push(i.constanteNumerica());
            break;
        } case ADD: {
            _pila.push(_pila.pop() + _pila.pop());
            break;
        } case SUB: {
            int first = _pila.pop();
            int second = _pila.pop();
            _pila.push(second - first);
            break;
        } case MUL: {
            _pila.push(_pila.pop() * _pila.pop());
            break;
        } case READ: {
            // Ya tenemos el iterador que apunta a la ventana de instantes asi que buscamos el ultimo
            // instante y lo agregamos a la pila
            IteradorVariables variable = i.obtenerIteradorVariables();
            _pila.push((*variable).ventana[(*variable).ventana.tam() - 1].valor);
            break;
        } case WRITE: {
            // Ya tenemos el iterador a la ventana y a la lista asi que agregamos el instante actual con el valor extraido de la pila
            int valor = _pila.pop();
            (*i.obtenerIteradorVariables()).ventana.registrar(ValorVariable(instante_actual, valor));
            (*i.obtenerIteradorVariables()).lista.push_back(ValorVariable(instante_actual, valor));
            break;
        } case JUMP: {
            // Ya tenemos el iterador de la rutina en la instruccion asi que lo buscamos y lo seteamos como rutina actual
            // Si el iterador es end() entonces es una rutina invalida asi que terminamos el programa
            // Definimos la instruccion actual en -1 porque al final hay un instruccion_actual++ y asi la prox instruccion es cero
            nombre_rutina_actual = i.nombreRutina();

            rutina_actual = i.obtenerIteradorRutinas();
            if (rutina_actual == rutinas.end()) {
                ejecutando = false;
            }
            indice_instruccion_actual = -1;
            break;
        } case JUMPZ: {
            // Igual que el jump pero verificando la pila
            if (_pila.pop() == 0) {
                nombre_rutina_actual = i.nombreRutina();
                rutina_actual = i.obtenerIteradorRutinas();
                if (rutina_actual == rutinas.end()) {
                    ejecutando = false;
                }
                indice_instruccion_actual = -1;
            }
            break;
        }
    }
    // Aumentamos instruccion actual e instante
    indice_instruccion_actual++;
    instante_actual++;
    // Si termino la rutina, termino el programa
    if (rutina_actual == rutinas.end() || indice_instruccion_actual >= (*rutina_actual).size())
        ejecutando = false;
}

void Calculadora::asignarVariable(Variable v, int valor) {
    // Buscamos la variable y le agregamos a la ventana y a la lista un nuevo valor en el instante actual (buscarla cuesta O(|x|))
    ValorVariable variable = ValorVariable(instante_actual, valor);

    IteradorVariables var = variables.buscar(v);
    if (var == variables.end()) {
        InfoVariables nuevo(cap_de_ventana);
        var = variables.agregar(v, nuevo);
    }
    (*var).ventana.registrar(variable);
    (*var).lista.push_back(variable);
}

Instante Calculadora::instanteActual() const {
    return instante_actual;
}

const Rutina& Calculadora::rutinaActual() const {
    return nombre_rutina_actual;
}

int Calculadora::indiceActual() const {
    return indice_instruccion_actual;
}

int Calculadora::valorVariable(Variable v, Instante instante) const {
    // Buscamos la variable en el trie O(|nombre|)
    IteradorVariables var = variables.buscar(v);
    // Si el instante buscado es mayor que el primer instante de la ventana, entonces esta
    // Porque los instantes estan ordenados de menor a mayor ya que los agregamos asi. Por eso tambien podemos usar busqueda binaria
    if (instante >= (*var).ventana[0].instante) {
        // Busqueda binaria en la ventana con las ultimas <capacidad de ventana> veces que se modifico
        // O(log(capacidad de ventana))
        int pos_resultado = busqueda_binaria((*var).ventana, instante);
        return (*var).ventana[pos_resultado].valor;
    } else {
        //Esto significa que no esta en la ventana asi que hay que buscarlo en la lista, esto es O(instante_actual) pero no me importa
        list<ValorVariable>& l = (*var).lista;
        list<ValorVariable>::iterator actual = l.begin();

        while (actual != l.end()) {
            if ((*actual).instante == instante)
                return (*actual).valor;
            else if ((*actual).instante > instante) {
                actual--;
                return (*actual).valor;
            }
            actual++;
        }

        return 0;
    }
}

int Calculadora::busqueda_binaria(const Ventana<ValorVariable>& ventana, Instante instante) const {
    // UN EJEMPLITO
    // instante = 6
    // 1 3 5 8 99 100 200 1500
    // L                   R
    // L     R
    //   L   R
    //     L R
    // DEVUELVE EL MENOR NUMERO MAS CERCANO
    int L = 0;
    int R = ventana.tam();
    while (R - L > 1) {
        if (instante >= ventana[L + (R - L) / 2].instante)
            L = L + (R - L) / 2;
        else
            R = L + (R - L) / 2;
    }
    return L;
}

int Calculadora::valorActual(Variable v) const {
    //Buscamos la variable y devolvemos el valor del ultimo instante en que se modifico
    IteradorVariables var = variables.buscar(v);
    return (*var).ventana[(*var).ventana.tam()-1].valor;
}

const Pila & Calculadora::pila() const {
    return _pila;
}