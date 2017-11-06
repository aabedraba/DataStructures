/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sucesor.h
 * Author: aabedraba
 *
 * Created on November 6, 2017, 8:30 PM
 */

#ifndef SUCESOR_H
#define SUCESOR_H

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

#endif /* SUCESOR_H */

