/* 
 * File:   TextoPredictivo.cpp
 * Author: aabedraba
 * 
 * Created on November 10, 2017, 4:59 PM
 */

#include "TextoPredictivo.h"

/**
 * Constructor parametrizado de TextoPredictivo.
 * @param diccIdioma referencia a un objeto de tipo diccionario.
 */
TextoPredictivo::TextoPredictivo( Diccionario &diccIdioma ) 
    : _diccIdioma ( diccIdioma ),
      _usuarios( 0 )
{}

/**
 * Contructor copia de TextoPredictivo.
 * @param orig TextoPredictivo que se quiere copiar.
 */
TextoPredictivo::TextoPredictivo( const TextoPredictivo& orig ) 
    : _diccIdioma ( orig._diccIdioma ),
      _usuarios ( orig._usuarios )
{}

TextoPredictivo::~TextoPredictivo()
{
}

void TextoPredictivo::nuevoUsuario( std::string id, std::string nombre ) {
    Usuario user( id, nombre, this );
    auto iter = _usuarios.begin();
    while ( iter != _usuarios.end() )
        if ( id == (*iter++).getId() )
            throw std::invalid_argument( "[TextoPredictivo::nuevoUsuario] Ya existe un usuario con el mismo id." );
    _usuarios.push_back( user );
}

Usuario *TextoPredictivo::getUsuario( std::string id ){
    auto iter = _usuarios.begin();
    while ( iter != _usuarios.end() ){
        if ( id == (*iter).getId() ) break;
        iter++;
    }
    if ( iter == _usuarios.end() )
        throw std::invalid_argument( "[TextoPredictivo::getUsuario] Usuario no existe." );
    return &( *iter );
}


/**
 * Metodo que llama al entrena de diccionario y realiza su misma funcion.
 * @param frase string que contiene la frase que se usara.
 */
bool TextoPredictivo::entrena( const std::string& palabra, const std::string& sucesor ) {
    Palabra *suc = _diccIdioma.busca( sucesor );
    Palabra *pal = _diccIdioma.busca( palabra ); 
    if ( suc == 0 || pal == 0 )
        return false;
    pal->introducirSucesor( sucesor );
    return true;
}

/**
 * Metodo que dado un termino, devuelve una lista con sus sucesores y otra con el numero de ocurrencias de estos sucesores.
 * @param termino string del que se quieren obtener sucesores.
 * @param ocurrencias referencia a lista de enteros que queremos rellenar con el numero de ocurrencias de los sucesores.
 * @return lista de string con los sucesores de termino.
 */
std::list<std::string> *TextoPredictivo::sugerencia( const std::string termino ) {
    Palabra *pal = _diccIdioma.busca( termino );
    if ( pal == 0 )
        return 0;
    return pal->sucesores( );
}




