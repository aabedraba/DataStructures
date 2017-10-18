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
    ListaEnlazada<T>();
    ListaEnlazada<T>( const ListaEnlazada<T>& orig ); 
    ListaEnlazada<T> operator= ( const ListaEnlazada<T> &orig );
    T& inicio();
    T& fin();
    
    void insertaInicio (T &dato);
    void insertaFin (T &dato);
    void inserta (Iterador &i, T &dato);
    void borraInicio ();
    void borraFinal ();
    void borra (Iterador &i);
    
    ListaEnlazada(const ListaEnlazada& orig);
    virtual ~ListaEnlazada();
private:
    Nodo<T> *cabecera, *cola;

private:
    class Nodo {
        friend class ListaEnlazada;
        public:
            T dato;
            Nodo *sig;
            Nodo( T &aDato, Nodo *asig = 0 );
            Nodo( const Nodo& orig );
            virtual ~Nodo( );
        private:

    };
    
public:
    class Iterador {
        friend class ListaEnlazada;
        friend class Nodo;
        public:
            Iterador( );
            Iterador( const Iterador& orig );
            virtual ~Iterador( );
        private:
            Nodo<T> *nodo;
    };

};

#endif /* LISTAENLAZADA_H */

