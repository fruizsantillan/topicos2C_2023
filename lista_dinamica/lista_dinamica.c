#include "lista_dinamica.h"

bool crearLista(Lista* pl) {
    pl->vec = malloc(sizeof(int) * 8); //ver si es necesario castear

    if(!pl->vec)
        return false;

    pl->ce = 0;
    pl->capacidad = 8;

    return true;
}

void destruirLista(Lista* pl) {
    free(pl->vec);
}

int listaInsertarOrd(Lista* pl, int elem) {
    if(pl->ce == pl->capacidad) {
        int nCapacidad = pl->capacidad * 2;
        int* nVec = realloc(pl->vec, sizeof(int) * nCapacidad);
        if(!nVec)
            return SIN_MEM;
        pl->vec = nVec;
        pl->capacidad = nCapacidad;
    }

    int* ini = pl->vec;
    int* ult = pl->vec + pl->ce - 1;

    while(ini <= ult && elem > *ini)
        ini++;

    if(ini <= ult && elem == *ini)
        return DUPLICADO;

    for(int* j = ult; j >= ini; j--)
        *(j + 1) = *j;

    *ini = elem;
    pl->ce++;

    return TODO_OK;
}

int listaEliminarOrd(Lista* pl, int elem) {
    int* ini = pl->vec;
    int* ult = pl->vec + pl->ce - 1;

    while(ini <= ult && elem >= *ini)
        ini++;

    if(ini > ult || elem < *ini)
        return false;

    for(int* j = ini + 1; j <= ult; j++)
        *(j - 1) = *j;

    pl->ce--;

    if(pl->ce * 4 == pl->capacidad) {
        pl->capacidad /= 2;
        pl->vec = realloc(pl->vec, sizeof(int) * pl->capacidad);
    }

    return true;
}

void listaOrdenarAsc(Lista* pLista, int metodo){
    switch(metodo){
        case BURBUJEO:
            listaOrdenarAscBurbujeo(pLista);
            break;
        case SELECCION:
            listaOrdenarAscSeleccion(pLista);
            break;
        case INSERCION:
            listaOrdenarAscInsercion(pLista);
            break;
    }
}

void listaOrdenarAscBurbujeo(Lista* pLista){
    bool huboIntercambio = true;
    int i = 1;
    //for(int i = 1; i < pLista->ce; i++){
    while(huboIntercambio && i < pLista->ce){
        huboIntercambio = false;
        for(int j = 0; j < pLista->ce - i; j++){
            if(pLista->vec[j] > pLista->vec[j + 1]){
                intercambiar(pLista->vec + j, pLista->vec + j + 1);
                huboIntercambio = true;
            }
        }
        i++;
    }
}

void intercambiar(int* a, int* b){
    int aTemp = *a;
    *a = *b;
    *b = aTemp;
}

int listaInsertarAlFinal(Lista* pl, int elem){
    if(pl->ce == pl->capacidad) {
        int nCapacidad = pl->capacidad * 2;
        int* nVec = realloc(pl->vec, sizeof(int) * nCapacidad);
        if(!nVec)
            return SIN_MEM;
        pl->vec = nVec;
        pl->capacidad = nCapacidad;
    }

    pl->vec[pl->ce] = elem;
    pl->ce++;

    return TODO_OK;
}

void listaMostrar(Lista* pl){
    for(int i = 0; i < pl->ce; i++){
        printf("%d ", pl->vec[i]);
    }
    putchar('\n');
}

void listaOrdenarAscSeleccion(Lista* pl){
    int* ult = pl->vec + pl->ce - 1;
    int* menor;

    for(int* i = pl->vec; i < ult; i++){
        menor = buscarMenor(i, ult);

        if(menor != i)
            intercambiar(menor, i);
    }
}

int* buscarMenor(int* ini, int* fin){
    int* menor = ini;

    for(int* i = ini + 1; i <= fin; i++){
        if(*i < *menor)
            menor = i;
    }

    return menor;
}

void listaOrdenarAscInsercion(Lista* pl){
    int* ult = pl->vec + pl->ce - 1;
    int* j;
    int elemAInsertar;

    for(int* i = pl->vec + 1; i <= ult; i++){
        elemAInsertar = *i;
        j = i - 1;

        while(j >= pl->vec && elemAInsertar < *j){
            *(j + 1) = *j;
            j--;
        }

        *(j + 1) = elemAInsertar;
    }
}

bool listaCrearRandom(Lista* pl, int cantElem, int semilla){

    srand(semilla);

    for(int i = 1; i <= cantElem; i++)
        listaInsertarAlFinal(pl, rand());

    return true;
}
