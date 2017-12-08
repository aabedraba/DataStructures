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
#include <stdexcept>
#include <sstream>
#include <map>

class Diccionario {
    
public:
    Diccionario();
    Diccionario( const std::string &nomFich );
    Diccionario( const Diccionario& orig ) = default;
    virtual ~Diccionario() = default;
    
    Palabra *busca( const std::string &termino );
    bool inserta( const std::string &palabra );
    void entrena ( const std::string& palabra, const std::string& sucesor );
    void usaCorpus(const std::string nomFich);
    
private:
    std::map<std::string, Palabra> _palabras;
};
#endif /* DICCIONARIO_H */

