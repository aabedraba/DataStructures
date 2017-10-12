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

using namespace std;

template <typename T>
class VDinamico {
public:
    
    /**
     * Contructor por defecto que asigna 1 como tamaño fisico y 0 como logico.
     */
    VDinamico ()
        : _tamF( 1 ),
          _tamL( 0 )
    {
        _vectorD = new T[_tamF];
    };
    
    /**
     * Contructor parametrizado.
     * @param tam tamaño logico que queremos asignar a nuestro vector.
     */
    VDinamico ( unsigned int tam )
        : _tamF( 1 ),    
          _tamL( tam )
    {
        _tamF = pow (2, std::ceil( log2( _tamL ) ) ); //2^log2(_tamL)
    
        _vectorD = new T[_tamF];
    };
    
    /**
     * Contructor de copia.
     * @param orig objeto de la clase VDinamico<T> que queremos copiar.
     */
    VDinamico ( const VDinamico<T>& orig )
        : _tamF( orig._tamF ),
          _tamL( orig._tamL )
    {
        _vectorD = new T[ _tamF ];
        for ( int i=0; i < _tamL; i++ ) {
            _vectorD[i] = orig._vectorD[i];
        }
    };
    
    /**
     * Contructor de copia parcial que copia solo un fragmento del vector.
     * @param orig objeto del tipo VDinamico<T> que queremos copiar.
     * @param inicio posicion donde queremos empezar a copiar.
     * @param num numero de posiciones que queremos copiar.
     */
    VDinamico ( const VDinamico<T>& orig, unsigned int inicio, unsigned int num )
        : _tamF ( orig._tamF ),
          _tamL ( num )
    {
        _vectorD = new T[_tamF];
        int contador = 0;
        for ( int i = inicio; i < inicio+num; i++ ) {
            _vectorD[contador] == orig._vectorD[i];
            contador++;
        }
    };
    
    /**
     * Destructor.
     */
    virtual ~VDinamico() {
        delete []_vectorD;
    };
    
    /**
     * Metodo get de tamaño logico.
     * @return atributo de tamaño lógico
     */
    unsigned int GetTamL() const {
        return _tamL;
    };
    
    
       
    /**
     * Operador de asignacion.
     * @param orig objeto de la clase VDinamico<T> cuyo contenido queremos copiar.
     * @return puntero que apunta a un VDinamico<T> que será una copia de orig.
     */
    VDinamico<T>& operator= (const VDinamico<T>& orig) {
        if ( *this != orig )
            delete []_vectorD;
        
        _tamF = orig._tamF;
        _tamL = orig._tamL;
        _vectorD = new T[_tamF];
        for (int i=0; i < _tamF; i++)
            _vectorD[i] = orig._vectorD[i];
        
        return *this;
    };
    
    /**
     * Operador que sustituye las operaciones de escritura/lectura.
     * @param pos posicion del vector que queremos buscar para su posterior
     lectura o sobreescritura.
     * @return posicion del vector pedida.
     */
    T& operator[] ( int pos ) {
        return _vectorD[pos];
    };
    
    int busquedaBin( const T &aBuscar ) {
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
    
    void insertar ( const T& dato, unsigned int pos = UINT_MAX){
        //Caso donde el Vector se ha llenado, doblo el tamaño del mismo
        if ( _tamL == _tamF ){ 
            _tamF *= 2;
            T auxiliar[_tamL]; //Creando en la pila
            for (int i = 0; i < _tamL; i++)
                auxiliar[i] = _vectorD[i];
            delete []_vectorD;
            _vectorD = new T[_tamF]; //Vector con el doble del tamaño
            for (int i = 0; i < _tamL; i++)
                _vectorD[i] = auxiliar[i];
        }
        //Caso donde hay que meter en mitad del vector, desplazamos todo a la derecha desde la posicion dada
        if ( ( pos < (_tamL) ) ){
            for (int i = (_tamL + 1); i > pos; i--)
                _vectorD[i] = _vectorD[i-1];
            _vectorD[pos] = dato;
            _tamL++;
        }
        else if ( pos == UINT_MAX ){ //En caso de que sea menor que el tamaño físico, meter al final del vector
            _vectorD[_tamL] = dato;
            _tamL++;
        }
        else
            throw std::out_of_range("[VDinamico::insertar]Posición fuera de rango.");
    }
    
    void eliminar ( unsigned int pos = GetTamL() ){
        T aux[_tamL];
        if ( pos == GetTamL() ){ //Caso de borrar al final
            for (int i = 0; i < (GetTamL()-1); i++)
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
        if (_tamL <= _tamF/3)
            _tamF /= 2;
        _vectorD = new T[_tamF];
        for (int i = 0; i < GetTamL(); i++)
            _vectorD[i] = aux[i];
    }

    void SetTamF(unsigned int _tamF) {
        this->_tamF = _tamF;
    }
    
private:
    
    T *_vectorD;
    unsigned int _tamF; //Tamaño fisico del vector.
    unsigned int _tamL; //Tamaño logico del vector.

};

#endif /* VDINAMICO_H */
