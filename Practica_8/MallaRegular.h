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
    MallaRegular( int XMin, int YMin, int XMax, int YMax, int aNDiv );
    MallaRegular( const MallaRegular& orig ) = default;
    virtual ~MallaRegular() = default;

    void insertar(float x, float y, const T &dato);
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

    unsigned int _numElementos;

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
    _numElementos++;
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

//TODO: finish
template <typename T>
std::vector<T> MallaRegular<T>::buscarPorRango(float rxmin, float rymin, float rxmax, float rymax) {
    std::vector<T> aDevolver;
    std::list<Casilla<T>> listaEntreRango;
    int i = ( rxmax - rxmin ) / _tamaCasillaX;
    int j = ( rymax - rymin ) / _tamaCasillaY;
    int contador = 0;
    while( contador < i && contador < j ) {
        Casilla<T> *aux = obtenerCasilla( contador + rxmin, contador + rymin );
        auto iter = aux->get_puntos().begin();
        while ( iter != aux->get_puntos().end() ){
            if ( (*iter).x > rxmin && (*iter).y < rymin )
                aDevolver.push_back( (*iter) );
            iter++;

        }
    }
    return aDevolver;
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
            Casilla<T>* casilla = obtenerCasilla( i,j );
            if ( casilla->numElementosCasilla() > maxElem ) maxElem = casilla->numElementosCasilla();
        }
    }
    return maxElem;
}

template <typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    float x = (_xMax - _xMin) / _tamaCasillaX;
    float y = (_yMax - _yMin) / _tamaCasillaY;
    return _numElementos / (x*y);
}

#endif //PRACTICA_8_MALLAREGULAR_H
