/* 
 * File:   VectorEstatico.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:56 AM
 */

#ifndef VECTORESTATICO_H
#define VECTORESTATICO_H

#include "Palabra.h"

class VectorEstatico {
public:
    VectorEstatico();
    VectorEstatico(const VectorEstatico& orig);
    virtual ~VectorEstatico();
    
    void asigna ( const Palabra &palabra, unsigned int pos );
    Palabra* recupera ( unsigned int pos );
    int busquedaBin ( const Palabra &aBuscar );
    
    int getTAM() const;
    
private:
    Palabra *_palabras;
    int _TAM;
    
};

#endif /* VECTORESTATICO_H */

