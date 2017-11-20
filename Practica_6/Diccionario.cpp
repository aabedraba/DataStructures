/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"

Diccionario::Diccionario( ) 
    : _palabras()
{}


/**
 * Constructor parametrizado de diccionario.
 * @param nomFich fichero con el que queremos crear nuestro diccionario.
 */
Diccionario::Diccionario( const std::string &nomFich )
    : _palabras()
{
    std::ifstream fe;
    std::string linea;
    fe.open( nomFich.c_str() ); //convierte nomFich en legible por ifstream::open
    
    if ( !fe.good() ) {
        fe.close();
        throw std::invalid_argument("[Diccionario::cargaPalabras]No se pudo abrir"
                " el fichero. Sugerencia: ¿nombre de archivo invalido?");
    }
    
    while ( !fe.eof() ) {
        getline( fe, linea );
        if ( linea != "" ) {
            Palabra palabra(linea);
            std::pair<std::string, Palabra> aInsertar( linea, palabra );
            _palabras.insert( aInsertar ); //La lista está ordenada
        }
    }
    fe.close();
}

Diccionario::Diccionario( const Diccionario& orig ) 
    : _palabras ( orig._palabras )
{}

Diccionario::~Diccionario() {
}

//TODO mirar por qué me devuelve una pos superior
/**
 * Metodo que inserta una palabra en el diccionario a traves de un string.
 * @param palabra string de la nueva palabra que queremos introducir.
 * @param pos posicion donde colocaremos la nueva palabra y que se actualizará cuando se haga.
 * @throw lanza una excepcion de tipo invalid_argument si la palabra ya existe.
 */
bool Diccionario::inserta( const std::string &palabra ) {
    Palabra p( palabra );
    std::pair<std::string, Palabra> aInsertar( palabra, p );
    return _palabras.insert( aInsertar ).second;
}

/**
 * Metodo que busca una palabra en el diccionario a traves de un string.
 * @param termino string de la palabra que queremos buscar.
 * @param pos posicion donde se encuentra dicha palabra y que se actualizara cuando se encuentre.
 * @return devuelve un objeto de tipo palabra con la palabra buscada.
 * @throw lanza una excepcion de tipo invalid_argument si la palabra no existe.
 */
Palabra *Diccionario::busca( const std::string &termino ) {
    auto iter = _palabras.find( termino );
    if ( iter == _palabras.end() )
        return 0;
    return &(*iter).second;    
}

/**
 * Metodo que a partir de una frase analizará las palabras que contiene y observará 
 el término que la precede y actualizará con él su lista de sucesores en el diccionario.
 * @param frase string que contiene la frase que usaremos.
 */
void Diccionario::entrena( const std::string& palabra, const std::string& sucesor ) {
    if ( sucesor == "" || palabra == "")
        throw std::invalid_argument( "[Diccionario::entrena] Argumento invalido. Cadena vacia." );

    Palabra pal( palabra );
    std::pair<std::string, Palabra> aInsertar( palabra, pal );
    auto iter = _palabras.find( palabra );
    (*iter).second.introducirSucesor( sucesor );
}

