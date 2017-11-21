/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.h
 * Author: Jesus
 * suli14
 *
 * Created on November 7, 2017, 5:24 PM
 */

#ifndef AVL_H
#define AVL_H

#include "Nodo.h"




template <typename T>
class Avl {
public:
    Avl( );
    Avl( const Avl<T>& orig );
    virtual ~Avl( );
    
    Nodo<T>* inserta( Nodo<T>* n, T &dato );
    Nodo<T>* equilibrio( Nodo<T>* n ); 
    void modificaAltura( Nodo<T>* n );
private:
    Nodo<T> *_raiz;
    
};

template <typename T>
Avl<T>::Avl()
    : _raiz( 0 )
{}

template <typename T>
Nodo<T> *Avl<T>::inserta( Nodo<T>* n, T &dato ){
    if ( !n ){
        return new Nodo<T>( dato );
    }
    if ( dato < n->_dato )
        n->_izq = inserta( n->_izq, dato );
    else if ( dato > n->_dato)
        n->_der = inserta( n->_der );
    else
        return n;
    
    equilibrio( n );
}

template<typename T>
Nodo<T>* Avl<T>::equilibrio( Nodo<T>* n ){
    modificaAltura( n );
    if ( n->balance() == 2){
        
    }
}

template<typename T>
void Avl<T>::modificaAltura( Nodo<T>* n ){
    int altIzq = n->altura( n->_izq );
    int altDer = n->altura( n->_der );
    n->_altura  = ( (altIzq > altDer) ? altIzq : altDer ) + 1;
}