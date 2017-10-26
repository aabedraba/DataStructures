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
            Palabra palabra(linea);
            _vectorPalabras.push_back( palabra ); //La lista está ordenada
            total++;
        }
    }
    fe.close();
}

Diccionario::Diccionario( const Diccionario& orig ) {
    throw std::runtime_error("Vector de copia no implementado");
}

Diccionario::~Diccionario() {
}

void Diccionario::insertar( const std::string palabra, unsigned int &pos ) { //Const no funciona
    Palabra pal( palabra );
    std::vector<Palabra>::iterator iter = _vectorPalabras.begin();
    for ( pos = 0; pos < _vectorPalabras.size(); pos++) {
        if ( pal == _vectorPalabras[pos] ) //Evitamos duplicado
            throw std::invalid_argument("[Diccionario::insertar] Ya se encuentra en el diccionario");
        if ( pal < _vectorPalabras[pos] ){
            _vectorPalabras.insert( iter, pal ); //Insertar en la posición correspondiente
            return;
        }
        iter++;
    }
}

void Diccionario::eliminar( const std::string &palabra, unsigned int &pos ) {
    Palabra pal( palabra );
    std::vector<Palabra>::iterator iter = _vectorPalabras.begin();
    for (unsigned int i = 0; i < _vectorPalabras.size(); i++, iter++)
        if ( pal == _vectorPalabras[i] ){
            _vectorPalabras.erase( iter );
            pos = i;
            return;
        }
    throw std::invalid_argument("[Diccionario::eliminar]Elemento no encontrado para eliminar");

}

Palabra &Diccionario::busca( const std::string &termino, unsigned int &pos ) {
    Palabra aBuscar( termino );
    std::vector<Palabra>::iterator iter;
    int posMaximo = _vectorPalabras.size(); //Maximo de palabras declarado en VectorEstatico
    int posMinimo = 0;
    pos = (posMaximo - posMinimo) / 2;
    while ( (posMaximo - posMinimo) >= 0 ){
        if (  _vectorPalabras[pos] != aBuscar ) {
            if ( _vectorPalabras[pos] > aBuscar ) 
                posMaximo = pos - 1;
            else 
                posMinimo = pos + 1;
            pos = posMinimo + (posMaximo - posMinimo)/2;
        } else 
            return _vectorPalabras[pos];
    } 
    throw std::invalid_argument ("[Diccionario::busca]Palabra no encontrada");
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

//TODO preguntar la parte del catch al profesor
void Diccionario::entrena(const std::string frase) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        if ( sucesor != "" ){
            unsigned int posP;
            try {
                busca( palabra, posP );
            } catch (std::invalid_argument  &e) {
                insertar( palabra, posP);
            }
            _vectorPalabras[posP].introducirSucesor( sucesor );
            palabra = sucesor;
            sucesor = "";
        }
        
    }
}


