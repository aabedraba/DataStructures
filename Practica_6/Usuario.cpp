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


void Usuario::escribeFrase( std::string frase ) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        bool enDiccionario = _textPred->entrena( palabra, sucesor );
        if ( !enDiccionario ){
            Palabra *pal = _miDic.busca( palabra );
            if ( pal == 0 ) _miDic.inserta( palabra );
            _miDic.busca( palabra )->introducirSucesor( sucesor );
        }
        palabra = sucesor;
        sucesor = "";
    }
}

std::list<std::string> *Usuario::sugerencia( std::string termino ){
    bool dicBase = true, dicUser = true;
    
    std::list<std::string> *base = _textPred->sugerencia( termino );
    Palabra *enUsuario = _miDic.busca( termino );
    if ( base == 0 ) dicBase = false;
    if ( enUsuario == 0 ) dicUser = false;
    
    if ( !dicBase && !dicUser ){
        _miDic.inserta( termino );
        return 0;
    }
    
    if ( dicBase && dicUser ){
        std::list<std::string> *aux = new std::list<std::string>;
        auto iter = base->begin();
        for ( int i = 0; i < 5 && iter != base->end(); i++, iter++ )
            aux->push_back( (*iter ) );
        std::list<std::string> *user = enUsuario->sucesores();
        iter = user->begin();
        for ( int i = 0; i < 5 && iter != user->end() ; i++, iter++ )
            aux->push_back( ( *iter ) );
        return aux;
    } else if ( dicBase )
        return _textPred->sugerencia( termino );
    else
        return _miDic.busca( termino )->sucesores();  
}
