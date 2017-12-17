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
//    friend class MallaRegular;
    Casilla();
    Casilla( const Casilla& orig ) = default;
    virtual ~Casilla() = default;

    void insertar( const T &dato );
    T *buscar( const T &dato );
    bool borrar( const T &dato );

    const std::list<T> &get_puntos() const;

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
    typename std::list<T>::iterator iter;
    iter = _puntos.begin();
    for (; iter != _puntos.end(); ++iter)
        if ( *iter == dato )
            return &(*iter);
    return 0;
}

template <typename T>
bool Casilla<T>::borrar(const T &dato) {
    typename std::list<T>::iterator iter;
    iter = _puntos.begin();
    for ( ; iter != _puntos.end() ; ++iter)
        if ( *iter == dato ){
            _puntos.erase(iter);
            return true;
        }
    return false;
}

template<typename T>
const std::list<T> &Casilla<T>::get_puntos() const {
    return _puntos;
}

#endif //PRACTICA_8_CASILLA_H
