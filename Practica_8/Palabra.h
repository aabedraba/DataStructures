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
    Palabra( std::string termino ); 
    Palabra(const Palabra& orig) = default;
    virtual ~Palabra() = default;
    Palabra &operator =( const Palabra &otro );   
    bool operator !=( const Palabra &otro ) const;
    bool operator ==( const Palabra &otro ) const;
    bool operator >( const Palabra &otro ) const; 
    bool operator <( const Palabra &otro ) const;
    std::string getTermino() const;
    void introducirSucesor(const std::string sucesor);
    std::list<std::string> sucesores( );

private:
    std::string _termino;
    std::list<Sucesor> _siguiente;
};

#endif /* PALABRA_H */

