/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"
#include <stdexcept>

Diccionario::Diccionario( std::string nomFich )
    : _vectorPalabras()
{
    cargaPalabras( nomFich );
}

Diccionario::Diccionario( const Diccionario& orig )
{
    throw std::runtime_error("Vector de copia no implementado");
}

Diccionario::~Diccionario() {
}

void Diccionario::cargaPalabras( const std::string &nomFich ) {
    std::ifstream fe;
    std::string linea;
    int total = 0;
    fe.open( nomFich.c_str() ); //convierte nomFich en legible por ifstream::open
    if ( fe.good() ) {
        while ( !fe.eof() ) {
            getline( fe, linea );
            if ( linea != "" ) {
                Palabra palabra( linea );
                _vectorPalabras.insertar( palabra ); //La lista está ordenada
                total++;
            }
        }
            fe.close();
    } else {
        fe.close();
        throw std::invalid_argument("[Diccionario::cargaPalabras]No se pudo abrir"
                " el fichero. Sugerencia: ¿nombre de archivo invalido?");
    }
    
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
