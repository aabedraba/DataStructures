//
// Created by aabedraba on 14/12/17.
//

#include "CodigoPost.h"

CodigoPost::CodigoPost(int codPost, std::string ciudad, std::string estado, float latitud,
                       float longitud, short timeZone, short dst)
        : _codPost(codPost), _ciudad(ciudad),
          _estado(estado), y(latitud),
          x(longitud), _timeZone(timeZone),
          _dst(dst)
{}

CodigoPost& CodigoPost::operator=(const CodigoPost &orig) {
    if ( *this != orig ) {
        this->_codPost = orig._codPost;
        this->_ciudad = orig._ciudad;
        this->_estado = orig._estado;
        this->y = orig.y;
        this->x = orig.x;
        this->_timeZone = orig._timeZone;
        this->_dst = orig._dst;
    }
    return *this;
}
bool CodigoPost::operator==(const CodigoPost &orig) const {
    return _codPost == orig._codPost &&
           _ciudad == orig._ciudad &&
           _estado == orig._estado &&
           y == orig.y &&
           x == orig.x &&
           _timeZone == orig._timeZone &&
           _dst == orig._dst;
}

bool CodigoPost::operator!=(const CodigoPost &orig) const {
    return !(orig == *this);
}