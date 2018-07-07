#include "gtest/gtest.h"

#include "../src/Instruccion.h"

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
    Instruccion* instruccion = new Instruccion(JUMP);

    ASSERT_EQ(instruccion->op(), JUMP);
}

TEST(test_instruccion, jumpz){
    Instruccion* instruccion = new Instruccion(JUMPZ);

    ASSERT_EQ(instruccion->op(), JUMPZ);
}

