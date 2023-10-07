#include "arrays.h"

void muestraArrayEnteros(int* vec, int ce) {
    while(ce != 0) {
        printf("| %d ", *vec);
        vec++;
        ce--;
    }
    printf("|\n");
}

void mueveElementosIzquierda(int* vec){
    while(*vec){
        *(vec) = *(vec + 1);
        vec++;
    }
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

void eliminaElemPosicion(int* vec, int ce, int pos) {
    int* aEliminar = vec + pos - 1;

    while(*aEliminar){
        *aEliminar = *(aEliminar + 1);
        aEliminar++;
    }
}

void eliminaPrimerAparicion(int* vec, int ce, int elem) {
    while(*vec && *vec != elem)
        vec++;

    while(*vec){
        *vec = *(vec + 1);
        vec++;
    }
}

void eliminaTodasApariciones(int * vec, int ce, int elem){
    while(*vec){
        if(*vec == elem){
            mueveElementosIzquierda(vec);
        }

        //Validamos si vienen dos elementos iguales seguidos a eliminar
        if(*vec == elem)
            vec--;

        vec++;
    }
}

bool esPalindromo(char* palabra){
    char* ini = palabra;

    while(*palabra)
        palabra++;

    char* fin = palabra - 1;

    while(tolower(*ini) == tolower(*fin) && ini != fin){
        ini++;
        fin--;
    }

    if(ini == fin)
        return true;
    else
        return false;


}
