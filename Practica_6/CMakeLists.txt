cmake_minimum_required(VERSION 3.9)
project(Practica_6)

set(CMAKE_CXX_STANDARD 11)

add_executable(Practica_6
        src/Diccionario.cpp
        src/Diccionario.h
        src/main.cpp
        src/Palabra.cpp
        src/Palabra.h
        src/Sucesor.h
        src/TextoPredictivo.cpp
        src/TextoPredictivo.h
        src/Usuario.cpp
        src/Usuario.h)
