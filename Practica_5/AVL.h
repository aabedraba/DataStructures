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
    bool buscar ( T &ele, T &result );
    bool insertar(T &ele);
    void recorreInorden( );
    unsigned int numElmentos( );
    unsigned int altura( );
    
private:
    void inorden (Nodo<T> *p, int nivel);
    void rotIzqda( Nodo<T>* &p );
    void rotDecha( Nodo<T>* &p );
    int inserta( Nodo<T>* &c, T &dato );
    Nodo<T>* insertaDato(T &ele, Nodo<T>* &p);
    Nodo<T>* buscaClave (T &ele, Nodo<T> *p);
    
private:
    Nodo<T> *_raiz;
    unsigned int _numElementos;
    
};

template <typename T>
void AVL<T>::inorden (Nodo<T> *p, int nivel){
    if (p){
        inorden (p->_izq, nivel+1);
        // Sustituir por procesamiento ----
        std::cout << "Procesando nodo " << p->_dato;
        std::cout << "en el nivel " << nivel << std::endl;
        // -----------
        inorden (p->_der, nivel+1);
    }
}

template <typename T>
void AVL<T>::recorreInorden() {
    inorden ( _raiz, 0 );
}

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
int AVL<T>::insertaDato( Nodo<T>* &c, T &dato ) {
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new Nodo<T>(dato);
        c = p; 
        deltaH=1;
    } else if (dato > p->_dato) {
        if (inserta(p->_der, dato)){
            p->_bal--;
            _numElementos++;
            if (p->_bal == -1) 
                deltaH=1;
            else if (p->_bal == -2) {
                if (p->_der->_bal == 1) 
                    rotDecha(p->_der);
                rotIzqda(c);
            } 
        } 
    } else if (dato < p->_dato) {
        if (inserta(p->_izq, dato)){
        p->_bal++;
        _numElementos++;
            if (p->_bal==1) deltaH = 1;
            else if (p->_bal == 2) {
                if (p->_izq->_bal == -1) 
                    rotIzqda(p->_izq);
                rotDecha(c);
            } 
        } 
    }
    return deltaH;
}

template <typename T>
Nodo<T> *AVL<T>::insertaDato(T &ele, Nodo<T>* &p){
    if (!p) {
        p = new Nodo<T>(ele);
    } else {
        if (ele <= p->_dato)
            p->_izq = insertaDato(ele, p->_izq);
        else
            p->_der = insertaDato(ele, p->_der);
    }
    _numElementos++;
    return p;
}

template <typename T>
bool AVL<T>::insertar(T &ele){
    bool encontrado = buscar(ele);
    if (!encontrado) {
        insertaDato(ele, _raiz);
        return true;
    }
    return false;
}

template <typename T>
Nodo<T> *AVL<T>::buscaClave (T &ele, Nodo<T> *p){
    if (!p)
        return 0;
    else if (ele < p->_dato)
        return buscaClave (ele, p->_izq);
    else if (ele > p-> _dato)
        return buscaClave (ele, p->_der);
    else return p;
}

template <typename T>
bool AVL<T>::buscar (T &ele, T &result){
    Nodo<T> *p = buscaClave (ele, _raiz);
    if (p) {
        result = p->_dato;
        return true;
    }
    return false;
}

template <typename T>
unsigned int AVL<T>::numElmentos() {
    return _numElementos;
}

template <typename T>
unsigned int AVL<T>::altura() {

}

#endif /* AVL_H */

