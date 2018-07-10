#include "gtest/gtest.h"
#include "../src/Programa.h"

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