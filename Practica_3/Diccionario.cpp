/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"
#include <stdexcept>
#include <sstream>

Diccionario::Diccionario( std::string nomFich )
    : _vectorPalabras()
{
    std::ifstream fe;
    std::string linea;
    int total = 0;
    fe.open( nomFich.c_str() ); //convierte nomFich en legible por ifstream::open
    if ( !fe.good() ) {
        fe.close();
        throw std::invalid_argument("[Diccionario::cargaPalabras]No se pudo abrir"
                " el fichero. Sugerencia: ¿nombre de archivo invalido?");
    }
    
    while ( !fe.eof() ) {
        getline( fe, linea );
        if ( linea != "" ) {
            Palabra *palabra = new Palabra(linea);
            _vectorPalabras.insertar( *palabra ); //La lista está ordenada
            total++;
        }
    }
    fe.close();
}

//TODO hacer más tarde
Diccionario::Diccionario( const Diccionario& orig )
{
    throw std::runtime_error("Vector de copia no implementado");
}

Diccionario::~Diccionario() {
}

int Diccionario::busca( const std::string &termino ) {
    Palabra aBuscar( termino );
    return _vectorPalabras.busquedaBin( aBuscar );
}

void Diccionario::insertar( const std::string &palabra ) { //Const no funciona
    Palabra p( palabra );
    for (int i = 0; i < _vectorPalabras.GetTamL(); i++) {
        if ( p == _vectorPalabras[i] ) //Evitamos duplicado
            break;
        if ( p < _vectorPalabras[i] ){
            _vectorPalabras.insertar( p, i ); //Insertar en la posición correspondiente
            break;
        }
    }
}

void Diccionario::eliminar(const std::string& palabra) {
    Palabra p( palabra );
    for (unsigned int i = 0; i < _vectorPalabras.GetTamL(); i++) {
        if ( p == _vectorPalabras[i] )
            _vectorPalabras.eliminar( i );
    }

}

void Diccionario::usaCorpus(std::string nomFich) {
    std::ifstream fe;
    std::string frase;
    int totalLeido =  0;
    fe.open( nomFich.c_str() );
    if ( fe.good() ){
        while ( !fe.eof() ){
            getline( fe, frase );
            entrena( frase );
        }
    } else {
        fe.close();
        throw std::invalid_argument( "[Diccionario::usaCorpus] No se pudo abrir"
                " el archivo. (¿Archivo incorrecto?)");
    }
}

void Diccionario::entrena(const std::string frase) {
    std::stringstream ss( frase );
    std::string palabra;
    std::string sucesor;
    
    while ( getline( ss, palabra, ' ') ){
        int pos = busca( palabra );
        if ( pos == -1 )
            insertar( palabra );
        getline(ss, sucesor, ' ');
        pos = busca( sucesor );
        if ( pos == -1 )
            insertar( sucesor );
        
    }
}
