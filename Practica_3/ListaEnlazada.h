/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaEnlazada.h
 * Author: aabedraba
 *
 * Created on October 17, 2017, 11:29 PM
 */

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Nodo.h"

template<typename T>
class ListaEnlazada {
public:
    ListaEnlazada<T>();
    ListaEnlazada<T>( const ListaEnlazada<T>& orig ); 
    ListaEnlazada<T> operator= ( const ListaEnlazada<T> &orig );
    T& inicio();
    T& fin();
    
    ListaEnlazada(const ListaEnlazada& orig);
    virtual ~ListaEnlazada();
private:
    Nodo<T> *cabecera, *cola;

};

#endif /* LISTAENLAZADA_H */

