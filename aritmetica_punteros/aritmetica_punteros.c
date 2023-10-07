#include "aritmetica_punteros.h"

int insertar_ordenado(Lista * pLista, int elem) {

    if(pLista->ce == TAM)
        return SIN_MEM;

    int* ult = pLista->vec + pLista->ce - 1;
    int* i = pLista->vec;

    while(i <= ult && elem > *i)
        i++;    //Buscamos la posicion donde insertar.
                //Validamos no pasarnos de la direccion
                //del ultimo elem para comparar contra basura

    //Cuando salgo del while en i tengo la direccion donde insertar

    if(i <= ult && elem == *i)
        return DUPLICADO;

    //Desplazamos para insertar
    for(int* j = ult; j >= i; j--)
        *(j+1) = *j;

    *i = elem;
    pLista->ce++;

    return TODO_OK;

}

bool eliminar_lista_ordenado(Lista* pLista, int elem) {
    if(pLista->ce == 0)
        return false;

    int* i = pLista->vec;
    int* ult = pLista->vec + pLista->ce-1;

    while(i <= ult && elem > *i)
        i++;

    if(i > ult || elem < *i)
        return false;

    for(int* j = i + 1; j <= ult; j++)
        *(j - 1) = *j;

    pLista->ce--;

    return true;
}
