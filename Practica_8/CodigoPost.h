//
// Created by aabedraba on 14/12/17.
//

#ifndef PRACTICA_8_CODIGOPOST_H
#define PRACTICA_8_CODIGOPOST_H

#include <string>

class CodigoPost {
public:
    CodigoPost(int codPost, std::string ciudad, std::string estado, float latitud, float longitud,
               char timeZone, bool dst);
    CodigoPost( const CodigoPost& orig ) = default;
    virtual ~CodigoPost() = default;

    CodigoPost &operator=( const CodigoPost& orig );
    bool operator==(const CodigoPost &orig) const;
    bool operator!=(const CodigoPost &orig) const;

private:
    int _codPost;
    std::string _ciudad;
    std::string _estado;
    float _latitud;
    float _longitud;
    char _timeZone;
    bool _dst;
};


#endif //PRACTICA_8_CODIGOPOST_H
