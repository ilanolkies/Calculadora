#include "gtest/gtest.h"
#include "../src/Pila.h"

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