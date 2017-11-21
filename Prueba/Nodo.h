/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: aabedraba
 *
 * Created on November 8, 2017, 7:52 PM
 */

#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    Nodo<T> *_izq;
    Nodo<T> *_der;
    T _dato;
    int _altura;
    
    Nodo( T &ele );
    Nodo( const Nodo& orig );
    virtual ~Nodo(){};
    
    int altura( Nodo *p);
    int balance();
};

template <typename T>
Nodo<T>::Nodo( T& ele )
    : _izq( 0 ),
      _der( 0 ),
      _altura ( 1 ),
      _dato( ele ) 
{};

template <typename T>
Nodo<T>::Nodo( const Nodo& orig )
    : _izq( orig._izq ),
      _der( orig._der ),
      _altura ( orig._altura ),
      _dato( orig._dato )
{};

template <typename T>
int Nodo<T>::altura( Nodo* p ){
    return p ? p->_altura : 0;
}

template <typename T>
int Nodo<T>::balance(){
    return altura(_izq) - altura(_der);
}

#endif /* NODO_H */

