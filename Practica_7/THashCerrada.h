/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashCerrada.h
 * Author: aabedraba
 *
 * Created on November 26, 2017, 4:30 PM
 */

#ifndef THASHCERRADA_H
#define THASHCERRADA_H

#include <vector>
#include <cmath>


template <typename T>
class THashCerrada {
public:
    THashCerrada( long &tamTabla );
    THashCerrada( const THashCerrada& orig );
    virtual ~THashCerrada( );
    
    bool insertar( long clave, const T& dato );
//    long dispersion( long clave );
//    bool borrar( long clave, const T& dato );
//    T* buscar( long clave, const T& dato );
//    unsigned long tamTalbla();
//    unsigned long numElementos();
//    unsigned int maxColisiones();
//    unsigned int promedioColisiones();
//    float factorCarga();
    long calculaPrimo( long tamTabla);
    
private:
    typedef std::pair<unsigned long, T> elemento;
    std::vector<T> _tabla;

};

template <typename T>
THashCerrada<T>::THashCerrada( long &tamTabla )
    : _tabla( calculaPrimo(tamTabla) )
{};

template <typename T>
THashCerrada<T>::THashCerrada( const THashCerrada& orig )
    : _tabla ( orig._tabla )
{};

template<typename T>
THashCerrada<T>::~THashCerrada( ) 
{};


template<typename T>
long THashCerrada<T>::calculaPrimo( long tamTabla ) {
    long primo;
    if ( _tabla.size() % 2 == 0 )
        primo = _tabla.size() + 1;
    else
        primo = _tabla.size() + 2;
    
    bool noEsPrimo;
    do {
        noEsPrimo = false;
        for ( int i = 2, x = std::sqrt( primo ); i <= x; i++ ){
            if ( primo % i == 0 ){
                noEsPrimo = true;
                primo += 2;
                break;
            }
        }
    } while ( noEsPrimo );
    return primo;
}

template<typename T>
bool THashCerrada<T>::insertar( long clave, const T& dato ){
    long posicion = clave %_tabla.size();
    try {
        _tabla.at( posicion );
    } catch ( std::exception &e ){
        
    }
    _tabla.insert( clave, )
}

#endif /* THASHCERRADA_H */
