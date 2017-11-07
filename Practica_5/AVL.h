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
        izq(0),
        der(0)
    {}
    
    Nodo( T &ele ):
        izq(0),
        der(0),
        dato(ele)
    {}
    
    Nodo( const Nodo& orig ):
        izq( orig.izq ),
        der( orig.der ),
        dato( orig.dato )
    {}
    
    virtual ~Nodo( );
};

template <typename T>
class AVL {
public:
    AVL( );
    AVL( const AVL& orig );
    virtual ~AVL( );
private:

};

#endif /* AVL_H */

