//
//  main.cpp
//  ImgQuad
//
//  Created by Antonio Jesús Rueda Ruiz on 09/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "MallaRegular.h"
#include "CodigoPost.h"


using namespace std;

int main(int argc, const char * argv[]) {
    vector<CodigoPost> codigosPostales;
    ifstream archivo;
    archivo.open("/home/aabedraba/Github/EstructurasDeDatos/Practica_8/zipcode.csv");
    if ( !archivo.good() ){
        cout << "te follen" << endl;
        return 1;
    }

    string linea;
    MallaRegular<CodigoPost> malla(-7.20997, -176.637, 71.2995, -64.7347, 100);
    getline(archivo, linea);
    int i = 0;
    while( !archivo.eof() ) {
        int tamanioLinea;
        string palabra;
        getline(archivo, linea);

        //codigoPostal
        tamanioLinea = linea.find(",", 0);
        if ( tamanioLinea == -1 ) continue;
        palabra = linea.substr(1, tamanioLinea - 2);
        int codigoPostal = stoi(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //ciudad
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        std::string ciudad = palabra;
        linea = linea.substr(tamanioLinea+1, 255);

        //estado
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        std::string estado = palabra;
        linea = linea.substr(tamanioLinea+1, 255);

        //latitud
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        float latitud = stof(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //longitud
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        float longitud = stof(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //zonaHoraria
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        short zonaHoraria = stoi(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //dst
        tamanioLinea = linea.find("\"", 0);
        palabra = linea.substr( 1, tamanioLinea-1);
        short dst = stoi(palabra);

        CodigoPost city( codigoPostal, ciudad, estado, latitud, longitud, zonaHoraria, dst );
        malla.insertar(longitud, latitud, city);
    }



    cout << "Prueba" << endl;
    return 0;
}


//float minimoLongitud, maximoLongitud;
//maximoLongitud = minimoLongitud = codigosPostales[0].x;
//float minimoLatitud, maximoLatitud;
//minimoLatitud = maximoLatitud = codigosPostales[0].y;
//for (int j = 1; j < codigosPostales.size(); ++j) {
//float latitud = codigosPostales[j].y;
//float longitud = codigosPostales[j].x;
//
//if ( latitud < minimoLatitud ) minimoLatitud = latitud;
//else if ( latitud > maximoLatitud ) maximoLatitud = latitud;
//
//if ( longitud < minimoLongitud ) minimoLongitud = longitud;
//else if ( longitud > maximoLongitud ) maximoLongitud = longitud;
//}
//
//cout << "Minimo latitud: " << minimoLatitud << ", maximo latitud: " << maximoLatitud << endl;
//cout << "Minimo longitud: " << minimoLongitud << ", maximo longitud: " << maximoLongitud << endl;

