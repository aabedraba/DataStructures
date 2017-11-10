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
#include "AVL.h"

class Diccionario {
    
public:
    Diccionario( const std::string &nomFich );
    Diccionario( const Diccionario& orig );
    virtual ~Diccionario();
    
    Palabra &busca( const std::string &termino );
    void inserta( const std::string &palabra, bool &insertado );
    void usaCorpus ( std::string nomFich );
    void entrena ( const std::string frase );
    
private:
    Avl<Palabra> _vec;
};
#endif /* DICCIONARIO_H */

