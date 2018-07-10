#include "gtest/gtest.h"

#include "../src/Calculadora.h"

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
    ASSERT_EQ(c->rutinaActual(), "r");

    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 10);
    ASSERT_EQ(c->rutinaActual(), "s");
}

TEST(test_calculadora, jumpz) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(JUMPZ, "s"));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(SUB));
    p->agregarInstruccion("r", Instruccion(JUMPZ, "s"));

    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);
    ASSERT_EQ(c->rutinaActual(), "r");

    c->ejeutar();

    ASSERT_EQ(c->rutinaActual(), "r");
    ASSERT_EQ(c->pila().top(), 10);

    c->ejeutar();
    c->ejeutar();
    c->ejeutar();
    c->ejeutar();

    ASSERT_EQ(c->rutinaActual(), "r");
    ASSERT_EQ(c->pila().top(), 0);

    c->ejeutar();

    ASSERT_EQ(c->rutinaActual(), "s");
}

// UTILIZACION DE LA PILA
TEST(test_calculadora, pila) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(ADD));
    p->agregarInstruccion("r", Instruccion(MUL));
    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));
    p->agregarInstruccion("r", Instruccion(PUSH, 20));
    p->agregarInstruccion("r", Instruccion(READ, "v"));
    p->agregarInstruccion("r", Instruccion(ADD));


    Calculadora *c = new Calculadora(*p, "r", 1);

    ASSERT_EQ(c->pila().size(), 0);
    ASSERT_EQ(c->pila().top(), 0);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 10);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 2);
    ASSERT_EQ(c->pila().top(), 10);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 3);
    ASSERT_EQ(c->pila().top(), 10);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 2);
    ASSERT_EQ(c->pila().top(), 20);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 200);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 2);
    ASSERT_EQ(c->pila().top(), 10);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 1);
    ASSERT_EQ(c->pila().top(), 200);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 2);
    ASSERT_EQ(c->pila().top(), 20);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 3);
    ASSERT_EQ(c->pila().top(), 10);

    c->ejeutar();

    ASSERT_EQ(c->pila().size(), 2);
    ASSERT_EQ(c->pila().top(), 30);
}

//UTILIZACION DE VENTANA
TEST(test_calculadora, ventana) {
    Programa *p = new Programa();
    p->agregarInstruccion("r", Instruccion(PUSH, 100));
    p->agregarInstruccion("r", Instruccion(PUSH, 200));
    p->agregarInstruccion("r", Instruccion(PUSH, 300));

    p->agregarInstruccion("r", Instruccion(PUSH, 10));
    p->agregarInstruccion("r", Instruccion(PUSH, 20));
    p->agregarInstruccion("r", Instruccion(PUSH, 30));
    p->agregarInstruccion("r", Instruccion(PUSH, 40));
    p->agregarInstruccion("r", Instruccion(PUSH, 50));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));
    p->agregarInstruccion("r", Instruccion(WRITE, "v"));

    p->agregarInstruccion("r", Instruccion(WRITE, "w"));
    p->agregarInstruccion("r", Instruccion(WRITE, "w"));
    p->agregarInstruccion("r", Instruccion(WRITE, "w"));

    Calculadora *c = new Calculadora(*p, "r", 3);

    // vairable v
    for (int i = 0; i < 8; ++i)
        c->ejeutar();

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 50);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 9), 50);

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 40);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 30);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);
    ASSERT_EQ(c->valorVariable("v", 10), 30);

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 20);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);
    ASSERT_EQ(c->valorVariable("v", 10), 30);
    ASSERT_EQ(c->valorVariable("v", 11), 20);

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 10);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);
    ASSERT_EQ(c->valorVariable("v", 10), 30);
    ASSERT_EQ(c->valorVariable("v", 11), 20);
    ASSERT_EQ(c->valorVariable("v", 12), 10);

    // vairable w
    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 10);
    ASSERT_EQ(c->valorActual("w"), 300);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);
    ASSERT_EQ(c->valorVariable("v", 10), 30);
    ASSERT_EQ(c->valorVariable("v", 11), 20);
    ASSERT_EQ(c->valorVariable("v", 12), 10);

    for (int i = 0; i < 12; ++i)
        ASSERT_EQ(c->valorVariable("w", i), 0);

    ASSERT_EQ(c->valorVariable("w", 13), 300);

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 10);
    ASSERT_EQ(c->valorActual("w"), 200);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);
    ASSERT_EQ(c->valorVariable("v", 10), 30);
    ASSERT_EQ(c->valorVariable("v", 11), 20);
    ASSERT_EQ(c->valorVariable("v", 12), 10);

    for (int i = 0; i < 12; ++i)
        ASSERT_EQ(c->valorVariable("w", i), 0);

    ASSERT_EQ(c->valorVariable("w", 13), 300);
    ASSERT_EQ(c->valorVariable("w", 14), 200);

    c->ejeutar();

    ASSERT_EQ(c->valorActual("v"), 10);
    ASSERT_EQ(c->valorActual("w"), 100);

    for (int i = 0; i < 8; ++i)
        ASSERT_EQ(c->valorVariable("v", i), 0);

    ASSERT_EQ(c->valorVariable("v", 8), 50);
    ASSERT_EQ(c->valorVariable("v", 9), 40);
    ASSERT_EQ(c->valorVariable("v", 10), 30);
    ASSERT_EQ(c->valorVariable("v", 11), 20);
    ASSERT_EQ(c->valorVariable("v", 12), 10);

    for (int i = 0; i < 12; ++i)
        ASSERT_EQ(c->valorVariable("w", i), 0);

    ASSERT_EQ(c->valorVariable("w", 13), 300);
    ASSERT_EQ(c->valorVariable("w", 14), 200);
    ASSERT_EQ(c->valorVariable("w", 15), 100);
}

