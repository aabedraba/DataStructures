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


void Diccionario::insertar( Palabra &p, int& pos ) { //Const no funciona
    for ( pos = 0; pos < _vectorPalabras.GetTamL(); pos++) {
        if ( p == _vectorPalabras[pos] ) //Evitamos duplicado
            break;
        if ( p < _vectorPalabras[pos] ){
            _vectorPalabras.insertar( p, pos ); //Insertar en la posición correspondiente
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
    fe.open( nomFich.c_str() );
    if ( !fe.good() ){
        fe.close();
        throw std::invalid_argument( "[Diccionario::usaCorpus] No se pudo abrir"
                " el archivo. (¿Archivo incorrecto?)");
    }
    while ( !fe.eof() ){
        getline( fe, frase );
        entrena( frase );
    }
    fe.close();
}

void Diccionario::entrena(const std::string frase) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        if ( sucesor != "" ){
            int posP;
            busca( palabra, posP );
            _vectorPalabras[posP].SetSucesores( sucesor );
            palabra = sucesor;
            sucesor = "";
        }
        
    }
}

Palabra &Diccionario::busca( const std::string &termino, int &pos ) {
    Palabra aBuscar( termino );
    int p = _vectorPalabras.busquedaBin( aBuscar );
    if ( p == -1 ){
        insertar( aBuscar, pos );
        return _vectorPalabras[pos];
    }
    pos = p;
    return _vectorPalabras[pos];
}
