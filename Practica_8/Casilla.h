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
    template <typename T>
    friend class MallaRegular;
    Casilla();
    Casilla( const Casilla& orig ) = default;
    virtual ~Casilla() = default;

    void insertar( const U &dato );
    U *buscar( const U &dato );
    bool borrar( const U &dato );

    const std::list<U> &get_puntos() const;
    unsigned int numElementosCasilla();

private:
    std::list<U> _puntos;
    unsigned int _numElementosCasilla;
};

template <typename U>
Casilla<U>::Casilla()
    : _puntos()
{}

template <typename U>
void Casilla<U>::insertar(const U &dato) {
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
    return 0;
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

template<typename U>
const std::list<U> &Casilla<U>::get_puntos() const {
    return _puntos;
}

template <typename U>
unsigned int Casilla<U>::numElementosCasilla() {
    return _numElementosCasilla;
}

#endif //PRACTICA_8_CASILLA_H
