/* 
 * File:   Usuario.cpp
 * Author: aabedraba
 * 
 * Created on November 16, 2017, 11:22 PM
 */

#include "Usuario.h"

Usuario::Usuario( )
    : _id(""),
      _nombre(""),
      _miDic()
{}

Usuario::Usuario( std::string id, std::string nombre )
    : _id( id ),
      _nombre ( nombre ),
      _miDic()
      
{}


Usuario::Usuario( const Usuario& orig )
    : _id ( orig._id ),
      _nombre ( orig._nombre ),
      _miDic ( orig._miDic )
{}

Usuario::~Usuario( ) {
}

std::string Usuario::getId( ) const {
    return _id;
}

std::string Usuario::getNombre( ) const {
    return _nombre;
}

void Usuario::escribeFrase( std::string &frase ) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        bool enDiccionario = _textPred->entrena( palabra, sucesor );
        if ( enDiccionario )
            break;
        _miDic.inserta( palabra );
        _miDic.busca( palabra ).introducirSucesor( sucesor );
        palabra = sucesor;
        sucesor = "";
    }
}

