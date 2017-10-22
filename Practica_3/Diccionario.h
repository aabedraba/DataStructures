/* 
 * File:   Diccionario.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Palabra.h"
#include "VDinamico.h"
#include <string>
#include <iostream>
#include <fstream>

class Diccionario {
public:
    Diccionario( std::string nomFich );
    Diccionario( const Diccionario& orig );
    virtual ~Diccionario();
    
//    void cargaPalabras( const std::string &nomFich );
    int busca( const std::string &termino );
    void insertar( const std::string &palabra );
    void eliminar ( const std::string &palabra );
    void entrena ( const std::string frase );
    void usaCorpus ( std::string nomFich );
    
private:
    VDinamico<Palabra> _vectorPalabras;
};

#endif /* DICCIONARIO_H */

