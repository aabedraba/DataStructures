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

    bool inserta(long clave, const T &dato);
    bool borra(long clave, const T &dato);
    T* busca(long clave, const T &dato, unsigned long &posEnVector = porDefecto);
    unsigned long tamaTabla();
    unsigned long numElementos();
    unsigned long maxColisiones();
    unsigned long promedioColisiones();
    float factorCarga();

private:
    unsigned long calculaPrimoMayor(unsigned long num);
    unsigned long dispersionCuadratica( long clave, const T& dato, unsigned long &colisiones = porDefecto );
    unsigned long dispersionDoble( long clave, const T& dato, unsigned long &colisiones = porDefecto);

private:
    std::vector<std::pair<bool, T>> _tabla;
    unsigned long _numElementos;
    unsigned long _maxColisiones;
    unsigned long _promedioColisiones;
};

/**
 * @brief constructor por defecto parametrizado que toma un tamaño indicado y le asigna a la table un tamaño n primo
 * @tparam T tipo del objeto
 * @param tamTabla tamaño tabla considerado
 */
template <typename T>
THashCerrada<T>::THashCerrada(unsigned long &tamTabla )
        : _tabla(calculaPrimoMayor(tamTabla) ),
          _numElementos( 0 ),
          _maxColisiones( 0 ),
          _promedioColisiones( 0 )
{}

/**
 * @brief calcula el primer primo más grande que el número dado
 * @tparam T tipo del objeto
 * @param num número al que se le va a calcular el primo mayor
 * @return primo mayor que el número dado
 */
template<typename T>
unsigned long THashCerrada<T>::calculaPrimoMayor(unsigned long num) {
    if ( num < 2 ) throw std::logic_error("[THashCerrada<T>::calculaPrimoMayor] Número incorrecto.");
    unsigned long primo;
    if ( !(num&1) ) //es par
        primo = num + 1;
    else
        primo = num + 2;

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

/**
 * @brief Función djb2 para calcular el hash de un string
 * @tparam T tipo del objeto
 * @param str tipo string a pasar
 * @return devuelve el hash calculado de ese string
 */
template <typename T>
unsigned long THashCerrada<T>::toDjb2( const char *str ) {
    unsigned long hash = 5381;
    long c;
    while ( c = *str++ )
        hash = ( (hash << 5) + hash ) + c;
    return hash;
}

/**
 * @brief Dispersión cuadrática para utilizar en la tabla
 * @tparam T tipo del objeto
 * @param clave clave del objeto precalculada para la tabla
 * @param dato objeto cuya posición se quiere calcular
 * @param colisiones [opcional] referencia que devuelve las colisiones que se han encontrado para ese objeto
 * @return la posición en la que se encuentra el objeto en la tabla o en la que debería de asignarse
 */
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

/**
 * @brief Dispersión doble para utilizar en la tabla
 * @tparam T tipo del objeto
 * @param clave clave del objeto precalculada para la tabla
 * @param dato objeto cuya posición se quiere calcular
 * @param colisiones [opcional] referencia que devuelve las colisiones que se han encontrado para ese objeto
 * @return la posición en la que se encuentra el objeto en la tabla o en la que debería de asignarse
 */
template <typename T>
unsigned long THashCerrada<T>::dispersionDoble(long clave, const T &dato, unsigned long &colisiones) {
    unsigned long posicion;
    long primerPrimo = calculaPrimoMayor(_tabla.size() - ( _tabla.size()/2 ) );
    long segundoPrimo = calculaPrimoMayor(_tabla.size() - ( _tabla.size()/4 ) );
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

/**
 * @brief Función para insertar un dato en la tabla hash
 * @tparam T tipo del objeto
 * @param clave  clave del objeto precalculada para la tabla
 * @param dato objeto a insertar en la tabla
 * @return true si se ha introducido, false si ya se encontraba en la tabla
 */
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

/**
 * @brief Función para buscar un objeto de la tabla hash
 * @tparam T tipo del objeto
 * @param clave clave del objeto precalculada para la tabla
 * @param dato objeto a buscar en la tabla
 * @param posEnVector [opcional] para saber en qué posición de la tabla se encuentra el objeto en caso de encontrarse
 * @return puntero hacia el objeto si se encuentra en la tabla. Puntero nulo en caso de no encontrarse.
 */
template<typename T>
T* THashCerrada<T>::busca(long clave, const T &dato, unsigned long &posEnVector) {
    posEnVector = dispersionDoble(clave, dato);
    if ( _tabla[posEnVector].first == false ) return nullptr;
    else return &_tabla[posEnVector].second;
}

/**
 * @brief Función para borrar un objeto de la tabla
 * @tparam T tipo del objeto
 * @param clave clave del objeto precalculada para la tabla
 * @param dato objeto a borrar de la tabla
 * @return true en caso de que se haya borrado. false en caso de que no se encontrase en la tabla
 */
template <typename T>
bool THashCerrada<T>::borra(long clave, const T &dato) {
    unsigned long posicion = dispersionDoble( clave, dato );
    if ( _tabla[posicion].first == true ) {
        _tabla[posicion].first = false;
        _numElementos--;
        return true;
    }
    else return false;
}

/**
 * @brief Devuelve el tamaño de la tabla
 * @tparam T tipo del objeto
 * @return tamaño de la tabla hash
 */
template <typename T>
unsigned long THashCerrada<T>::tamaTabla() {
    return _tabla.size();
}

/**
 * @brief Devuelve el número de elementos que hay en la tabla
 * @tparam T tipo del objeto
 * @return número de elementos de la tabla
 */
template <typename T>
unsigned long THashCerrada<T>::numElementos() {
    return _numElementos;
}

/**
 * @brief Devuelve el máximo número de colisiones encontradas
 * @tparam T tipo del objeto
 * @return máximo número de colisiones de la tabla
 */
template <typename T>
unsigned long THashCerrada<T>::maxColisiones() {
    return _maxColisiones;
}

/**
 * @brief Devuelve el promedio de colisiones realizadas en el proceso de inserción en la tabla
 * @tparam T tipo del objeto
 * @return promedio de colisiones ocurridas en la tabla
 */
template <typename T>
unsigned long THashCerrada<T>::promedioColisiones() {
    return _promedioColisiones;
}

/**
 * @brief Devuelve el factor de carga de la tabla
 * @tparam T tipo del objeto
 * @return factor de carga de la tabla hash
 */
template <typename T>
float THashCerrada<T>::factorCarga() {
    return ( (float)_numElementos / (float)_tabla.size() );
}


#endif /* THASHCERRADA_H */