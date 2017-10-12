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
    std::cout << "Cargando palabras..." << std::endl;
    std::ifstream fe;
    std::string linea;
    int total = 0;
    fe.open( nomFich.c_str() ); //convierte nomFich en legible por ifstream::open
    if ( fe.good() ) {
        while ( !fe.eof() ) {
            getline( fe, linea );
            if ( linea != "" ) {
                Palabra palabra( linea );
                _vectorPalabras.asigna( palabra, total );
                total++;
            }
        }
            std::cout << "Carga de palabras realizada correctamente." << std::endl;
            fe.close();
    } else {
        fe.close();
        throw std::invalid_argument("[Diccionario::cargaPalabras]No se pudo abrir"
                " el fichero. Sugerencia: ¿nombre de archivo invalido?");
    }
    
}

int Diccionario::busca( const std::string termino ) {
    Palabra aBuscar( termino );
    return _vectorPalabras.busquedaBin( termino );
}

void Diccionario::inserta(const Palabra& aInsertar, int pos) {
    try{
        _vectorPalabras.asigna( aInsertar, pos );
    } catch ( std::string &e ){
        std::cerr << e << std::endl;
    }
}




