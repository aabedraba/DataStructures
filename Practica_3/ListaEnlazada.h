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

#include "Diccionario.h"

template<typename T>
class Nodo {
    public:
        T _dato;
        Nodo *_sig;

        Nodo( T &aDato, Nodo *aSig = 0 ):
            _dato ( aDato ),
            _sig ( aSig )
        {}
        Nodo( const Nodo& orig )
           : _dato ( orig._dato ),
             _sig ( orig._sig )
        {};
        virtual ~Nodo (){};
}; 

template<typename T>
class ListaEnlazada {
public:
    ListaEnlazada<T>();
    ListaEnlazada<T>( const ListaEnlazada<T>& orig ); 
    virtual ~ListaEnlazada();
    ListaEnlazada<T> operator= ( const ListaEnlazada<T> &orig );
    
    class Iterador {
    private:
        Nodo<T> *_nodo;
    public:
        Iterador( Nodo<T> *aNodo )
            : _nodo ( aNodo )
        {};
        Iterador( const Iterador& orig )
            : _nodo ( orig._nodo )
        {};
        virtual ~Iterador( ){};
        bool fin () {
            return _nodo == 0;
        };
        void siguiente () {
            _nodo = _nodo->_sig;
        };
        T& dato () {
            return _nodo->_dato;
        };       
    };
    
    Iterador iterador();
    T& inicio();
    T& fin();
    void insertaInicio ( T &dato );
    void insertaFin ( T &dato );
    void inserta ( Iterador &iter, T &dato );
    void borraInicio ();
    void borraFinal ();
    void borra ( Iterador &iter );
    
private:
    Nodo<T> *_cabecera, *_cola;
    
};

template<typename T>

ListaEnlazada<T>::ListaEnlazada()
    : _cabecera( 0 ),
      _cola( 0 )
{
}

template<typename T>
ListaEnlazada<T>::ListaEnlazada ( const ListaEnlazada<T>& orig ) 
    : _cabecera ( orig._cabecera ),
      _cola ( orig._cola )
{
}

template<typename T>
ListaEnlazada<T>::~ListaEnlazada()
{   
    while ( _cabecera != 0 ){
        Nodo<T> *aux = _cabecera;
        _cabecera = _cabecera->_sig;
        delete aux;
    }
}

template<typename T>
ListaEnlazada<T> ListaEnlazada<T>::operator =( const ListaEnlazada<T>& orig ) {
    _cabecera = orig._cabecera;
    _cola = orig._cola;
}

template<typename T>
void ListaEnlazada<T>::insertaInicio ( T& dato ) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T> ( dato, _cabecera );
    if ( _cola == 0 )
        _cola = nuevo;
    _cabecera = nuevo;
}

template<typename T>
void ListaEnlazada<T>::insertaFin ( T& dato ) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T> ( dato );
    if ( _cola != 0 )
        _cola->_sig = nuevo;
    if ( _cabecera == 0 )
        _cabecera = nuevo;
    _cola = nuevo;
}

template<typename T>
void ListaEnlazada<T>::inserta ( Iterador& iter, T& dato ) {
    Nodo<T> *anterior = 0;
    if ( _cabecera != _cola ) {
        anterior = _cabecera;
        while ( anterior->_sig != iter )
            anterior = anterior->_sig;
    }
    Nodo<T> *nuevo;
    nuevo = new Nodo<T> ( dato, iter );
    anterior->_sig = nuevo;
    if ( _cabecera == 0 )
        _cabecera = _cola = nuevo;
}

template<typename T>
void ListaEnlazada<T>::borraInicio () {
    Nodo<T> *borrado = _cabecera;
    _cabecera = _cabecera->_sig;
    delete borrado;
    if ( _cabecera == 0 )
        _cola = 0;
}

template<typename T>
void ListaEnlazada<T>::borraFinal () {
    Nodo<T> *anterior =0;
    if ( _cabecera != _cola ) {
        anterior = _cabecera;
        while ( anterior->_sig != _cola )
            anterior = anterior->_sig;
    }
    delete _cola;
    _cola = anterior;
    if ( anterior != 0 )
        anterior->_sig = 0;
    else
        _cabecera = 0;
}

template<typename T>
void ListaEnlazada<T>::borra ( Iterador& iter ) {
    Nodo<T> *anterior = 0;
    if ( _cabecera != _cola ) {
        anterior = _cabecera;
        while ( anterior->_sig != iter )
            anterior = anterior->_sig;
    }
    anterior->_sig = iter._nodo->_sig;
    delete iter;
}

template<typename T>
T& ListaEnlazada<T>::inicio () {
    return _cabecera->_dato;
}

template<typename T>
T& ListaEnlazada<T>::fin () {
    return _cola->_dato;
}

template<typename T>
typename ListaEnlazada<T>::Iterador ListaEnlazada<T>::iterador(){
    return Iterador( _cabecera );
}

#endif /* LISTAENLAZADA_H */