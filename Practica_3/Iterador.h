/* 
 * File:   Iterador.h
 * Author: aabedraba
 *
 * Created on October 17, 2017, 11:49 PM
 */

#ifndef ITERADOR_H
#define ITERADOR_H

#include "ListaEnlazada.h"

template<typename T>
class Iterador {
public:
    Iterador( );
    Iterador( const Iterador& orig );
    virtual ~Iterador( );
private:
    Nodo<T> *nodo;
    friend class ListaEnlazada;

};

#endif /* ITERADOR_H */

