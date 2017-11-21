#include <iostream>

int fibonacci( int n ) {
    if ( n == 0 )
        return 0;
    if ( n == 1 )
        return 1;
    return fibonacci( n-1 ) + fibonacci( n-2 );
}

using namespace std;

int main(int argc, char** argv) {
    int n = 20;
    cout << fibonacci( n );

    return 0;
}

