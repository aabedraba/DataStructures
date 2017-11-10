/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Palabra.h"

Palabra::Palabra()
    : _termino (""),
      _sucesores()
{}

Palabra::Palabra( std::string termino )
    : _termino ( termino ),
      _sucesores ()
{}

Palabra::Palabra(const Palabra& orig)
    : _termino( orig._termino ),
      _sucesores ( orig._sucesores )
{}

Palabra::~Palabra()
{}

Palabra &Palabra::operator =( const Palabra &otro ) {
    if ( *this != otro ){
        _termino = otro._termino; 
        _sucesores = otro._sucesores;
    }
    return *this;
}

bool Palabra::operator !=( const Palabra &otro ) const {
    if ( _termino != otro._termino ) 
             return true;
    return false;
}

bool Palabra::operator ==( const Palabra &otro ) const {
    return !(operator !=( otro ));
}

bool Palabra::operator >( const Palabra &otro ) const {
    if ( _termino > otro._termino ) 
        return true;
    return false;
}

bool Palabra::operator <( const Palabra &otro ) const{
    return !(operator >(otro));
}

std::string Palabra::getTermino() const {
    return _termino;
}

/**
 * Dado un string lo incluye como sucesor de la palabra.
 * @pre si ya existe, solo aumenta su numero de ocurrencias.
 * @param sucesor string que queremos anadir como sucesor de cierta palabra.
 */
void Palabra::introducirSucesor( std::string sucesor ) {
    Sucesor suces( sucesor );
    std::list<Sucesor>::iterator iter = _sucesores.begin();
    while ( iter != _sucesores.end()  ){
        if ( suces == (*iter) ){
            (*iter).aumentaOcurrencias();
            return;
        }
        iter++;
    }
    if ( iter == _sucesores.end() )//no se ha insertado nada
        _sucesores.push_back( suces );
}

/**
 * Metodo que lista todos los sucesores de cierta palabra.
 * @return devuelve una lista enlazada con todos los sucesores ordenados por 
 su numero de courrencias.
 */
std::list<std::string> Palabra::sucesores( std::list<int> &ocurrencias ) {
    std::list<std::string> aux;
    std::list<Sucesor>::iterator iter = _sucesores.begin();
    std::priority_queue<Sucesor> listaOrdenada;
    while ( iter != _sucesores.end() ){
        listaOrdenada.push( (*iter) );
        iter++;
    }
    while ( !listaOrdenada.empty() ){
        for (int i = 0; i < 10 && !listaOrdenada.empty(); i++){
            aux.push_back( listaOrdenada.top().getTermino() );
            ocurrencias.push_back( listaOrdenada.top().getNumOcurrencias() );
            listaOrdenada.pop();
        }
    }
    return aux;
}
