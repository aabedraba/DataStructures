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
    AVL operator=( const AVL<T>& orig );
    virtual ~AVL( );
    
private:
    void rotIzqda( Nodo<T>* &p );
    void rotDecha( Nodo<T>* &p );
    int inserta( Nodo<T>* &c, T &dato );
    
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

template <typename T>
int AVL<T>::inserta( Nodo<T>* &c, T &dato ) {
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new Nodo<T>(dato);
        c = p; deltaH=1;
    } else if (dato > p->dato) {
        if (inserta(p->der, dato)){
        p->bal--;
            if (p->bal == -1) 
                deltaH=1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) 
                    rotDecha(p->der);
                rotIzqda(c);
            } 
        } 
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato)){
        p->bal++;
            if (p->bal==1) deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1) 
                    rotIzqda(p->izq);
                rotDecha(c);
            } 
        } 
    }
    return deltaH;
}

#endif /* AVL_H */

