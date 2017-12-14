//
//  main.cpp
//  ImgQuad
//
//  Created by Antonio Jesús Rueda Ruiz on 09/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MallaRegular.h"

using namespace std;

int main(int argc, const char * argv[]) {
    MallaRegular<int> mapa( 0, 0, 10, 10, 10 );
    int num = 5;
    mapa.insertar( 1, 2, num );
    mapa.buscar( 1, 2, num );


}

