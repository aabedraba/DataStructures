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
      _miDic(),
      _textPred( 0 )
{}

Usuario::Usuario( std::string id, std::string nombre, TextoPredictivo *textPred )
    : _id( id ),
      _nombre ( nombre ),
      _miDic(),
      _textPred( textPred )    
{}


Usuario::Usuario( const Usuario& orig )
    : _id ( orig._id ),
      _nombre ( orig._nombre ),
      _miDic ( orig._miDic ),
      _textPred ( orig._textPred )
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
        if ( !enDiccionario ){
            _miDic.inserta( palabra );
            _miDic.busca( palabra )->introducirSucesor( sucesor );
        }
        palabra = sucesor;
        sucesor = "";
    }
}

std::list<std::string> *Usuario::sugerencia( std::string termino ){
    bool dicBase = true, dicUser = true;
    std::list<std::string> *base = _textPred->sugerencia( termino );
    Palabra *enUsuario = _miDic.busca( "abdallah" );
    if ( enUsuario == 0 ) dicUser = false;
    if ( base->empty() ) dicBase = false;
    
    if ( !dicBase && !dicUser ){
        _miDic.inserta( termino );
        throw std::invalid_argument( "[Usuario::sugerencia] Palabra no existe" );
    }
    
    if ( dicBase && dicUser ){
        std::list<std::string> *aux = new std::list<std::string>;
        std::list<std::string> *user = enUsuario->sucesores();
        auto iter = base->begin();
        for ( int i = 0; i < 5; i++, iter )
            aux->push_back( (*iter ) );
        iter = user->begin();
        for ( int i = 0; i < 5; i++, iter++ )
            aux->push_back( ( *iter ) );
        return aux;
    } else if ( dicBase )
        _textPred->sugerencia( termino );
    else
        return _miDic.busca( termino )->sucesores();
    
}
