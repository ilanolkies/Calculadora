#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"
#include "../src/DiccionarioString.h"
#include "../src/Pila.h"
#include "../src/Calculadora.h"

//INSTRUCCION
TEST(test_instruccion, add) {
    Instruccion *instruccion = new Instruccion(ADD);

    ASSERT_EQ(instruccion->op(), ADD);
}

TEST(test_instruccion, sub) {
    Instruccion *instruccion = new Instruccion(SUB);

    ASSERT_EQ(instruccion->op(), SUB);
}

TEST(test_instruccion, mul) {
    Instruccion *instruccion = new Instruccion(MUL);

    ASSERT_EQ(instruccion->op(), MUL);
}

TEST(test_instruccion, jump) {
    Instruccion *instruccion = new Instruccion(JUMP, "rutina");

    ASSERT_EQ(instruccion->op(), JUMP);
    ASSERT_EQ(instruccion->nombreRutina(), "rutina");
}

TEST(test_instruccion, jumpz) {
    Instruccion *instruccion = new Instruccion(JUMPZ, "rutina");

    ASSERT_EQ(instruccion->op(), JUMPZ);
    ASSERT_EQ(instruccion->nombreRutina(), "rutina");
}

TEST(test_instruccion, push) {
    Instruccion *instruccion = new Instruccion(PUSH, 10);

    ASSERT_EQ(instruccion->op(), PUSH);
    ASSERT_EQ(instruccion->constanteNumerica(), 10);
}

TEST(test_instruccion, read) {
    Instruccion *instruccion = new Instruccion(READ, "x");

    ASSERT_EQ(instruccion->op(), READ);
    ASSERT_EQ(instruccion->nombreVariable(), "x");
}

TEST(test_instruccion, write) {
    Instruccion *instruccion = new Instruccion(WRITE, "x");

    ASSERT_EQ(instruccion->op(), WRITE);
    ASSERT_EQ(instruccion->nombreVariable(), "x");
}

//PROGRAMA
const vector<string> rutinas = {"a", "b", "c"};

TEST(test_programa, vacia) {
    Programa *p = new Programa;

    for (int i = 0; i < rutinas.size(); ++i)
        ASSERT_EQ(p->longitudRutina(rutinas[i]), 0);

    ASSERT_EQ(p->longitudTotal(), 0);

    ASSERT_EQ(p->longitudPrograma(), 0);

    auto it = p->begin();
    ASSERT_FALSE(it != p->end());
}

TEST(test_programa, una_insturccion) {
    Programa *p = new Programa;

    for (int i = 0; i < rutinas.size(); ++i)
        ASSERT_EQ(p->longitudRutina(rutinas[i]), 0);

    ASSERT_EQ(p->longitudTotal(), 0);

    ASSERT_EQ(p->longitudPrograma(), 0);

    p->agregarInstruccion("a", Instruccion(ADD));

    ASSERT_EQ(p->obtenerInstrucciones("a").size(), 1);
    ASSERT_EQ(p->obtenerInstrucciones("a")[0].op(), ADD);

    ASSERT_EQ(p->longitudPrograma(), 1);
    ASSERT_EQ(p->longitudRutina("a"), 1);
    ASSERT_EQ(p->longitudTotal(), 1);
    ASSERT_EQ(p->obtenerRutina(0), "a");

    auto it = p->begin();
    ASSERT_TRUE(it != p->end());
    ASSERT_EQ((*it).instrucciones[0].op(), ADD);
    ++it;
    ASSERT_FALSE(it != p->end());
}

TEST(test_programa, dos_insturcciones) {
    Programa *p = new Programa;

    for (int i = 0; i < rutinas.size(); ++i)
        ASSERT_EQ(p->longitudRutina(rutinas[i]), 0);

    ASSERT_EQ(p->longitudTotal(), 0);

    ASSERT_EQ(p->longitudPrograma(), 0);

    p->agregarInstruccion("a", Instruccion(ADD));
    p->agregarInstruccion("a", Instruccion(MUL));

    ASSERT_EQ(p->obtenerInstrucciones("a").size(), 2);
    ASSERT_EQ(p->obtenerInstrucciones("a")[0].op(), ADD);
    ASSERT_EQ(p->obtenerInstrucciones("a")[1].op(), MUL);

    ASSERT_EQ(p->longitudPrograma(), 1);
    ASSERT_EQ(p->longitudRutina("a"), 2);
    ASSERT_EQ(p->longitudTotal(), 2);
    ASSERT_EQ(p->obtenerRutina(0), "a");

    auto it = p->begin();
    ASSERT_TRUE(it != p->end());
    ASSERT_EQ((*it).instrucciones[0].op(), ADD);
    ASSERT_EQ((*it).instrucciones[1].op(), MUL);
    ++it;
    ASSERT_FALSE(it != p->end());
}

