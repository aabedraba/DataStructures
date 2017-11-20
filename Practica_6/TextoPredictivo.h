/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextoPredictivo.h
 * Author: aabedraba
 *
 * Created on November 10, 2017, 4:59 PM
 */

#ifndef TEXTOPREDICTIVO_H
#define TEXTOPREDICTIVO_H

#include "Diccionario.h"
#include <vector>
#include "Usuario.h"

class TextoPredictivo {
public:
    TextoPredictivo( Diccionario &diccIdioma );
    TextoPredictivo( const TextoPredictivo& orig );
    virtual ~TextoPredictivo( );
    bool entrena( std::string &frase );
    std::list<std::string> sugerencia( const std::string &termino, std::list<int> &ocurrencias );
    void nuevoUsuario( std::string id, std::string nombre );
    Usuario *getUsuario( std::string &id );
    
private:
    Diccionario _diccIdioma;
    std::vector<Usuario> _usuarios;
};

#endif /* TEXTOPREDICTIVO_H */

