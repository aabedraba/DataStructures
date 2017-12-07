cmake_minimum_required(VERSION 3.9)
project(THash)

set(CMAKE_CXX_STANDARD 17)

add_executable(THash main.cpp THashCerrada.h Palabra.cpp Palabra.h Sucesor.h)