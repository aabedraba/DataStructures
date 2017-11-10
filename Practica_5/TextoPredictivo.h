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

class TextoPredictivo {
public:
    TextoPredictivo( Diccionario &diccIdioma );
    TextoPredictivo( const TextoPredictivo& orig );
    virtual ~TextoPredictivo( );
    void entrena( std::string &frase );
    std::list<std::string> sugerencia( const std::string &termino, std::list<int> &ocurrencias );
private:
    Diccionario _diccIdioma;
};

#endif /* TEXTOPREDICTIVO_H */

