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
#include <optional>

#define MAX_COLISIONES 500
static long posPorDefecto = 0;


template <typename T>
class THashCerrada {
public:
    explicit THashCerrada( long &tamTabla );
    THashCerrada( const THashCerrada& orig );
    virtual ~THashCerrada( ) = default;

    unsigned long toDjb2( const char *str );
    unsigned long calculaPrimo( long tamTabla);

    bool insertar( long clave, const T& dato );
    bool borrar( long clave, const T& dato );
    T* buscar( long clave, const T& dato, long &posEnVector = posPorDefecto );
    unsigned long tamaTabla();
    unsigned long numElementos();
    unsigned int maxColisiones();
    unsigned int promedioColisiones();
    float factorCarga();

private:
    std::vector<std::pair<bool, T>> _tabla;
    unsigned long _numElementos;
    unsigned int _maxColisiones;
    unsigned int _promedioColisiones;
};

template <typename T>
THashCerrada<T>::THashCerrada( long &tamTabla )
    : _tabla( calculaPrimo(tamTabla) ),
      _numElementos( 0 ),
      _maxColisiones( 0 ),
      _promedioColisiones( 0 )
{};

template <typename T>
THashCerrada<T>::THashCerrada( const THashCerrada& orig )
    : _tabla ( orig._tabla ),
      _numElementos( orig._numElementos ),
      _maxColisiones( orig._maxColisiones ),
      _promedioColisiones( orig._promedioColisiones )
{};


template<typename T>
unsigned long THashCerrada<T>::calculaPrimo( long tamTabla ) {
    long primo;
    if ( tamTabla % 2 == 0 )
        primo = tamTabla + 1;
    else
        primo = tamTabla + 2;

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


template <typename T>
unsigned long THashCerrada<T>::toDjb2( const char *str ) {
    unsigned long hash = 5381;
    int c;
    while ( c = *str++ )
        hash = ( (hash << 5) + hash ) + c;
    return hash;
}


template<typename T>
bool THashCerrada<T>::insertar( long clave, const T& dato ){
    long posicion;
    int i;
    for (i = 0; i <= MAX_COLISIONES; ++i) {
        posicion = (clave + i*i) % _tabla.size();
        if ( _tabla[posicion].first == true && _tabla[posicion].second == dato ) return false;
        if ( _tabla[posicion].first == false ) {
            _tabla[posicion].first = true;
            _tabla[posicion].second = dato;
            ++_numElementos;
            break;
        }
    }
    _promedioColisiones = (_promedioColisiones + i) / 2;
    if ( i > _maxColisiones ) _maxColisiones = i;
    return true;
}


template<typename T>
T* THashCerrada<T>::buscar(long clave, const T &dato, long &posEnVector) {
    long posicion;
    for (int i = 0; i <= MAX_COLISIONES; ++i) {
        posicion = (clave + i*i) % _tabla.size();
        if ( _tabla[posicion].first == true )
            if ( _tabla[posicion].second == dato ) {
                posEnVector = posicion;
                return &_tabla[posicion].second;
            }
    }
    return nullptr;
}

template <typename T>
bool THashCerrada<T>::borrar(long clave, const T &dato) {
    long posEnVector;
    T* aBuscar = buscar( clave, dato, posEnVector );
    if ( aBuscar != nullptr ) {
        _tabla[posEnVector].first = false;
        _numElementos--;
        return true;
    }
    else return false;
}

template <typename T>
unsigned long THashCerrada<T>::tamaTabla() {
    return _tabla.size();
}

template <typename T>
unsigned long THashCerrada<T>::numElementos() {
    return _numElementos;
}

template <typename T>
unsigned int THashCerrada<T>::maxColisiones() {
    return _maxColisiones;
}

template <typename T>
unsigned int THashCerrada<T>::promedioColisiones() {
    return _promedioColisiones;
}

template <typename T>
float THashCerrada<T>::factorCarga() {
    return ( (float)_numElementos / (float)_tabla.size() );
}

#endif /* THASHCERRADA_H */

