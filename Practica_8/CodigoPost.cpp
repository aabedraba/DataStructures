//
// Created by aabedraba on 14/12/17.
//

#include "CodigoPost.h"

CodigoPost::CodigoPost(int codPost, std::string ciudad, std::string estado, float latitud,
                       float longitud, short timeZone, short dst)
        : _codPost(codPost), _ciudad(ciudad),
          _estado(estado), _latitud(latitud),
          _longitud(longitud), _timeZone(timeZone),
          _dst(dst)
{}

CodigoPost& CodigoPost::operator=(const CodigoPost &orig) {
    if ( *this != orig ) {
        this->_codPost = orig._codPost;
        this->_ciudad = orig._ciudad;
        this->_estado = orig._estado;
        this->_latitud = orig._latitud;
        this->_longitud = orig._longitud;
        this->_timeZone = orig._timeZone;
        this->_dst = orig._dst;
    }
    return *this;
}
bool CodigoPost::operator==(const CodigoPost &orig) const {
    return _codPost == orig._codPost &&
           _ciudad == orig._ciudad &&
           _estado == orig._estado &&
           _latitud == orig._latitud &&
           _longitud == orig._longitud &&
           _timeZone == orig._timeZone &&
           _dst == orig._dst;
}

bool CodigoPost::operator!=(const CodigoPost &orig) const {
    return !(orig == *this);
}

int CodigoPost::get_codPost() const {
    return _codPost;
}

const std::string &CodigoPost::get_ciudad() const {
    return _ciudad;
}

const std::string &CodigoPost::get_estado() const {
    return _estado;
}

float CodigoPost::get_latitud() const {
    return _latitud;
}

float CodigoPost::get_longitud() const {
    return _longitud;
}

short CodigoPost::get_timeZone() const {
    return _timeZone;
}

short CodigoPost::get_dst() const {
    return _dst;
}

bool CodigoPost::operator<(const CodigoPost &rhs) const {
    if (_latitud < rhs._latitud)
        return true;
    if (rhs._latitud < _latitud)
        return false;
    return _longitud < rhs._longitud;
}

bool CodigoPost::operator>(const CodigoPost &rhs) const {
    return rhs < *this;
}

bool CodigoPost::operator<=(const CodigoPost &rhs) const {
    return !(rhs < *this);
}

bool CodigoPost::operator>=(const CodigoPost &rhs) const {
    return !(*this < rhs);
}
