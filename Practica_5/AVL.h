/* 
 * File:   AVL.h
 * Author: Jesus
 * suli14
 *
 * Created on November 7, 2017, 5:24 PM
 */

#ifndef AVL_H
#define AVL_H

#include <queue>
#include <iostream>


template <typename T>
class Nodo {
public:
    Nodo( T &ele ):
        _izq( 0 ),
        _der( 0 ),
        _bal ( 0 ),
        _dato( ele )
//        _altura ( 0 )
    {};
    Nodo( const Nodo& orig ):
        _izq( orig._izq ),
        _der( orig._der ),
        _dato( orig._dato ),
        _bal ( orig._bal )
//        _altura ( orig._altura )
    {};
    virtual ~Nodo( )
    {};
    Nodo<T> *_izq;
    Nodo<T> *_der;
    T _dato;
    char _bal;
//    int _altura;
};

template <typename T>
class Avl {
public:
    Avl( );
    Avl( const Avl<T>& orig );
    Avl &operator=( const Avl<T>& orig );
    virtual ~Avl( );
    bool insertar( T &ele );
    bool buscar ( T &ele, T &result );
    void recorreInorden( );
    T &modificaDato( T &ele );
    unsigned int numElmentos( );
    int alturaAvl( );
    
private:
    void posordenBorrado ( Nodo<T> *p );
    void inorden ( Nodo<T> *p, std::queue<T> &cola );
    void rotIzqda( Nodo<T>* &p );
    void rotDecha( Nodo<T>* &p );
    int insertaDato( Nodo<T>* &c, T &dato );
    Nodo<T>* buscaClave (T &ele, Nodo<T> *p);
    int altura( Nodo<T> *n );
    void borraNodos ( Nodo<T>* p );
    
private:
    Nodo<T> *_raiz;
    unsigned int _numElementos;
    
};

/**
 * @brief constructor por defecto
 * @post objeto de la clase Avl creado sin elementos
 */
template <typename T>
Avl<T>::Avl()
    : _raiz( 0 ),
      _numElementos( 0 )
{}

/**
 * @brief constructor de copia
 * @param orig objeto de la clase Avl a copiar
 */
template <typename T>
Avl<T>::Avl( const Avl<T>& orig ){
    std::queue<T> cola;
    inorden( orig._raiz, cola );
    while( !cola.empty() ){
        insertar( cola.front() );
        cola.pop();
    }
}

/**
 * @orig operador de asignación
 * @param orig objeto de la clase Avl a copiar
 * @return referencia al propio objeto
 */
template <typename T>
Avl<T> &Avl<T>::operator =(const Avl<T>& orig){
    if ( *this != orig ){
        std::queue<T> cola;
        inorden( orig._raiz, cola );
        while( !cola.empty() ){
            insertar( cola.front() );
            cola.pop();
        }
    }
    return *this;  
}

/**
 * @brief destructor del objeto Avl, empezando desde la raíz
 */
template <typename T>
Avl<T>::~Avl(){
    posordenBorrado( _raiz );
}

/**
 * @brief 
 * @param p
 */
template <typename T>
void Avl<T>::borraNodos( Nodo<T>* p ){
    delete _raiz;
}

template <typename T>
void Avl<T>::posordenBorrado ( Nodo<T> *p ) {
    if ( p ) {
        posordenBorrado ( p->_izq );
        posordenBorrado ( p->_der );   
        delete p;
        p = 0;
    }
}

/**
 * Metodo recorre el Avl en inorden y coloca los elementos en una queue que se pasa por referencia.
 * @param p puntero a un nodo del Avl, normalmente será la raiz.
 * @param cola referencia a una queue que cargaremos con los datos del arbol en inorden.
 */
template <typename T>
void Avl<T>::inorden ( Nodo<T> *p, std::queue<T> &cola ){
    if ( p ){
        inorden ( p->_izq, cola );
        cola.push( p->_dato );
        inorden (p->_der, cola );
    }
}

/**
 * Metodo que muestra el contenido del Avl en inorden.
 */
template <typename T>
void Avl<T>::recorreInorden() {
    std::queue<T> cola;
    inorden ( _raiz, cola );
    while( !cola.empty() ){
        std::cout << cola.front() << ' ';
        cola.pop();
    }
    std::cout << "\n";
}

/**
 * Metodo que dado un puntero a un nodo desequilibrado, realiza una rotacion a la izquierda para equilibrarlo.
 * @param p puntero al nodo desequilibrado.
 */
template<typename T>
void Avl<T>::rotIzqda( Nodo<T>* &p ) {
    Nodo<T> *q = p, *r;
    p = r = q->_der;
    q->_der = r->_izq;
    r->_izq = q;
    q->_bal++;
    if ( r->_bal < 0 ) 
        q->_bal += -r->_bal;
    r->_bal++;
    if ( q->_bal > 0 ) 
        r->_bal += q->_bal;
}

