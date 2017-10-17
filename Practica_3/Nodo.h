/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: aabedraba
 *
 * Created on October 17, 2017, 11:55 PM
 */

#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo {
public:
    T dato;
    Nodo *sig;
    
    Nodo( T &aDato, Nodo *asig = 0 );
    Nodo( const Nodo& orig );
    virtual ~Nodo( );
private:

};

#endif /* NODO_H */

