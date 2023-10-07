#include "TDAPalabra.h"

void normalizar(const char* cadANormalizar, char* cadNormalizada) {
    SecuenciaPal secLectura, secEscritura;

    crearSecuencia(&secLectura, (char*)cadANormalizar);
    crearSecuencia(&secEscritura, cadNormalizada);

    Palabra pal;

    leerPalabra(&secLectura, &pal);

    while(!finSecuencia(&secLectura)) {
        aTitulo(&pal);
        escribirPalabra(&secEscritura, &pal);
        escribirCaracter(&secEscritura, ' ');
        leerPalabra(&secLectura, &pal);
    }

    reposicionarCursor(&secEscritura, -1);
    cerrarSecuencia(&secEscritura);
}
