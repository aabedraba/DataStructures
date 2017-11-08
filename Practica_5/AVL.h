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

#include <queue>
#include <iostream>


template <typename T>
class Nodo {
public:
    Nodo( T &ele ):
        _izq( 0 ),
        _der( 0 ),
        _bal ( 0 ),
        _dato( ele )
//        _altura ( 0 )
    {};
    Nodo( const Nodo& orig ):
        _izq( orig._izq ),
        _der( orig._der ),
        _dato( orig._dato ),
        _bal ( orig._bal )
//        _altura ( orig._altura )
    {};
    virtual ~Nodo( ) {};
    Nodo<T> *_izq;
    Nodo<T> *_der;
    T _dato;
    char _bal;
//    int _altura;
};

template <typename T>
class Avl {
public:
    Avl( );
    Avl( const Avl<T>& orig );
    Avl &operator=( const Avl<T>& orig );
    virtual ~Avl( );
    bool insertar( T &ele );
    bool buscar ( T &ele );
    void recorreInorden( );
    unsigned int numElmentos( );
//    unsigned int alturaAvl( );
    
private:
    void inorden ( Nodo<T> *p, std::queue<T> &cola );
    void rotIzqda( Nodo<T>* &p );
    void rotDecha( Nodo<T>* &p );
    int insertaDato( Nodo<T>* &c, T &dato );
    Nodo<T>* buscaClave (T &ele, Nodo<T> *p);
//    unsigned int altura( Nodo<T> *n );
    void borraNodos ( Nodo<T>* &p );
    
private:
    Nodo<T> *_raiz;
    unsigned int _numElementos;
    
};

template <typename T>
Avl<T>::Avl()
    : _raiz( 0 ),
      _numElementos( 0 )
{}

template <typename T>
Avl<T>::Avl( const Avl<T>& orig ){
    std::queue<T> cola;
    inorden( orig._raiz, cola );
    while( !cola.empty() ){
        insertar( cola.front() );
        cola.pop();
    }
}

template <typename T>
Avl<T> &Avl<T>::operator =(const Avl<T>& orig){
    std::queue<T> cola;
    inorden( orig._raiz, cola );
    while( !cola.empty() ){
        insertar( cola.front() );
        cola.pop();
    }
}

template <typename T>
Avl<T>::~Avl(){
    borraNodos( _raiz );
}

template <typename T>
void Avl<T>::borraNodos( Nodo<T>* &p ){
    if ( p ){
        borraNodos( p->_izq );
        borraNodos( p->_der );
        delete p;
    }
}

template <typename T>
void Avl<T>::inorden ( Nodo<T> *p, std::queue<T> &cola ){
    if ( p ){
        inorden ( p->_izq, cola );
        cola.push( p->_dato );
        inorden (p->_der, cola );
    }
}

template <typename T>
void Avl<T>::recorreInorden() {
    std::queue<T> cola;
    inorden ( _raiz, cola );
    while( !cola.empty() ){
        std::cout << cola.front() << ' ';
        cola.pop();
    }
    std::cout << "\n";
}

template<typename T>
void Avl<T>::rotIzqda( Nodo<T>* &p ) {
    Nodo<T> *q = p, *r;
    p = r = q->_der;
    q->_der = r->_izq;
    r->_izq = q;
    q->_bal++;
    if ( r->_bal < 0 ) 
        q->_bal += -r->_bal;
    r->_bal++;
    if ( q->_bal > 0 ) 
        r->_bal += q->_bal;
}

template<typename T>
void Avl<T>::rotDecha( Nodo<T>* &p ) {
    Nodo<T> *q = p, *l;
    p = l = q->_izq;
    q->_izq = l->_der;
    l->_der = q;
    q->_bal--;
    if ( l->_bal > 0 ) 
        q->_bal -= l->_bal;
    l->_bal--;
    if ( q->_bal < 0 ) 
        l->_bal -= -q->_bal;
}

template <typename T>
int Avl<T>::insertaDato( Nodo<T>* &c, T &dato  ) {
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new Nodo<T>(dato);
        c = p;
        deltaH = 1;
    } else if (dato > p->_dato) {
        if ( insertaDato( p->_der, dato ) ){
            p->_bal--;
            if ( p->_bal == -1 ) deltaH = 1;
            else if ( p->_bal == -2 ) {
                if ( p->_der->_bal == 1 ) 
                    rotDecha( p->_der );
                rotIzqda( c );
            } 
        } 
    } else if ( dato < p->_dato ) {
        if ( insertaDato( p->_izq, dato ) ){
            p->_bal++;
            if ( p->_bal == 1 ) deltaH = 1;
            else if ( p->_bal == 2 ) {
                if ( p->_izq->_bal == -1 ) 
                    rotIzqda( p->_izq );
                rotDecha(c);
            } 
        } 
    }
    
    return deltaH;
}

template <typename T>
bool Avl<T>::insertar( T &ele ){
    bool encontrado = buscar( ele );
    if ( !encontrado ) {
        insertaDato( _raiz, ele );
        _numElementos++;
        return true;
    }
    return false;
}

template <typename T>
Nodo<T> *Avl<T>::buscaClave (T &ele, Nodo<T> *p){
    if (!p)
        return 0;
    else if ( ele == p->_dato )
        return p;
    else if ( ele < p->_dato )
        return buscaClave (ele, p->_izq);
    else if ( ele > p-> _dato )
        return buscaClave (ele, p->_der);
}

template <typename T>
bool Avl<T>::buscar ( T &ele ){
    Nodo<T> *p = buscaClave ( ele, _raiz );
    return p ? true : false;
}

template <typename T>
unsigned int Avl<T>::numElmentos() {
    return _numElementos;
}

//template <typename T>
//unsigned int Avl<T>::alturaAvl(){
//    return altura( _raiz );
//}


//template <typename T>
//unsigned int Avl<T>::altura( Nodo<T> *n ) {
//    if ( n ){
//        unsigned int altIzq =  _raiz->_izq->_altura;
//        unsigned int altDer =  _raiz->_der->_altura;
//        return ( (altIzq > altDer) ? altIzq : altDer );
//    }
//    return 0;
//}

#endif /* AVL_H */

