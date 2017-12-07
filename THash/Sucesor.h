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
    explicit Sucesor( std::string termino )
            : _termino ( termino ),
              _numOcurrencias ( 1 )
    {};

    Sucesor( const Sucesor &orig )
            : _termino ( orig._termino ),
              _numOcurrencias ( orig._numOcurrencias )
    {};
    virtual ~Sucesor() = default;

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


private:
    std::string _termino;
    int _numOcurrencias;
};

#endif /* SUCESOR_H */
