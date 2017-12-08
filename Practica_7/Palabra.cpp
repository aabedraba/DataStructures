#include "Palabra.h"

Palabra::Palabra()
    : _termino (""),
      _siguiente()
{}

Palabra::Palabra( std::string termino )
    : _termino ( termino ),
      _siguiente ()
{}


Palabra &Palabra::operator =( const Palabra &otro ) {
    if ( *this != otro ){
        _termino = otro._termino; 
        _siguiente = otro._siguiente;
    }
    return *this;
}

bool Palabra::operator ==( const Palabra &otro ) const {
    if ( _termino == otro._termino ) 
        return true;
    return false;
}

bool Palabra::operator !=( const Palabra &otro ) const {
    return !( operator ==( otro ) );
}

bool Palabra::operator >( const Palabra &otro ) const {
    if ( _termino > otro._termino ) 
        return true;
    return false;
}

bool Palabra::operator <( const Palabra &otro ) const{
    if ( _termino < otro._termino ) 
        return true;
    return false;
}

std::string Palabra::getTermino() const {
    return _termino;
}
/**
 * @brief Introduce un sucesor a la lista del objeto Palabra
 * @param sucesor const string, sucesor a introducir en la lista
 * @post la lista de sucesores del objeto queda actualizada con el nuevo sucesor si este no se encontraba
 */
void Palabra::introducirSucesor(const std::string sucesor) {
    Sucesor suces( sucesor );
    std::list<Sucesor>::iterator iter = _siguiente.begin();
    while ( iter != _siguiente.end()  ){
        if ( suces == (*iter) ){
            (*iter).aumentaOcurrencias();
            return;
        }
        iter++;
    }
    if ( iter == _siguiente.end() )//no se ha insertado nada
        _siguiente.push_back( suces );
}

/**
 * @brief Lista los sucesores del objeto Palabra
 * @return una lista de máximo 10 sucesores más frecuentes de la palabra, o una lista vacía en caso de no tener sucesores
 */
std::list<std::string> Palabra::sucesores( ) {
    std::list<std::string> aux;
    std::list<Sucesor>::iterator iter = _siguiente.begin();
    std::priority_queue<Sucesor> listaOrdenada;
    int i = 0;
    while ( iter != _siguiente.end() ){
        listaOrdenada.push( (*iter) );
        i++ ;iter++;
    }
    if ( listaOrdenada.empty() ) return std::list<std::string>();
    for (int i = 0; i < 10 && !listaOrdenada.empty(); i++){
        aux.push_back( listaOrdenada.top().getTermino() );
        listaOrdenada.pop();
    }
    return aux;
}
