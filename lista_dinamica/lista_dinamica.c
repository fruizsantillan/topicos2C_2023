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
