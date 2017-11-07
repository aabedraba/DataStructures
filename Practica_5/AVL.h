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
    Nodo( T &ele ):
        _izq( 0 ),
        _der( 0 ),
        _bal ( 0 ),
        _dato( ele ) 
    {};
    Nodo( const Nodo& orig ):
        _izq( orig._izq ),
        _der( orig._der ),
        _dato( orig._dato ),
        _bal ( orig._bal )
    {};
    virtual ~Nodo( );
private:
    Nodo<T> *_izq;
    Nodo<T> *_der;
    T _dato;
    char _bal;
};

template <typename T>
class AVL {
public:
    AVL( );
    AVL( const AVL<T>& orig );
    virtual ~AVL( );
    AVL operator=( const AVL<T>& orig );
    void rotIzqda( Nodo<T>* &p );
    void rotDecha( Nodo<T>* &p );
    
private:
    Nodo<T> *raiz;
    
};

template<typename T>
void AVL<T>::rotIzqda( Nodo<T>* &p ) {
    Nodo<T> *q = p, *r;
    p = r = q->_der;
    q->_der = r->_izq;
    r->_izq = q;
    q->_bal++;
    if ( r->_bal < 0 ) q->_bal += -r->_bal;
    r->_bal++;
    if ( q->_bal > 0 ) r->_bal += q->_bal;
}

template<typename T>
void AVL<T>::rotDecha( Nodo<T>* &p ) {
    Nodo<T> *q = p, *l;
    p = l = q->_izq;
    q->_izq = l->_der;
    l->_der = q;
    q->_bal--;
    if ( l->_bal > 0 ) q->_bal -= l->_bal;
    l->_bal--;
    if ( q->_bal < 0 ) l->_bal -= -q->_bal;
}

#endif /* AVL_H */

