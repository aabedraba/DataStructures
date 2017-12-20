cmake_minimum_required(VERSION 3.9)
project(Practica_8)

set(CMAKE_CXX_STANDARD 11)

add_executable(Practica_8
        src/img.cpp src/img.h
        src/main.cpp src/MallaRegular.h 
        src/Casilla.h src/CodigoPost.cpp 
        src/CodigoPost.h)
