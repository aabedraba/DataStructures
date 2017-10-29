/* 
 * File:   Palabra.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:56 AM
 */

#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include <list>
#include <queue>

class Sucesor{
public:
    Sucesor( std::string termino )
        : _termino ( termino ),
          _numOcurrencias ( 1 )
    {};
    
    Sucesor( const Sucesor &orig )
        : _termino ( orig._termino ),
          _numOcurrencias ( orig._numOcurrencias )
    {};
    virtual ~Sucesor() {
    };
    bool operator!= ( const Sucesor &otro ) const{
        if ( _termino != otro._termino ) 
                 return true;
        return false;
    };
    bool operator== ( const Sucesor &otro ) const{
        return !(operator !=( otro ));
    }
    bool operator <( const Sucesor &otro ) const{
        if ( _numOcurrencias < otro._numOcurrencias )
            return true;
        return false;
    }
    void aumentaOcurrencias(){
        _numOcurrencias++;
    }

    std::string getTermino( ) const {
        return _termino;
    }

    int getNumOcurrencias( ) const {
        return _numOcurrencias;
    }

private:
    std::string _termino;
    int _numOcurrencias;
};

class Palabra {
public:
    Palabra()
        : _termino (""),
          _sucesores()
    {};
    
    Palabra( std::string termino )
        : _termino ( termino ),
          _sucesores ()
    {};
    
    Palabra(const Palabra& orig)
        : _termino( orig._termino ),
          _sucesores ( orig._sucesores )
    {};
    
    virtual ~Palabra()
    {};
    
    Palabra &operator =( const Palabra &otro ) {
        if ( *this != otro ){
            this->_termino = otro._termino; 
            this->_sucesores = otro._sucesores;
        }
        return *this;
    }
    
    bool operator !=( const Palabra &otro ) const {
        if ( _termino != otro._termino ) 
                 return true;
        return false;
    };
    
    bool operator ==( const Palabra &otro ) const {
        return !(operator !=( otro ));
    }
    
    bool operator >( const Palabra &otro ) const {
        if ( _termino > otro._termino ) 
            return true;
        return false;
    }
    
    bool operator <( const Palabra &otro ) const{
        return !(operator >(otro));
    }

    void SetTermino(std::string _termino) {
        this->_termino = _termino;
    }

    std::string GetTermino() const {
        return _termino;
    }
    
    /**
     * Dado un string lo incluye como sucesor de la palabra.
     * @pre si ya existe, solo aumenta su numero de ocurrencias.
     * @param sucesor string que queremos anadir como sucesor de cierta palabra.
     */
    void introducirSucesor( std::string sucesor ) {
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

    //Mirar que no se esté copiando
    /**
     * Metodo que lista todos los sucesores de cierta palabra.
     * @return devuelve una lista enlazada con todos los sucesores ordenados por 
     su numero de courrencias.
     */
    std::list<Sucesor> sucesores() {
        std::list<Sucesor> aux;
        std::list<Sucesor>::iterator iter = _sucesores.begin();
        std::priority_queue<Sucesor> listaOrdenada;
        if ( iter != _sucesores.end() ){
            while ( iter != _sucesores.end() ){
                listaOrdenada.push( (*iter) );
                iter++;
            }
            while ( !listaOrdenada.empty() ){
                aux.push_back( listaOrdenada.top() );
                listaOrdenada.pop();
            }
            _sucesores = aux;
        }  
        return _sucesores;
    }

private:
    std::string _termino;
    std::list<Sucesor> _sucesores;
};

#endif /* PALABRA_H */

