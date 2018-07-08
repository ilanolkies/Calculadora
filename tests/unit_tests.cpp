#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"
#include "../src/DiccionarioString.h"

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
