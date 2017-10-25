/* 
 * File:   VDinamico.h
 * Author: Jesus
 * suli14
 *
 * Created on 28 de septiembre de 2017, 16:37
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <cmath>
#include <stdexcept>
#include <climits>
#include <ios>
#include <valarray>

using namespace std;

template <typename T>
class VDinamico {
public:
    
    VDinamico ();
    VDinamico ( unsigned int tam );
    VDinamico ( const VDinamico<T>& orig );
    VDinamico ( const VDinamico<T>& orig, 
            unsigned int inicio, unsigned int num );
    virtual ~VDinamico();
    unsigned int GetTamL() const;
    unsigned int GetTamF() const;
    VDinamico<T>& operator= (const VDinamico<T>& orig);
    T& operator[] ( int pos );
    int busquedaBin( const T &aBuscar );
    void insertar ( const T& dato, unsigned int pos = UINT_MAX);  
    void eliminar ( unsigned int pos = UINT_MAX );
    void aumenta (); 
    void reducir ();
    
private:
    T *_vectorD;
    unsigned int _tamF; //Tamaño fisico del vector.
    unsigned int _tamL; //Tamaño logico del vector.
};

template<typename T>
VDinamico<T>::VDinamico ()
    : _tamF( 1 ),
      _tamL( 0 )
{
    _vectorD = new T[_tamF];
}

template<typename T>
VDinamico<T>::VDinamico ( unsigned int tam )
    : _tamF( 1 ),    
    _tamL( tam )
    {
    _tamF = pow (2, std::ceil( log2( _tamL ) ) ); //2^log2(_tamL)

    _vectorD = new T[_tamF];
}

template<typename T>
VDinamico<T>::VDinamico ( const VDinamico<T>& orig )
    : _tamF( orig._tamF ),
    _tamL( orig._tamL )
    {
    _vectorD = new T[ _tamF ];
    for ( int i=0; i < _tamL; i++ ) {
        _vectorD[i] = orig._vectorD[i];
    }
}

template<typename T>
VDinamico<T>::VDinamico ( const VDinamico<T>& orig, unsigned int inicio, unsigned int num )
    : _tamL ( num )
    {
    _tamF = pow (2, std::ceil( log2( _tamL ) ) );
    _vectorD = new T[_tamF];
    int contador = 0;
    for ( int i = inicio; i < inicio+num; i++ ) {
        _vectorD[contador] == orig._vectorD[i];
        contador++;
    }
}

template<typename T>
VDinamico<T>::~VDinamico() {
    delete []_vectorD;
}

template<typename T>
unsigned int VDinamico<T>::GetTamL() const{
    return _tamL;
}

template<typename T>
unsigned int VDinamico<T>::GetTamF() const{
    return _tamF;
}

template<typename T>
VDinamico<T>& VDinamico<T>::operator= (const VDinamico<T>& orig) {
    if ( *this != orig )
        delete []_vectorD;
    
    _tamF = orig._tamF;
    _tamL = orig._tamL;
    _vectorD = new T[_tamF];
    for (int i=0; i < _tamL; i++)
        _vectorD[i] = orig._vectorD[i];
    
    return *this;
}

template<typename T>
T& VDinamico<T>::operator[] ( int pos ) {
    if ( (pos < 0) || (pos >= _tamL) )
        throw std::out_of_range("[VDinamico::operator[]] Posicion fuera"
                " de rango");
    return _vectorD[pos];
}

template<typename T>
int VDinamico<T>::busquedaBin( const T &aBuscar ) {
    int posMaximo = _tamL; //Maximo de palabras declarado en VectorEstatico
    int posMinimo = 0;
    unsigned int posBuscada = (posMaximo - posMinimo) / 2;
    while ( (posMaximo - posMinimo) >= 0 ){
        if (  _vectorD[posBuscada] != aBuscar ) {
            if ( _vectorD[posBuscada] > aBuscar ) 
                posMaximo = posBuscada - 1;
            else 
                posMinimo = posBuscada + 1;
            posBuscada = posMinimo + (posMaximo - posMinimo)/2;
        } else 
            return posBuscada;
    } 
    return -1; //Para cuando posMaximo ya es 0, ergo: elemento no presente
}

template<typename T>
void VDinamico<T>::insertar ( const T& dato, unsigned int pos){
    //Caso donde el Vector se ha llenado, doblo el tamaño del mismo
    if ( _tamL == _tamF )
        aumenta();
    //Caso donde hay que meter en mitad del vector, desplazamos todo a la derecha desde la posicion dada
    if ( pos < _tamL ) {
        for ( long int i = (_tamL-1); i >= pos; i-- ){
            _vectorD[i+1] = _vectorD[i];
        }
        _vectorD[pos] = dato;
        _tamL++;
    }
    else if ( pos == UINT_MAX ){ 
        _vectorD[_tamL] = dato;
        _tamL++;
    }
    else
        throw std::out_of_range("[VDinamico::insertar]Posición fuera de rango.");
}

template<typename T>
void VDinamico<T>::aumenta (){
    _tamF *= 2;
    T *auxiliar = new T[_tamF];
    for ( int i = 0; i < _tamL; i++ )
        auxiliar[i] = _vectorD[i];
    delete []_vectorD;
    _vectorD = auxiliar;
}

template<typename T>
void VDinamico<T>::eliminar ( unsigned int pos ){
    T *aux = new T[_tamF];
    if ( pos == UINT_MAX ){ //Caso de borrar al final
        for (int i = 0; i < (_tamL-1); i++)
            aux[i] = _vectorD[i];
    } 
    else if ( pos < GetTamL() ){ //Caso de borrar en mitad
        int contador = 0; 
        for (int i = 0; i < GetTamL(); i++){
            if ( i == pos )
                contador++; //Me salto la posición que deseo eliminar
            aux[i] = _vectorD[contador];
            contador++;
        }
    }
    else
        throw std::out_of_range("[VDinamico::eliminar]Posicion fuera de rango.");
    
    delete []_vectorD;
    _tamL--;
    _vectorD = aux;
    if (_tamL <= _tamF/3){
        reducir();
    }
}

template<typename T>
void VDinamico<T>::reducir(){
    _tamF /= 2;
    T *aux = new T[_tamF];
    for ( int i = 0; i < _tamL; i++ )
        aux[i] = _vectorD[i];
    delete []_vectorD;
    _vectorD = aux;
}

#endif /* VDINAMICO_H */