/**
 * Metodo que dado un puntero a un nodo desequilibrado, realiza una rotacion a la derecha para equilibrarlo.
 * @param p puntero al nodo desequilibrado.
 */
template<typename T>
void Avl<T>::rotDecha( Nodo<T>* &p ) {
    Nodo<T> *q = p, *l;
    p = l = q->_izq;
    q->_izq = l->_der;
    l->_der = q;
    q->_bal--;
    if ( l->_bal > 0 ) 
        q->_bal -= l->_bal;
    l->_bal--;
    if ( q->_bal < 0 ) 
        l->_bal -= -q->_bal;
}

/**
 * Metodo que dado un dato de tipo T lo inserta en el Avl.
 * @param c referencia a un puntero a un nodo, normalmente la raiz, que se debe ir actualizando al insertar un nuevo nodo.
 * @param dato objeto de tipo T que se introduce en el Avl.
 * @return 
 */
template <typename T>
int Avl<T>::insertaDato( Nodo<T>* &c, T &dato  ) {
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new Nodo<T>(dato);
        c = p; deltaH = 1;
    } else if (dato > p->_dato) {
        if ( insertaDato( p->_der, dato ) ){
            p->_bal--;
            if ( p->_bal == -1 ) deltaH = 1;
            else if ( p->_bal == -2 ) {
                if ( p->_der->_bal == 1 ) 
                    rotDecha( p->_der );
                rotIzqda( c );
            } 
        } 
    } else if ( dato < p->_dato ) {
        if ( insertaDato( p->_izq, dato ) ){
            p->_bal++;
            if ( p->_bal == 1 ) deltaH = 1;
            else if ( p->_bal == 2 ) {
                if ( p->_izq->_bal == -1 ) 
                    rotIzqda( p->_izq );
                rotDecha(c);
            } 
        } 
    }
    
    return deltaH;
}

/**
 * Metodo que insertar un dato de tipo T en el Avl siempre que no este ya insertado.
 * @param ele objeto de tipo T que se quiere insertar.
 * @return devuelve true si el dato no existia y se ha insertado. False en caso de que ya existiese.
 */
template <typename T>
bool Avl<T>::insertar( T &ele ){
    bool encontrado = buscaClave( ele, _raiz );
    if ( !encontrado ) {
        insertaDato( _raiz, ele );
        _numElementos++;
        return true;
    }
    return false;
}

/**
 * Metodo recursivo privado que dado un objeto de tipo T lo busca en el Avl.
 * @param ele objeto de tipo T que se quiere buscar.
 * @param p puntero a nodo, normalmente sera la raiz, que se ira aztualizando conforme avancemos por el Avl 
 y cuyo dato iremos comparando con ele, hasta encontrar la coincidencia. 
 * @return puntero al nodo donde se encuentra ele, y puntero vacío si no se encuentra.
 */
template <typename T>
Nodo<T> *Avl<T>::buscaClave (T &ele, Nodo<T> *p){
    if (!p)
        return 0;
    else if ( ele < p->_dato )
        return buscaClave (ele, p->_izq);
    else if ( ele > p->_dato )
        return buscaClave (ele, p->_der);
    else return p;
}

/**
 * Metodo publico que dado un objeto de tipo T lo busca en el Avl.
 * @param ele objeto de tipo T que se quiere buscar.
 * @param result si se encuentra, actualiza este parametro con el elemento buscado.
 * @return devuelve true si se ha enontrado, false en caso contrario.
 */
template <typename T>
bool Avl<T>::buscar ( T &ele, T &result ){
    Nodo<T> *p = buscaClave ( ele, _raiz );
    if ( p ){
        result = p->_dato;
        return true;
    }
    return false;
    
}

/*Como no tenemos el borra hecho, y necesitamos modificar los sucesores, este
 *método sirve de puente para que en esta práctica podamos meter sucesores
 */
template <typename T>
T &Avl<T>::modificaDato ( T &ele ){
    Nodo<T> *p = buscaClave( ele, _raiz );
    if ( !p ){
        insertar( ele );
        p = buscaClave( ele, _raiz );
    }
    return p->_dato;
}

template <typename T>
unsigned int Avl<T>::numElmentos() {
    return _numElementos;
}
 /**
  * Metodo publico que muestra la altura del Avl.
  * @return entero con la altura exacta del Avl.
  */
template <typename T>
int Avl<T>::alturaAvl(){
    return altura( _raiz );
}
 /**
  * Metodo privado que calcula la altura del Avl.
  * @param n puntero al nodo, normalmente sera la raiz, del cual se quiere saber la altura.
  * @return entero con la altura del Avl.
  */
template <typename T>
int Avl<T>::altura( Nodo<T> *n ) {
    int alturaIzq; 
    int alturaDer;
    if( n==0 )
        return -1;
    else {
        alturaIzq = altura( n->_izq );
        alturaDer = altura( n->_der );

        if( alturaIzq > alturaDer )
            return alturaIzq + 1;
        else
            return alturaDer + 1;
    }
}

#endif /* AVL_H */

