cmake_minimum_required(VERSION 3.7)
project(solucion)

set(CMAKE_CXX_STANDARD 11)

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES src/*.cpp src/*.h)

# Leemos todos los archivos de test en ./tests
file(GLOB TEST_SOURCES tests/*.cpp)

add_subdirectory(tests/google-test)

# Creamos el ejecutable para correr los tests
add_executable(correrTests ${TEST_SOURCES} ${SOURCE_FILES} src/Calculadora.h src/Programa.h src/Programa.cpp src/Calculadora.cpp src/Instruccion.h src/Instruccion.cpp src/DiccionarioString.h src/DiccionarioString.hpp src/Basics.h)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

add_test(correrTests correrTests)
