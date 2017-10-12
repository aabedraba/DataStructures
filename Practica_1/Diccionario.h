/* 
 * File:   Diccionario.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Palabra.h"
#include "VectorEstatico.h"

#include <string>
#include <iostream>
#include <fstream>

class Diccionario {
public:
    Diccionario( std::string nomFich );
    Diccionario( const Diccionario& orig );
    virtual ~Diccionario();
    
    void cargaPalabras( const std::string &nomFich );
    int busca( const std::string termino );
    void inserta( const Palabra &p, int pos );
    
private:
    VectorEstatico _vectorPalabras;
};

#endif /* DICCIONARIO_H */

