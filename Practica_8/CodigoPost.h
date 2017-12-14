//
// Created by aabedraba on 14/12/17.
//

#ifndef PRACTICA_8_CODIGOPOST_H
#define PRACTICA_8_CODIGOPOST_H

#include <string>

class CodigoPost {
public:
    CodigoPost(int codPost, std::string ciudad, std::string estado, float latitud, float longitud,
               short timeZone, short dst);
    CodigoPost( const CodigoPost& orig ) = default;
    virtual ~CodigoPost() = default;

    CodigoPost &operator=( const CodigoPost& orig );
    bool operator==(const CodigoPost &orig) const;
    bool operator!=(const CodigoPost &orig) const;
    bool operator<(const CodigoPost &rhs) const;
    bool operator>(const CodigoPost &rhs) const;
    bool operator<=(const CodigoPost &rhs) const;
    bool operator>=(const CodigoPost &rhs) const;

    int get_codPost() const;
    const std::string &get_ciudad() const;
    const std::string &get_estado() const;
    float get_latitud() const;
    float get_longitud() const;
    short get_timeZone() const;
    short get_dst() const;

private:
    int _codPost;
    std::string _ciudad;
    std::string _estado;
    float _latitud;
    float _longitud;
    short _timeZone;
    short _dst;
};


#endif //PRACTICA_8_CODIGOPOST_H
