/* 
 * File:   VectorEstatico.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:56 AM
 */

#include <stdexcept>

#include "VectorEstatico.h"

VectorEstatico::VectorEstatico( )
    : _TAM(80383)
{
    _palabras = new Palabra[_TAM];
}

VectorEstatico::VectorEstatico( const VectorEstatico& orig ) 
    : _TAM(orig._TAM)
{
    for (int i = 0; i < _TAM; i++) {
        _palabras[i] = orig._palabras[i]; //no hace falta sobrecargar el operador
    }
}

VectorEstatico::~VectorEstatico( ) {
    delete []_palabras;
}

int VectorEstatico::getTAM() const {
    return _TAM;
}

void VectorEstatico::asigna( const Palabra &palabra, unsigned int pos ) {
    if ( pos >= this->getTAM() ) throw std::out_of_range( "[VectorEstatico::asigna] Posicion fuera "
            "de rango" );
    
    _palabras[pos] = palabra;
}

Palabra* VectorEstatico::recupera( unsigned int pos ) {
    if ( pos >= this->getTAM() ) throw std::out_of_range( "[VectorEstatico::recupera] Posicion "
            "de rango" );
    
    return &_palabras[pos];
}

int VectorEstatico::busquedaBin( const Palabra &aBuscar ) {
    int posMaximo = this->getTAM() -1 ; //Maximo de palabras declarado en VectorEstatico
    int posMinimo = 0;
    unsigned int posBuscada = (posMaximo - posMinimo) / 2;
    while ( (posMaximo - posMinimo) >= 0 ){
        if (  _palabras[posBuscada] != aBuscar ) {
            if ( _palabras[posBuscada] > aBuscar ) posMaximo = posBuscada - 1;
            else posMinimo = posBuscada + 1;
            posBuscada = posMinimo + (posMaximo - posMinimo)/2;
        } else return posBuscada;
    } 
    return -1; //Para cuando posMaximo ya es 0, ergo: elemento no presente
}