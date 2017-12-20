/* 
 * File:   Diccionario.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

#include "Palabra.h"
#include "THashCerrada.h"

class Diccionario {
    
public:
    explicit Diccionario(unsigned long tam);
    Diccionario(const std::string &nomFich, unsigned long tam);
    Diccionario( const Diccionario& orig ) = default;
    virtual ~Diccionario() = default;
    
    Palabra *busca( const std::string &termino );
    bool inserta( const std::string &palabra );
    void entrena ( const std::string& palabra, const std::string& sucesor );
    void usaCorpus(const std::string nomFich);

private:
    THashCerrada<Palabra> _palabras;
};
#endif /* DICCIONARIO_H */

