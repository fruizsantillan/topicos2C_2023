#include "arrays.h"

void muestraArrayEnteros(int* vec, int ce) {
    while(ce != 0) {
        printf("| %d ", *vec);
        vec++;
        ce--;
    }
    printf("|\n");
}

void arrayInsertaEnPosicion(int* vec, int ce, int num, int pos) {
    int* fin = vec + ce - 1;
    int* posInsercion = vec + pos - 1;

    while(fin >= posInsercion) {
        *(fin + 1) = *fin;
        fin--;
    }

    *posInsercion = num;
}

void arrayInsertaOrdenadoAsc(int* vec, int ce, int num) {
    int* fin = vec + ce - 1;

    while(fin >= vec && *fin > num) {
        *(fin + 1) = *fin;
        fin--;
    }

    *(fin + 1) = num;
} 

