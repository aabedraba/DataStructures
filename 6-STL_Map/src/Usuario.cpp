/* 
 * File:   Usuario.cpp
 * Author: aabedraba
 * 
 * Created on November 16, 2017, 11:22 PM
 */

#include "Usuario.h"

/**
 * @brief Constructor por defecto parametrizado. Crea un nuevo usuario con un id, nombre y un puntero al objeto padre
 * (TextoPredictivo) que lo crea
 * @param id const string, número de identificación del usuario a crear
 * @param nombre const string, nombre del usuario a crear
 * @param textPred puntero al objeto padre que lo crea
 */
Usuario::Usuario(const std::string id, const std::string nombre, TextoPredictivo *textPred)
    : _id( id ),
      _nombre ( nombre ),
      _miDic(),
      _textPred( textPred )    
{}

/**
 * @brief Getter de id del usuario
 * @return id del usuario
 */
std::string Usuario::getId( ) const {
    return _id;
}

/**
 * @brief Dada una frase, entrena el diccionario del usuario añadiendo las palabras en los diccionario personal (si no se encontraban)
 * y añadiendo los sucesores a esas palabras.
 * @param frase const string, frase con la cual se va a entrenar el diccionario del usuario
 */
void Usuario::escribeFrase(const std::string frase) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        bool enDiccionario = _textPred->entrena( palabra, sucesor );
        //true, se ha insertado sucesor en la lista de sucesores de palabra, false si no se encuentra cualquiera
        //de los dos en el diccionario principal
        if ( !enDiccionario ){
            Palabra *pal = _miDic.busca( palabra );
            if ( pal == nullptr ) {_miDic.inserta( palabra ); pal = _miDic.busca( palabra );}
            pal->introducirSucesor( sucesor );
        }
        palabra = sucesor;
        sucesor = "";
    }
}

/**
 * @brief Crea una lista de sugerencias dependiendo de en qué diccionarios estén las palabras
 * @param termino const string, termino del cual se buscarán las sugerencias
 * @return dependiendo del diccionario en el que se encuentre, una lista de diez sugerencias
 */
std::list<std::string> Usuario::sugerencia(const std::string termino){
    bool enDicBase = true, enDicUser = true;
    std::list<std::string> base = _textPred->sugerencia( termino );
    Palabra *enUsuario = _miDic.busca( termino );
    if ( base.empty() ) enDicBase = false;
    if ( enUsuario == nullptr ) enDicUser = false;
    
    if ( !enDicBase && !enDicUser ){
        _miDic.inserta( termino );
        throw std::logic_error("[Usuario::sugerencia]No se ha encontrado la palabra");
    }
    
    if ( enDicBase && enDicUser ){
        std::list<std::string> user = enUsuario->sucesores();
        std::list<std::string> aux;

        auto iter = base.begin();
        for ( int i = 0; i < 5 && iter != base.end(); i++, iter++ )
            aux.push_back( (*iter ) );
        iter = user.begin();
        for ( int i = 0; i < 5 && iter != user.end() ; i++, iter++ )
            aux.push_back( ( *iter ) );
        return aux;
    } else if ( enDicBase )
        return base;
    else
        return enUsuario->sucesores();
}
