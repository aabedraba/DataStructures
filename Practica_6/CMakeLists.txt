cmake_minimum_required(VERSION 3.9)
project(Practica_6)

set(CMAKE_CXX_STANDARD 11)

add_executable(Practica_6
        Diccionario.cpp
        Diccionario.h
        main.cpp
        Palabra.cpp
        Palabra.h
        Sucesor.h
        TextoPredictivo.cpp
        TextoPredictivo.h
        Usuario.cpp
        Usuario.h)
