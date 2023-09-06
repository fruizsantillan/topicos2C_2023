#include "funciones.h"

int insertar_ordenado(Lista * pLista, int elem) {

    if(pLista->ce == TAM)
        return SIN_MEM;

    int i = 0;

    while(i < pLista->ce && elem > pLista->vec[i])
        i++;    //Buscamos la posicion donde insertar.
                //Validamos no pasarnos de la CE para
                //comparar contra basura.

    //Cuando salgo del while en i tengo la posicion

    if(i < pLista->ce && elem == pLista->vec[i])
        return DUPLICADO;

    //Desplazamos para insertar
    for(int j = pLista->ce-1; j >= i; j--)
        pLista->vec[j+1] = pLista->vec[j];

    pLista->vec[i] = elem;
    pLista->ce++:

    return TODO_OK;

}
