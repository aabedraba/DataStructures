/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"

/**
 * @brief Crea un diccionario vacío
 */
Diccionario::Diccionario()
    : _palabras()
{}

/**
 * @brief Constructor parametrizado de diccionario que lo inicia con un archivo que contiene palabras.
 * @param nomFich const string, fichero con el que vamos a cargar nuestro diccionario
 * @throw invalid_argument, en caso de que el archivo no sea legible
 */
Diccionario::Diccionario( const std::string &nomFich )
    : _palabras()
{
    std::ifstream fe;
    std::string linea;
    fe.open( nomFich.c_str() );
    
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

/**
 * @brief Introduce una palabra en el diccionario
 * @param palabra const string, palabra a introducir en el diccionario
 * @return true, en caso de que se haya insertado. false, en caso de que no se haya insertado (ya se encuentra)
 */
bool Diccionario::inserta( const std::string &palabra ) {
    Palabra p( palabra );
    std::pair<std::string, Palabra> aInsertar( palabra, p );
    return _palabras.insert( aInsertar ).second;
}

/**
 * @brief Devuelve un puntero a la palabra buscada en el diccionario
 * @param termino const string, palabra a buscar en el diccionario
 * @return Puntero hacia la palabra en el diccinario. nullptr, en caso de que no se encuentre en el diccionario.
 */
Palabra *Diccionario::busca( const std::string &termino ) {
    if ( _palabras.empty() )
        return nullptr;
    auto iter = _palabras.find( termino );
    if ( iter == _palabras.end() )
        return nullptr;
    return &(*iter).second;    
}

/**
 * @brief Dada una palabra y un sucesor, incluir el sucesor en la lista de sucesores de la palabra
 * @param palabra const string, palabra a la cual se le va a introducir un sucesor
 * @param sucesor const string, palabra que se incluirá como sucesor
 * @throw invalid_argument, en caso de que las palabras pasadas como parámetros estén vacías.
 */
void Diccionario::entrena( const std::string& palabra, const std::string& sucesor ) {
    if ( sucesor.empty() || palabra.empty() )
        throw std::invalid_argument( "[Diccionario::entrena] Argumento invalido. Cadena vacia." );

    Palabra pal( palabra );
    std::pair<std::string, Palabra> aInsertar( palabra, pal );
    auto iter = _palabras.find( palabra );
    (*iter).second.introducirSucesor( sucesor );
}


/**
 * @brief Entrena al diccionario con un corpus dado
 * @param nomFich const string, nombre del corpus
 * @post el objeto diccionario queda entrenado con todas las palabras del corpus
 */
void Diccionario::usaCorpus(const std::string nomFich) {
    std::ifstream fe;
    std::string frase;
    fe.open( nomFich.c_str() );
    if ( !fe.good() ){
        fe.close();
        throw std::invalid_argument( "[Diccionario::usaCorpus] No se pudo abrir"
                                             " el archivo. (¿Archivo incorrecto?)");
    }
    while ( !fe.eof() ) {
        getline(fe, frase);
        if (!frase.empty()) {
            std::stringstream ss(frase);
            std::string palabra, sucesor;
            ss >> palabra;
            while (!ss.eof()) {
                ss >> sucesor;
                Palabra *pal = busca(palabra);
                if (pal == nullptr) {
                    inserta(palabra);
                    pal = busca(palabra);
                }
                pal->introducirSucesor(sucesor);
                ss >> palabra;
                sucesor = "";
            }
        }
    }
    fe.close();
}