TEST(test_programa, dos_rutinas) {
    Programa *p = new Programa;

    for (int i = 0; i < rutinas.size(); ++i)
        ASSERT_EQ(p->longitudRutina(rutinas[i]), 0);

    ASSERT_EQ(p->longitudTotal(), 0);

    ASSERT_EQ(p->longitudPrograma(), 0);

    p->agregarInstruccion("a", Instruccion(ADD));
    p->agregarInstruccion("b", Instruccion(MUL));

    ASSERT_EQ(p->obtenerInstrucciones("a").size(), 1);
    ASSERT_EQ(p->obtenerInstrucciones("a")[0].op(), ADD);

    ASSERT_EQ(p->obtenerInstrucciones("b").size(), 1);
    ASSERT_EQ(p->obtenerInstrucciones("b")[0].op(), MUL);

    ASSERT_EQ(p->longitudPrograma(), 2);
    ASSERT_EQ(p->longitudRutina("a"), 1);
    ASSERT_EQ(p->longitudRutina("b"), 1);
    ASSERT_EQ(p->longitudTotal(), 2);
    ASSERT_EQ(p->obtenerRutina(0), "a");
    ASSERT_EQ(p->obtenerRutina(1), "b");

    auto it = p->begin();
    ASSERT_TRUE(it != p->end());
    ASSERT_EQ((*it).instrucciones[0].op(), ADD);
    ++it;
    ASSERT_TRUE(it != p->end());
    ASSERT_EQ((*it).instrucciones[0].op(), MUL);
    ++it;
    ASSERT_FALSE(it != p->end());
}

//DICIONARIO STRING
TEST(test_dicc_string, vacio) {
    DiccionarioString<int> *dicc = new DiccionarioString<int>;

    ASSERT_TRUE(dicc->buscar("a") == dicc->end());
}

TEST(test_dicc_string, un_elemento) {
    DiccionarioString<int> *dicc = new DiccionarioString<int>;

    ASSERT_TRUE(dicc->buscar("a") == dicc->end());

    int v(10);
    dicc->agregar("clave", v);
    ASSERT_EQ(*dicc->buscar("clave"), v);
}

TEST(test_dicc_string, dos_elementos) {
    DiccionarioString<int> *dicc = new DiccionarioString<int>;

    ASSERT_TRUE(dicc->buscar("a") == dicc->end());

    int v1(10);
    dicc->agregar("clave1", v1);
    ASSERT_EQ(*dicc->buscar("clave1"), v1);

    int v2(20);
    dicc->agregar("clave2", v2);
    ASSERT_EQ(*dicc->buscar("clave2"), v2);
}

TEST(test_dicc_string, mismo_elemento) {
    DiccionarioString<int> *dicc = new DiccionarioString<int>;

    ASSERT_TRUE(dicc->buscar("a") == dicc->end());

    int v(10);
    dicc->agregar("clave", v);
    ASSERT_EQ(*dicc->buscar("clave"), v);

    int v2(20);
    dicc->agregar("clave", v2);
    ASSERT_EQ(*dicc->buscar("clave"), v2);
}

TEST(test_dicc_string, aliasing) {
    DiccionarioString<int> *dicc = new DiccionarioString<int>;

    ASSERT_TRUE(dicc->buscar("a") == dicc->end());

    int v(10);
    dicc->agregar("clave", v);
    ASSERT_EQ(*dicc->buscar("clave"), v);

    *dicc->buscar("clave") = 20;
    ASSERT_EQ(*dicc->buscar("clave"), 20);
    ASSERT_EQ(v, 10);
}

//PILA
TEST(test_pila, vacia) {
    Pila *p = new Pila;

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);
}

TEST(test_pila, un_elemento) {
    Pila *p = new Pila;

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);

    p->push(10);

    ASSERT_EQ(p->size(), 1);
    ASSERT_EQ(p->top(), 10);
    ASSERT_EQ(p->getStack().size(), 1);
    ASSERT_EQ(p->getStack().top(), 10);
    ASSERT_EQ(p->getStack().empty(), false);
}

TEST(test_pila, un_elemento_pop) {
    Pila *p = new Pila;

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);

    p->push(10);

    ASSERT_EQ(p->size(), 1);
    ASSERT_EQ(p->top(), 10);
    ASSERT_EQ(p->getStack().size(), 1);
    ASSERT_EQ(p->getStack().top(), 10);
    ASSERT_EQ(p->getStack().empty(), false);

    int pop = p->pop();
    ASSERT_EQ(pop, 10);

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);
}

TEST(test_pila, dos_elementos) {
    Pila *p = new Pila;

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);

    p->push(10);

    ASSERT_EQ(p->size(), 1);
    ASSERT_EQ(p->top(), 10);
    ASSERT_EQ(p->getStack().size(), 1);
    ASSERT_EQ(p->getStack().top(), 10);
    ASSERT_EQ(p->getStack().empty(), false);

    p->push(20);

    ASSERT_EQ(p->size(), 2);
    ASSERT_EQ(p->top(), 20);
    ASSERT_EQ(p->getStack().size(), 2);
    ASSERT_EQ(p->getStack().top(), 20);
    ASSERT_EQ(p->getStack().empty(), false);
}

