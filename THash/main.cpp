#include <iostream>
#include "THashCerrada.h"

using namespace std;

int main() {
    long tam = 5;
    THashCerrada<int> numeros( tam );
    numeros.insertar(1, 1);
    numeros.insertar(1, 2);
    if (numeros.buscar(1, 2) == nullptr ) cout << "gilipollas!" << endl;
    else cout << *numeros.buscar(1, 2)  << endl;

    return 0;
}