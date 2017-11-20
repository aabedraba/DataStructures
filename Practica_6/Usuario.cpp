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
      _miDic ()
      
{}


Usuario::Usuario( const Usuario& orig )
    : _id ( orig._id ),
      _nombre ( orig._nombre ),
      _miDic ( orig._miDic )
{}

Usuario::~Usuario( ) {
}

//std::list<std::string> Usuario::sugerencia( std::string termino ) {
//}

//TODO resolver asociación entre clases
void Usuario::escribeFrase( std::string &frase ) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        bool enDiccionario; // = TextoPredictivo.entrena
        if ( enDiccionario ){
            //Añadir en DicBase el sucesor
        } else {
            _miDic.inserta( palabra );
        }
    }
}

std::string Usuario::getId( ) const {
    return _id;
}

std::string Usuario::getNombre( ) const {
    return _nombre;
}



