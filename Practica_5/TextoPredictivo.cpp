/* 
 * File:   TextoPredictivo.cpp
 * Author: aabedraba
 * 
 * Created on November 10, 2017, 4:59 PM
 */

#include "TextoPredictivo.h"

TextoPredictivo::TextoPredictivo( Diccionario &diccIdioma ) 
    : _diccIdioma ( diccIdioma )
{}

TextoPredictivo::TextoPredictivo( const TextoPredictivo& orig ) 
    : _diccIdioma ( _diccIdioma )
{}

TextoPredictivo::~TextoPredictivo()
{}

std::list<std::string> TextoPredictivo::sugerencia( const std::string& termino, std::list<int> &ocurrencias ) {
    return _diccIdioma.busca( termino ).sucesores( ocurrencias );
}

void TextoPredictivo::entrena( std::string& frase ) {
    _diccIdioma.entrena( frase );
}



