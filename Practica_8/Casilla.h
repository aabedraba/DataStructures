//
// Created by aabedraba on 14/12/17.
//

#ifndef PRACTICA_8_CASILLA_H
#define PRACTICA_8_CASILLA_H

#include <list>
#include "MallaRegular.h"

template <typename T>
class Casilla {
public:
    friend class MallaRegular<T>;
    Casilla();
    Casilla( const Casilla& orig ) = default;
    virtual ~Casilla() = default;

    void insertar( const T &dato );
    T *buscar( const T &dato );
    bool borrar( const T &dato );

private:
    std::list<T> _puntos;
};

template <typename T>
Casilla<T>::Casilla()
    : _puntos()
{}

template <typename T>
void Casilla<T>::insertar(const T &dato) {
    _puntos.push_back( dato );
}

template <typename T>
T* Casilla<T>::buscar(const T &dato) {
    std::list<T>::iterator iter;
    iter = _puntos.begin();
    for (; iter != _puntos.end(); ++iter)
        if ( *iter == dato )
            return &(*iter);
    return 0;
}

template <typename T>
bool Casilla<T>::borrar(const T &dato) {
    std::list<T>::iterator iter;
    iter = _puntos.begin();
    for ( ; iter != _puntos.end() ; ++iter)
        if ( *iter == dato ){
            _puntos.erase(iter);
            return true;
        }
    return false;
}

#endif //PRACTICA_8_CASILLA_H
