#include "arrays.h"

int main() {
//    int vec[TAM] = {3, 3, 3, 6, 3, 8};
//    int ce = 6;
//    int num = 3;
//    int pos = 3;
//    muestraArrayEnteros(vec, ce);
//    eliminaTodasApariciones(vec, ce, num);
//    muestraArrayEnteros(vec, ce - 4);

    char palabra[] = "peron";
    if(esPalindromo(palabra))
        printf("La palabra %s es un palindromo", palabra);
    else
        printf("La palabra %s no es un palindromo", palabra);
    return 0;
}
