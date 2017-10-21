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
        : _termino ( termino )
    {};
    
    Sucesor( const Sucesor &orig )
        : _termino ( orig._termino ),
          _numOcurrencias ( orig._numOcurrencias )
    {};
    virtual ~Sucesor( ) {
    }

private:
    std::string _termino;
    int _numOcurrencias;
};

class Palabra {
public:
    Palabra()
        : _termino ("")
    {};
    
    Palabra( std::string termino )
        : _termino ( termino )
    {};
    
    Palabra(const Palabra& orig)
        : _termino( orig._termino )
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
private:
    std::string _termino;
    ListaEnlazada<Sucesor> sucesores;
    
};

#endif /* PALABRA_H */

