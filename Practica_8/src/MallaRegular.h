//
// Created by aabedraba on 14/12/17.
//

#ifndef PRACTICA_8_MALLAREGULAR_H
#define PRACTICA_8_MALLAREGULAR_H

#include "Casilla.h"
#include <vector>
#include <list>


template <typename T>
class MallaRegular {
public:
    MallaRegular(float XMin, float YMin, float XMax, float YMax, int aNDiv);
    MallaRegular( const MallaRegular& orig ) = default;
    virtual ~MallaRegular() = default;

    bool insertar(float x, float y, const T &dato);
    T *buscar(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);

    std::vector<T> buscarPorRango( float rxmin, float rymin, float rxmax, float rymax );
    unsigned int numElementos();
    unsigned int maxElementosEnCelda();
    float promedioElementosPorCelda();

private:
    Casilla<T> *obtenerCasilla(float x, float y);

private:
    float _xMin, _yMin, _xMax, _yMax; ///Tamañoo real global
    float _tamaCasillaX, _tamaCasillaY; ///Tamaño real de cada casilla

    std::vector<std::vector<Casilla<T> > > _mr; ///Vector 2D de casillas

    unsigned int _numElementos;
};

template <typename T>
MallaRegular<T>::MallaRegular(float XMin, float YMin, float XMax, float YMax, int aNDiv)
    : _xMin ( XMin ), _yMin ( YMin ), _xMax ( XMax ), _yMax ( YMax ), _numElementos( 0 ) {
    _tamaCasillaX = ( _xMax - _xMin ) / aNDiv;
    _tamaCasillaY = ( _yMax - _yMin ) / aNDiv;
    _mr.insert( _mr.begin(), aNDiv, std::vector<Casilla<T> >(aNDiv) );
}


template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla ( float x, float y ){
    float i = ( x - _xMin ) / _tamaCasillaX;
    float j = ( y - _yMin ) / _tamaCasillaY;
    return &_mr[i][j];
}

template <typename T>
T* MallaRegular<T>::buscar( float x, float y, const T &dato ) {
    Casilla<T> *c = obtenerCasilla( x, y );
    T *aDevolver = c->buscar( dato );
    if ( aDevolver != nullptr ) return aDevolver;
    return nullptr;
}
template<typename T>
bool MallaRegular<T>::insertar(float x, float y, const T& dato){
    if (!( x >= _xMin && x <= _xMax && y >= _yMin && y <= _yMax ))
        return false;
    Casilla<T> *c = obtenerCasilla( x,y );
    c->insertar( dato );
    _numElementos++;
    return true;
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla( x, y );
    if ( c->borrar( dato ) ) {
        _numElementos--;
        return true;
    }
    return false;
}

template <typename T>
std::vector<T> MallaRegular<T>::buscarPorRango(float rxmin, float rymin, float rxmax, float rymax) {
    std::vector<T> puntosEnRango;

    if ( rxmin > rxmax ) swap( rxmin, rxmax );
    if ( rymin > rymax ) swap( rymin, rymax );

    for ( float i = rxmin; i <= rxmax; i += _tamaCasillaX ) {
        for ( float j = rymin; j <= rymax; j += _tamaCasillaY) {
            Casilla<T> *c = obtenerCasilla( i, j );
            typename std::list<T>::iterator iter = c->_puntos.begin();
            while ( iter != c->_puntos.end() ) {
                if ( ( *iter ).y <= rxmax && ( *iter ).y >= rxmin && ( *iter ).x >= rymin && ( *iter ).x <= rymax )
                    puntosEnRango.push_back(( *iter ));
                iter++;
            }
        }
    }
    return puntosEnRango;
}

template <typename T>
unsigned int MallaRegular<T>::numElementos() {
    return _numElementos;
}

template <typename T>
unsigned int MallaRegular<T>::maxElementosEnCelda() {
    unsigned int maxElem = 0;
    for ( float i=_xMin; i<=_xMax; i+=_tamaCasillaX ) {
        for ( float j=_yMin; j<=_yMax; j+=_tamaCasillaY ) {
            Casilla<T> *casilla = obtenerCasilla( i, j );
            unsigned int tam = casilla->numElementosCasilla();
            if (  tam > maxElem )
                maxElem = casilla->numElementosCasilla();
        }
    }
    return maxElem;
}

template <typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    float aNDiv = ( _xMax - _xMin ) / _tamaCasillaX; //despejano número de divisiones
    return _numElementos / aNDiv;
}

#endif //PRACTICA_8_MALLAREGULAR_H
