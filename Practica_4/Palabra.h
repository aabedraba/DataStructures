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
    bool operator !=( const Sucesor &otro ){
        if ( this->getTermino() != otro.getTermino() ) 
                 return true;
        return false;
    };
    bool operator ==( const Sucesor &otro ){
        return !(operator !=( otro ));
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

    void introducirSucesor( std::string sucesor ) {
        Sucesor suces( sucesor );
        std::list<Sucesor>::iterator iter = _sucesores.begin();
        while ( !iter._M_node != 0 ){
            if ( suces == (*iter) ){
                (*iter).aumentaOcurrencias();
                break;
            }
            iter++;
        }
        if ( iter._M_node->_M_next )//no se ha insertado nada
            _sucesores.push_back( suces );
    }

    //Mirar que no se esté copiando
    std::list<Sucesor> sucesores() const {
        return _sucesores;
    }

private:
    std::string _termino;
    std::list<Sucesor> _sucesores;
};

#endif /* PALABRA_H */

