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
#include "Sucesor.h"

class Palabra {
public:
    Palabra();
    explicit Palabra( std::string termino );
    Palabra(const Palabra& orig);
    virtual ~Palabra();

    Palabra &operator =( const Palabra &otro );   
    bool operator !=( const Palabra &otro ) const;
    bool operator ==( const Palabra &otro ) const;
    bool operator >( const Palabra &otro ) const; 
    bool operator <( const Palabra &otro ) const;
    
    void introducirSucesor( std::string sucesor );
    std::list<std::string> *sucesores( );
    unsigned long djb2( unsigned char *str );

private:
    std::string _termino;
    std::list<Sucesor> _siguiente;
};

#endif /* PALABRA_H */

