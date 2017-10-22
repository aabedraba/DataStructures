/* 
 * File:   Palabra.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:56 AM
 */

#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include "ListaEnlazada.h"

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
    virtual ~Sucesor( ) {
    }
    
    void aumenta(){
        _numOcurrencias++;
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
        if ( *this != otro )
            this->_termino = otro._termino;      
        return *this;
    }
    
    bool operator !=( const Palabra &otro ){
        if ( this->GetTermino() != otro.GetTermino() ) 
                 return true;
        return false;
    };
    
    bool operator ==( const Palabra &otro ){
        return !(operator !=( otro ));
    }
    
    bool operator >( const Palabra &otro ){
        if ( this->GetTermino() > otro.GetTermino() ) 
            return true;
        return false;
    }
    
    bool operator <( const Palabra &otro ){
        return !(operator >(otro));
    }

    void SetTermino(std::string _termino) {
        this->_termino = _termino;
    }

    std::string GetTermino() const {
        return _termino;
    }

    void SetSucesores( ListaEnlazada<Sucesor> sucesores ) {
        this->_sucesores = _sucesores;
    }

    ListaEnlazada<Sucesor> GetSucesores( ) const {
        return _sucesores;
    }

private:
    std::string _termino;
    ListaEnlazada<Sucesor> _sucesores;
};

#endif /* PALABRA_H */

