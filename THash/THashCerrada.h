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

#define MAX_COLISIONES 15
static unsigned long porDefecto = 0;


template <typename T>
class THashCerrada {
public:
    explicit THashCerrada( unsigned long &tamTabla );
    THashCerrada( const THashCerrada& orig ) = default;
    virtual ~THashCerrada( ) = default;

    unsigned long toDjb2( const char *str );
    unsigned long calculaPrimo(unsigned long tamTabla);

    unsigned long dispersionCuadratica( long clave, const T& dato, unsigned long &colisiones = porDefecto );
    unsigned long dispersionDoble( long clave, const T& dato, unsigned long &colisiones = porDefecto);
    bool inserta(long clave, const T &dato);
    bool borra(long clave, const T &dato);
    T* busca(long clave, const T &dato, unsigned long &posEnVector = porDefecto);
    unsigned long tamaTabla();
    unsigned long numElementos();
    unsigned long maxColisiones();
    unsigned long promedioColisiones();
    float factorCarga();


private:
    std::vector<std::pair<bool, T>> _tabla;
    unsigned long _numElementos;
    unsigned long _maxColisiones;
    unsigned long _promedioColisiones;
};

template <typename T>
THashCerrada<T>::THashCerrada(unsigned long &tamTabla )
    : _tabla( calculaPrimo(tamTabla) ),
      _numElementos( 0 ),
      _maxColisiones( 0 ),
      _promedioColisiones( 0 )
{}

template<typename T>
unsigned long THashCerrada<T>::calculaPrimo( unsigned long tamTabla ) {
    unsigned long primo;
    if ( !(tamTabla&1) ) //es par
        primo = tamTabla + 1;
    else
        primo = tamTabla + 2;

    bool noEsPrimo;
    do {
        noEsPrimo = false;
        for ( unsigned long i = 3, x = std::sqrt( primo ); i <= x; i+=2 )
            if ( !(primo % i) ){
                noEsPrimo = true;
                primo += 2;
                break;
            }
    } while ( noEsPrimo );
    return primo;
}


template <typename T>
unsigned long THashCerrada<T>::toDjb2( const char *str ) {
    unsigned long hash = 5381;
    long c;
    while ( c = *str++ )
        hash = ( (hash << 5) + hash ) + c;
    return hash;
}

template <typename T>
unsigned long THashCerrada<T>::dispersionCuadratica(long clave, const T &dato, unsigned long &colisiones) {
    unsigned long posicion;
    for (unsigned long i = 0; i < MAX_COLISIONES; ++i) {
        posicion = (clave + i*i) % _tabla.size();
        if ( _tabla[posicion].first == true && _tabla[posicion].second == dato ) {
            colisiones = i;
            return posicion;
        }
        if ( _tabla[posicion].first == false ) {
            colisiones = i;
            return posicion;
        }
    }
}

template <typename T>
unsigned long THashCerrada<T>::dispersionDoble(long clave, const T &dato, unsigned long &colisiones) {
    unsigned long posicion;
    long primerPrimo = calculaPrimo(_tabla.size()-1000);
    long segundoPrimo = calculaPrimo(_tabla.size()-500);
    long primerHash = clave % primerPrimo;
    long segundoHash = segundoPrimo - (clave % segundoPrimo);
    for (unsigned long i = 0; i < MAX_COLISIONES; ++i) {
        posicion = (primerHash + i*segundoHash) % _tabla.size();
        if ( _tabla[posicion].first == true && _tabla[posicion].second == dato ) {
            colisiones = i;
            return posicion;
        }
        if ( _tabla[posicion].first == false ) {
            colisiones = i;
            return posicion;
        }
    }
}

template<typename T>
bool THashCerrada<T>::inserta(long clave, const T &dato){
    unsigned long colisiones;
    unsigned long posicion = dispersionDoble(clave, dato, colisiones);
    if ( _tabla[posicion].first == true ) return false; //ya está insertado
    _tabla[posicion].first = true;
    _tabla[posicion].second = dato;
    ++_numElementos;
    _promedioColisiones = (_promedioColisiones + colisiones) / 2;
    if ( colisiones > _maxColisiones ) _maxColisiones = colisiones;
    return true;
}


template<typename T>
T* THashCerrada<T>::busca(long clave, const T &dato, unsigned long &posEnVector) {
    posEnVector = dispersionDoble(clave, dato);
    if ( _tabla[posEnVector].first == false ) return nullptr;
    else return &_tabla[posEnVector].second;
}

template <typename T>
bool THashCerrada<T>::borra(long clave, const T &dato) {
    unsigned long posicion;
    T* aBuscar = busca(clave, dato, posicion);
    if ( aBuscar != nullptr ) {
        _tabla[posicion].first = false;
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
unsigned long THashCerrada<T>::maxColisiones() {
    return _maxColisiones;
}

template <typename T>
unsigned long THashCerrada<T>::promedioColisiones() {
    return _promedioColisiones;
}

template <typename T>
float THashCerrada<T>::factorCarga() {
    return ( (float)_numElementos / (float)_tabla.size() );
}


#endif /* THASHCERRADA_H */

