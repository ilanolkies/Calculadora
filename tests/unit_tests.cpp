#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"

//INSTRUCCION

TEST(test_instruccion, add){
    Instruccion* instruccion = new Instruccion(ADD);

    ASSERT_EQ(instruccion->op(), ADD);
}

TEST(test_instruccion, sub){
    Instruccion* instruccion = new Instruccion(SUB);

    ASSERT_EQ(instruccion->op(), SUB);
}

TEST(test_instruccion, mul){
    Instruccion* instruccion = new Instruccion(MUL);

    ASSERT_EQ(instruccion->op(), MUL);
}

TEST(test_instruccion, jump){
    Instruccion* instruccion = new Instruccion(JUMP, "rutina");

    ASSERT_EQ(instruccion->op(), JUMP);
    ASSERT_EQ(instruccion->nombreRutina(), "rutina");
}

TEST(test_instruccion, jumpz){
    Instruccion* instruccion = new Instruccion(JUMPZ, "rutina");

    ASSERT_EQ(instruccion->op(), JUMPZ);
    ASSERT_EQ(instruccion->nombreRutina(), "rutina");
}

TEST(test_instruccion, push){
    Instruccion* instruccion = new Instruccion(PUSH, 10);

    ASSERT_EQ(instruccion->op(), PUSH);
    ASSERT_EQ(instruccion->constanteNumerica(), 10);
}

TEST(test_instruccion, read){
    Instruccion* instruccion = new Instruccion(READ, "x");

    ASSERT_EQ(instruccion->op(), READ);
    ASSERT_EQ(instruccion->nombreVariable(), "x");
}

TEST(test_instruccion, write){
    Instruccion* instruccion = new Instruccion(WRITE, "x");

    ASSERT_EQ(instruccion->op(), WRITE);
    ASSERT_EQ(instruccion->nombreVariable(), "x");
}

//PROGRAMA
const vector<string> rutinas = {"a", "b", "c"};

TEST(test_programa, vacia) {
    Programa *p = new Programa;

    for (int i = 0; i < rutinas.size(); ++i)
        ASSERT_EQ(p->longitudRutina(rutinas[i]),0);

    ASSERT_EQ(p->longitudTotal(), 0);

    ASSERT_EQ(p->longitudPrograma(), 0);
}
