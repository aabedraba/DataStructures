/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.h
 * Author: aabedraba
 *
 * Created on November 7, 2017, 5:24 PM
 */

#ifndef AVL_H
#define AVL_H

template <typename T>
class Nodo {
public:
    Nodo<T> *izq;
    Nodo<T> *der;
    T dato;
    
    Nodo( ):
        izq( 0 ),
        der( 0 )
    {};
    Nodo( T &ele ):
        izq( 0 ),
        der( 0 ),
        dato( ele )
    {};
    Nodo( const Nodo& orig ):
        izq( orig.izq ),
        der( orig.der ),
        dato( orig.dato )
    {};
    virtual ~Nodo( );
};

template <typename T>
class AVL {
public:
    AVL( );
    AVL( const AVL<T>& orig );
    virtual ~AVL( );
    AVL operator=( const AVL<T>& orig );
    AVL rotIzqda( Nodo<T>* &p );
    AVL rotDecha( Nodo<T>* &p );
    
private:
    
};

template<typename T>
void Avl<T>::rotIzqda( Nodo<T>* &p ) {
    Nodo<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if ( r->bal < 0 ) q->bal += -r->bal;
    r->bal++;
    if ( q->bal > 0 ) r->bal += q->bal;
}

template<typename T>
void Avl<T>::rotDecha( Nodo<T>* &p ) {
    Nodo<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if ( l->bal > 0 ) q->bal -= l->bal;
    l->bal--;
    if ( q->bal < 0 ) l->bal -= -q->bal;
}

#endif /* AVL_H */

