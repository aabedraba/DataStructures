//
// Created by aabedraba on 14/12/17.
//

#ifndef PRACTICA_8_CASILLA_H
#define PRACTICA_8_CASILLA_H

#include <list>
#include "MallaRegular.h"

template <typename T>
class MallaRegular;

template <typename U>
class Casilla {
public:
    friend class MallaRegular<U>;
    Casilla();
    Casilla( const Casilla& orig ) = default;
    virtual ~Casilla() = default;

    void insertar( const U &dato );
    U *buscar( const U &dato );
    bool borrar( const U &dato );

    unsigned int numElementosCasilla();

private:
    std::list<U> _puntos;
    unsigned int _numElementosCasilla;
};

template <typename U>
Casilla<U>::Casilla()
    : _puntos(), _numElementosCasilla( 0 )
{}

template <typename U>
void Casilla<U>::insertar( const U &dato) {
//    U *buscado = buscar( dato );
//    if ( buscado )
//        return;
    _puntos.push_back( dato );
    _numElementosCasilla++;
}

template <typename U>
U* Casilla<U>::buscar(const U &dato) {
    typename std::list<U>::iterator iter;
    iter = _puntos.begin();
    for (; iter != _puntos.end(); ++iter)
        if ( *iter == dato )
            return &(*iter);
    return nullptr;
}

template <typename U>
bool Casilla<U>::borrar(const U &dato) {
    typename std::list<U>::iterator iter;
    iter = _puntos.begin();
    for ( ; iter != _puntos.end() ; ++iter)
        if ( *iter == dato ){
            _puntos.erase(iter);
            _numElementosCasilla--;
            return true;
        }
    return false;
}


template <typename U>
unsigned int Casilla<U>::numElementosCasilla() {
    return _numElementosCasilla;
}

#endif //PRACTICA_8_CASILLA_H
