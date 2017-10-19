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

template<typename T>
class ListaEnlazada {
public:
    
    ListaEnlazada<T>():
        cabecera(0),
        cola(0)
    {}
    
    ListaEnlazada<T>( const ListaEnlazada<T>& orig ); 
    ListaEnlazada<T> operator= ( const ListaEnlazada<T> &orig );
    T& inicio();
    T& fin();
    void insertaInicio ( T &dato );
    void insertaFin ( T &dato );
    void inserta ( Iterador &i, T &dato );
    void borraInicio ();
    void borraFinal ();
    void borra ( Iterador &i );
    ListaEnlazada(const ListaEnlazada& orig);
    virtual ~ListaEnlazada();
private:
    Nodo<T> *cabecera, *cola;

private:
    class Nodo {
        public:
            T dato;
            Nodo *sig;
            
            Nodo( T &aDato, Nodo *aSig = 0 ):
                dato ( aDato ),
                sig ( aSig )
            {}
            
            Nodo( const Nodo& orig );
            virtual ~Nodo ();
    };

public:
    class Iterador {
        friend class ListaEnlazada;
        public:
            Iterador( Nodo<T> *aNodo ):
                nodo ( aNodo )
            {};
            Iterador( const Iterador& orig );
            virtual ~Iterador( );
            
            bool fin () {
                return nodo == 0;
            }
            
            void siguiente () {
                nodo = nodo->sig;
            }
            
            T &dato () {
                return nodo->dato;
            }
        private:
            Nodo<T> *nodo;
    };
    
};


ListaEnlazada<T>::operator =( const ListaEnlazada<T>& orig ){
    
}

ListaEnlazada<T>::ListaEnlazada ( const ListaEnlazada<T>& orig ) {
    
}

ListaEnlazada<T>::insertaInicio ( T& dato ) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T> ( dato, cabecera );
    if ( cola == 0 )
        cola = nuevo;
    cabecera = nuevo;
}

ListaEnlazada<T>::insertaFin ( T& dato ) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T> ( dato, 0 );
    if ( cola != 0 )
        cola->sig = nuevo;
    if ( cabecera == 0 )
        cabecera = nuevo;
    cola = nuevo;
}

ListaEnlazada<T>::inserta ( Iterador& i, T& dato ) {
    Nodo<T> *anterior = 0;
    if ( cabecera != cola ) {
        anterior = cabecera;
        while ( anterior->sig != i )
            anterior = anterior->sig;
    }
    Nodo<T> *nuevo;
    nuevo = new Nodo<T> ( dato, i );
    anterior->sig = nuevo;
    if ( cabecera == 0 )
        cabecera = cola = nuevo;
}

ListaEnlazada<T>::borraInicio () {
    Nodo<T> *borrado = cabecera;
    cabecera = cabecera->sig;
    delete borrado;
    if ( cabecera == 0 )
        cola = 0;
}

ListaEnlazada<T>::borraFinal () {
    Nodo<T> *anterior =0;
    if ( cabecera != cola ) {
        anterior = cabecera;
        while ( anterior->sig != cola )
            anterior = anterior->sig;
    }
    delete cola;
    cola = anterior;
    if ( anterior != 0 )
        anterior->sig = 0;
    else
        cabecera = 0;
}

ListaEnlazada<T>::borra ( Iterador& i ) {
    Nodo<T> *anterior = 0;
    if ( cabecera != cola ) {
        anterior = cabecera;
        while ( anterior->sig != i )
            anterior = anterior->sig;
    }
    anterior->sig = i->siguiente;
    delete i;
}

ListaEnlazada<T>::inicio () {
    
}

ListaEnlazada<T>::fin () {
    
}

#endif /* LISTAENLAZADA_H */