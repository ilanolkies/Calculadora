#include "gtest/gtest.h"

#include "../src/Instruccion.h"

TEST(test_instruccion, sin_operandos){
    Instruccion* instruccion = new Instruccion(ADD);

    ASSERT_EQ(instruccion->op(), ADD);
}
