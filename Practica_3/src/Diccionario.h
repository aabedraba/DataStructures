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
    
    Palabra& busca( const std::string &termino, int &pos);
    void insertar( std::string palabra, int& pos );
    void eliminar ( const std::string &palabra );
    void entrena ( const std::string frase );
    void usaCorpus ( std::string nomFich );
    
private:
    VDinamico<Palabra> _vectorPalabras;
};

#endif /* DICCIONARIO_H */

