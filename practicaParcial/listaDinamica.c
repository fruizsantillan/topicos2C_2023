#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(x,y) ((x) > (y) ? (x) : (y))

typedef struct 
{
    void* vec;
    int ce;
    size_t cap;
    size_t tamElem;
}
Lista;

typedef int(*Cmp)(const void*, const void*);
typedef void(*Accion)(void*, void*);

int listaCrear(Lista* pl, size_t tamElem)
{
    pl->vec = malloc(8 * tamElem);

    if(!pl->vec)
        return SIN_MEM;

    pl->ce = 0;
    pl->cap = 8;
    pl->tamElem = tamElem;

    return TODO_OK;
}

void listaDestruir(Lista* pl)
{
    free(pl->vec);
}

void listaVaciar(Lista* pl)
{
    pl->ce = 0;
}

int listaInsertarAlFinal(Lista* pl, void* elem)
{
    if(pl->ce == pl->cap)
    {
        size_t nuevaCap = pl->cap * 2;
        void* nuevoVec = realloc(pl->vec, nuevaCap * pl->tamElem);

        if(!nuevoVec)
            return SIN_MEM;

        pl->vec = nuevoVec;
        pl->cap = nuevaCap;
    }

    memcpy(pl->vec + pl->ce * pl->tamElem, elem, pl->tamElem);
    pl->ce++;

    return TODO_OK;
}

int listaInsertarAlInicio(Lista* pl, void* elem)
{
    if(pl->ce == pl->cap)
    {
        size_t nuevaCap = pl->cap * 2;
        void* nuevoVec = realloc(pl->vec, nuevaCap * pl->tamElem);

        if(!nuevoVec)
            return SIN_MEM;

        pl->vec = nuevoVec;
        pl->cap = nuevaCap;
    }

    for(void* i = pl->vec + pl->ce * pl->tamElem; i > pl->vec, i -= pl->tamElem)
        memcpy(i, i - pl->tamElem, pl->tamElem);

    memcpy(pl->vec, elem, pl->tamElem);
    pl->ce++;

    return TODO_OK;
}

int listaInsertarOrdAsc(Lista* pl, void* elem, Cmp cmp)
{
    if(pl->ce == pl->cap)
    {
        size_t nuevaCap = pl->cap * 2;
        void* nuevoVec = realloc(pl->vec, nuevaCap * pl->tamElem);

        if(!nuevoVec)
            return SIN_MEM;

        pl->vec = nuevoVec;
        pl->cap = nuevaCap;
    }

    void* i = pl->vec;
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;

    //Encontrar la posicion a insertar
    while(i <= ult && cmp(i, elem) < 0)
        i += pl->tamElem;
    //Verificar si está duplicado
    if(cmp(i, ult) <= 0 && cmp(i, elem) == 0)
        return DUPLICADO;
    //Desplazar para poder insertar
    for(void* j = ult; j >= i; j -= pl->tamElem)
        memcpy(j + pl->tamElem, j, pl->tamElem);
    //Insertar
    memcpy(i, elem, pl->tamElem);

    //Aumentar cant
    pl->ce++;
    return TODO_OK;
}