TEST(test_calculadora, fibonacci_stress) {
    Programa* p = new Programa();
    p->agregarInstruccion("Calcular F(n)", Instruccion(READ, "F(n-1)"));
    p->agregarInstruccion("Calcular F(n)", Instruccion(READ, "F(n-2)"));
    p->agregarInstruccion("Calcular F(n)", Instruccion(ADD));
    p->agregarInstruccion("Calcular F(n)", Instruccion(WRITE, "F(n)"));
    p->agregarInstruccion("Calcular F(n)", Instruccion(JUMP, "Guardar nuevos valores"));
    p->agregarInstruccion("Guardar nuevos valores", Instruccion(READ, "F(n-1)"));
    p->agregarInstruccion("Guardar nuevos valores", Instruccion(WRITE, "F(n-2)"));
    p->agregarInstruccion("Guardar nuevos valores", Instruccion(READ, "F(n)"));
    p->agregarInstruccion("Guardar nuevos valores", Instruccion(WRITE, "F(n-1)"));
    p->agregarInstruccion("Guardar nuevos valores", Instruccion(JUMP, "Termino?"));
    p->agregarInstruccion("Termino?", Instruccion(READ, "n"));
    p->agregarInstruccion("Termino?", Instruccion(PUSH, 1));
    p->agregarInstruccion("Termino?", Instruccion(SUB));
    p->agregarInstruccion("Termino?", Instruccion(WRITE, "n"));
    p->agregarInstruccion("Termino?", Instruccion(READ, "n"));
    p->agregarInstruccion("Termino?", Instruccion(PUSH, 1));
    p->agregarInstruccion("Termino?", Instruccion(SUB));
    p->agregarInstruccion("Termino?", Instruccion(JUMPZ, "FIN"));
    p->agregarInstruccion("Termino?", Instruccion(JUMP, "Calcular F(n)"));

    Calculadora *c = new Calculadora(*p, "Calcular F(n)", 2);

    int n = 20;
    int Fn2 = 0, Fn1 = 1;
    c->asignarVariable("n", n);
    c->asignarVariable("F(n-2)", Fn2);
    c->asignarVariable("F(n-1)", Fn1);

    cout << endl;
    vector< pair<int, int> > historialFn;
    while(!c->finalizo()) {
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), Fn1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), Fn2);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), Fn1+Fn2);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 0);
        EXPECT_EQ(c->valorActual("F(n)"), Fn1+Fn2);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 0);
        EXPECT_EQ(c->rutinaActual(), "Guardar nuevos valores");
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), Fn1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 0);
        EXPECT_EQ(c->valorActual("F(n-2)"), Fn1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), Fn1+Fn2);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 0);
        EXPECT_EQ(c->valorActual("F(n-1)"), Fn1+Fn2);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 0);
        EXPECT_EQ(c->rutinaActual(), "Termino?");
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), n);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), n-1);
        c->ejeutar();
        EXPECT_EQ(c->valorActual("n"), n-1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), n-1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), 1);
        c->ejeutar();
        EXPECT_EQ(c->pila().top(), n-2);
        c->ejeutar();
        if (n == 2) {
            EXPECT_TRUE(c->finalizo());
        } else {
            EXPECT_FALSE(c->finalizo());
            c->ejeutar();
            EXPECT_EQ(c->rutinaActual(), "Calcular F(n)");
        }

        int oldFn1 = Fn1;
        Fn1 = Fn1 + Fn2;
        Fn2 = oldFn1;
        n = n-1;

        historialFn.push_back({c->instanteActual(), Fn1});
    }
    EXPECT_EQ(c->valorActual("F(n)"), Fn1);

    for (pair<int,int> instante : historialFn) {
        EXPECT_EQ(c->valorVariable("F(n)",instante.first), instante.second);
    }
}