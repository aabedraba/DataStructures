//
// Created by aabedraba on 14/12/17.
//

#ifndef PRACTICA_8_MALLAREGULAR_H
#define PRACTICA_8_MALLAREGULAR_H

#include "Casilla.h"
#include <vector>

template <typename T>
class MallaRegular {
public:
    MallaRegular( int XMin,int YMin, int XMax, int YMax, int aNDiv );
    MallaRegular( const MallaRegular& orig ) = default;
    virtual ~MallaRegular() = default;

    void insertar(float x, float y, const T &dato);
    T *buscar(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);

    std::vector<T> buscarRengo( float rxmin, float rymin, float rxmax, float rymax );
    unsigned numElementos();
    unsigned maxElementosEnCelda();
    float promedioElementosPorCelda();

private:
    Casilla<T> *obtenerCasilla(float x, float y);

private:
    float _xMin, _yMin, _xMax, _yMax; ///Tamañoo real global
    float _tamaCasillaX, _tamaCasillaY; ///Tamaño real de cada casilla

    std::vector<std::vector<Casilla<T> > > _mr; ///Vector 2D de casillas
};

template <typename T>
MallaRegular<T>::MallaRegular(int XMin, int YMin, int XMax, int YMax, int aNDiv)
    : _xMin ( XMin ), _yMin ( YMin ), _xMax ( XMax ), _yMax ( YMax ) {
    _tamaCasillaX = ( _xMax - _xMin ) / aNDiv;
    _tamaCasillaY = ( _yMax - _yMin ) / aNDiv;
    _mr.insert( _mr.begin(), aNDiv, std::vector<Casilla<T> >(aNDiv));
}


template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla (float x, float y){
    int i = ( x - _xMin ) / _tamaCasillaX;
    int j = ( y - _yMin ) / _tamaCasillaY;
    return &_mr[j][i];
}

template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    Casilla<T> *c = obtenerCasilla( x,y );
    c->insertar( dato );
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla( x, y );
    return c->borrar( dato );
}

#endif //PRACTICA_8_MALLAREGULAR_H