TEST(test_pila, dos_elementos_pop) {
    Pila *p = new Pila;

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);

    p->push(10);

    ASSERT_EQ(p->size(), 1);
    ASSERT_EQ(p->top(), 10);
    ASSERT_EQ(p->getStack().size(), 1);
    ASSERT_EQ(p->getStack().top(), 10);
    ASSERT_EQ(p->getStack().empty(), false);

    p->push(20);

    ASSERT_EQ(p->size(), 2);
    ASSERT_EQ(p->top(), 20);
    ASSERT_EQ(p->getStack().size(), 2);
    ASSERT_EQ(p->getStack().top(), 20);
    ASSERT_EQ(p->getStack().empty(), false);

    int pop = p->pop();
    ASSERT_EQ(pop, 20);

    ASSERT_EQ(p->size(), 1);
    ASSERT_EQ(p->top(), 10);
    ASSERT_EQ(p->getStack().size(), 1);
    ASSERT_EQ(p->getStack().empty(), false);
    ASSERT_EQ(p->getStack().top(), 10);

    pop = p->pop();
    ASSERT_EQ(pop, 10);

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);

    ASSERT_EQ(p->pop(), 0);
}

TEST(test_pila, un_elemento_aliasing) {
    Pila *p = new Pila;

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);
    ASSERT_EQ(p->getStack().size(), 0);
    ASSERT_EQ(p->getStack().empty(), true);
    ASSERT_EQ(p->pop(), 0);

    p->push(10);

    auto s = p->getStack();

    ASSERT_EQ(p->size(), 1);
    ASSERT_EQ(p->top(), 10);

    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.empty(), false);
    ASSERT_EQ(s.top(), 10);

    int pop = p->pop();
    ASSERT_EQ(pop, 10);

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);

    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.empty(), false);
    ASSERT_EQ(s.top(), 10);

    int s_top = s.top();
    s.pop();

    ASSERT_EQ(p->size(), 0);
    ASSERT_EQ(p->top(), 0);

    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.empty(), true);
}

//CALCULADORA

vector<Operacion> ops = { PUSH, ADD, SUB, MUL, READ, WRITE, JUMP, JUMPZ };

TEST(test_calculadora, vacia) {
    Programa *p = new Programa;

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().top(), 0);
    ASSERT_EQ(c->pila().size(), 0);
    ASSERT_EQ(c->indiceActual(), 0);
    ASSERT_EQ(c->rutinaActual(), "r");
    ASSERT_EQ(c->instanteActual(), 0);
    ASSERT_EQ(c->finalizo(), true);
}

// COMPORTAMIENTO GENERAL DE UA CALCULADORA CON UNA SOLA ISNTRUCCION
TEST(test_calculadora, una_instruccion) {
    for(Operacion op : ops) {
        Programa *p = new Programa;
        if(op == ADD || op == SUB || op == MUL)
            p->agregarInstruccion("r", Instruccion(op));
        else if (op==PUSH)
            p->agregarInstruccion("r", Instruccion(op, 10));
        else if(op==READ || op == WRITE)
            p->agregarInstruccion("r", Instruccion(op, "v"));
        else if(op == JUMP || op == JUMPZ)
            p->agregarInstruccion("r", Instruccion(op, "fin"));


        Calculadora *c = new Calculadora(*p, "r", 1);

        ASSERT_EQ(c->indiceActual(), 0);
        ASSERT_EQ(c->rutinaActual(), "r");
        ASSERT_EQ(c->instanteActual(), 0);
        ASSERT_EQ(c->finalizo(), false);

        c->ejeutar();

        if(op == JUMP || op == JUMPZ) {
            ASSERT_EQ(c->indiceActual(), 0);
            ASSERT_EQ(c->rutinaActual(), "fin");
        }
        else {
            ASSERT_EQ(c->indiceActual(), 1);
            ASSERT_EQ(c->rutinaActual(), "r");
        }

        ASSERT_EQ(c->instanteActual(), 1);
        ASSERT_EQ(c->finalizo(), true);
    }
}

// COMPORTAMIENTO DETALLADO DE LA EJECUCION DE CADA INSTRUCCION
TEST(test_calculadora, push) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 10));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 10);
}

TEST(test_calculadora, add) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 15));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(ADD));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);

    c->ejeutar();
    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 25);
}

TEST(test_calculadora, sub) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 15));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(SUB));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);

    c->ejeutar();
    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 5);
}

TEST(test_calculadora, mul) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 15));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(MUL));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);

    c->ejeutar();
    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 150);
}

TEST(test_calculadora, write) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 15));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);
    ASSERT_EQ(c->valorActual("v"), 0);

    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 15);
    ASSERT_EQ(c->valorVariable("v", 0), 0);
}

TEST(test_calculadora, read) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 15));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));
    p->agregarInstruccion("r", Instruccion(READ, "v"));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);

    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 15);
    ASSERT_EQ(c->valorVariable("v", 0), 0);
    ASSERT_EQ(c->pila().top(), 0);

    c->ejeutar();

    ASSERT_EQ(c->pila().top(), 15);
}

TEST(test_calculadora, jump) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(JUMP, "s"));
    p->agregarInstruccion("s", Instruccion(PUSH, 10));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);

    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 10);
    ASSERT_EQ(c->rutinaActual(), "s");
}
