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
#include "TextoPredictivo.h"
#include "Diccionario.h"


class Usuario {
public:
    Usuario( );
    Usuario( std::string id, std::string nombre );
    Usuario( const Usuario& orig );
    virtual ~Usuario( );
    std::list<std::string> sugerencia( std::string &termino );
    void escribeFrase( std::string &frase );
    std::string getId( ) const;
    std::string getNombre( ) const;
private:
    std::string _id;
    std::string _nombre;
    Diccionario _miDic;
};

#endif /* USUARIO_H */

