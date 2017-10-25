/* 
 * File:   Diccionario.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Palabra.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Diccionario {
public:
    Diccionario( std::string nomFich );
    Diccionario( const Diccionario& orig );
    virtual ~Diccionario();
    
    Palabra& busca( const std::string &termino, unsigned int &pos);
    void insertar( std::string palabra, unsigned int& pos );
    void eliminar ( const std::string &palabra, unsigned int &pos );
    void entrena ( const std::string frase );
    void usaCorpus ( std::string nomFich );
    
private:
    std::vector<Palabra> _vectorPalabras;
};

#endif /* DICCIONARIO_H */

