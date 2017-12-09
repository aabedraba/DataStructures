/* 
 * File:   TextoPredictivo.cpp
 * Author: aabedraba
 * 
 * Created on November 10, 2017, 4:59 PM
 */

#include "TextoPredictivo.h"

/**
 * @brief Constructor parametrizado que recibe un diccionario base
 * @param diccIdioma referencia al diccionario base del objeto
 */
TextoPredictivo::TextoPredictivo( Diccionario &diccIdioma ) 
    : _diccIdioma ( diccIdioma ),
      _usuarios( )
{}

/**
 * @brief Crea un nuevo usuario de la clase
 * @param id número de identificación del usuario a crear
 * @param nombre nombre del usuario a crear
 * @post se crea un usuario en el sistema con una referncia al objeto TextoPredictivo que lo crea
 * @throw invalid_argument si existe un usuario con el mismo id ya creado
 */
void TextoPredictivo::nuevoUsuario( std::string id, std::string nombre ) {
    Usuario user( id, nombre, this );
    auto iter = _usuarios.begin();
    while ( iter != _usuarios.end() )
        if ( id == (*iter++).getId() )
            throw std::invalid_argument( "[TextoPredictivo::nuevoUsuario] Ya existe un usuario con el mismo id." );
    _usuarios.push_back( user );
}

/**
 * @brief Devuelve un puntro a un usuario dado su id
 * @param id número de identificación del usuario a buscar
 * @return puntero al usuario buscado
 * @throw invalid_argument en caso de que el usuario no se haya encontrado
 */
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
 * @brief Busca la palabra y su sucesor en el diccionario
 * @param palabra string palabra a la cual se le va a introducir un sucesor
 * @param sucesor  string palabra que será el sucesor a introducir
 * @return true en caso de que se hayan encontrado las dos palabras en el diccionario y se haya insertado sucesor en palabra.
 * false en caso de que uno de los dos no se encuentre en el diccionario principal
 */
bool TextoPredictivo::entrena( const std::string& palabra, const std::string& sucesor ) {
    Palabra *suc = _diccIdioma.busca( sucesor );
    Palabra *pal = _diccIdioma.busca( palabra ); 
    if ( suc == nullptr || pal == nullptr )
        return false;
    _diccIdioma.entrena( palabra, sucesor );
    return true;
}

/**
 * @brief Dado un termino, devuelve los sucesores de este
 * @param termino string término del cual se buscan los sucesores
 * @return en caso de que el término se encuentre, devuelve los una lista de sucesores que tenga en el diccionario principal.
 * En caso contrario, devuelve una lista vacía
 */
std::list<std::string> TextoPredictivo::sugerencia( const std::string termino ) {
    Palabra *pal = _diccIdioma.busca( termino );
    return pal ? pal->sucesores() : std::list<std::string>();
}




