#include "gtest/gtest.h"
#include "../src/DiccionarioString.h"

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
