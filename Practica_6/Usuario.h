/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Usuario.h
 * Author: aabedraba
 *
 * Created on November 16, 2017, 11:22 PM
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <list>
#include <sstream>
#include "Diccionario.h"
#include "TextoPredictivo.h"

class TextoPredictivo;

class Usuario {
public:
    Usuario(const std::string id, const std::string nombre, TextoPredictivo *textPred);
    Usuario( const Usuario& orig ) = default;
    virtual ~Usuario() = default;

    std::string getId( ) const;

    void escribeFrase(const std::string frase);
    std::list<std::string> sugerencia(const std::string termino);
private:
    std::string _id;
    std::string _nombre;
    Diccionario _miDic;
    TextoPredictivo *_textPred;
};

#endif /* USUARIO_H */

