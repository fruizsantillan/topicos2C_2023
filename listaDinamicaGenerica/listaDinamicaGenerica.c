#include "listaDinamicaGenerica.h"

//Genericas Lista
bool listaCrear(Lista* pl, size_t tamElem)
{
    pl->vec = malloc(8 * tamElem);

    if(!pl->vec)
        return false;

    pl->ce = 0;
    pl->cap = 8;
    pl->tamElem = tamElem;

    return true;
}

bool listaCrearRandom(Lista* pl, int ce)
{
    if(!listaCrear(pl, sizeof(int)))
        return false;

    int randV;
    srand(time(NULL));

    for(int i = 0; i < ce; i++)
    {
        randV = rand();
        listaInsertarAlFinal(pl, &randV);
    }

    return true;
}

void listaDestruir(Lista* pl)
{
    free(pl->vec);
}

void listaRecorrer(const Lista* pl, Accion accion, void* extra)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;
    for(void* i = pl->vec; i <= ult; i += pl->tamElem)
    {
        accion(i, extra);

    }
}

void listaVaciar(Lista* pl);

//Ordenar Lista Ascendente
void listaOrdenarAsc(Lista* pl, int metodo, Cmp cmp)
{
    switch(metodo)
    {
        case BURBUJEO:
            listaOrdenarAscBurbujeo(pl, cmp);
            break;
        case SELECCION:
            listaOrdenarAscSeleccion(pl, cmp);
            break;
        case INSERCION:
          listaOrdenarAscInsercion(pl, cmp);
            break;
    }
}

void listaOrdenarAscBurbujeo(Lista* pl, Cmp cmp)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;

    for(void* i = pl->vec + pl->tamElem; i < ult; i += pl->tamElem)
    {
        for(void* j = pl->vec; j < ult; j += pl->tamElem)
        {
            if(cmp(j, j + pl->tamElem) > 0)
                intercambiar(j, j + pl->tamElem, pl->tamElem);
        }
    }
}

void listaOrdenarAscSeleccion(Lista* pl, Cmp cmp)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;
    void* m;

    for(void* i = pl->vec; i < ult; i += pl->tamElem)
    {
        m = buscarMenor(i, ult, pl->tamElem, cmp);
        intercambiar(i, m, pl->tamElem);
    }
}

void listaOrdenarAscInsercion(Lista* pl, Cmp cmp)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;


    for(void* i = pl->vec + pl->tamElem; i <= ult; i += pl->tamElem)
    {
        void* aInsertar = i;
        void* j = i - pl->tamElem;

        while(j >= pl->vec && cmp(j, aInsertar) > 0)
        {
            intercambiar(j, aInsertar, pl->tamElem);
            aInsertar = j;
            j -= pl->tamElem;
        }
    }
}

//Ordenar Lista Descendente
void listaOrdenarDesc(Lista* pl, int metodo, Cmp cmp)
{
    switch(metodo)
    {
        case BURBUJEO:
            listaOrdenarDescBurbujeo(pl, cmp);
            break;
        case SELECCION:
            listaOrdenarDescSeleccion(pl, cmp);
            break;
        case INSERCION:
            listaOrdenarDescInsercion(pl, cmp);
            break;
    }
}

void listaOrdenarDescBurbujeo(Lista* pl, Cmp cmp)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;

    for(void* i = pl->vec + pl->tamElem; i < ult; i += pl->tamElem)
    {
        for(void* j = pl->vec; j < ult; j += pl->tamElem)
        {
            if(cmp(j, j + pl->tamElem) < 0)
                intercambiar(j, j + pl->tamElem, pl->tamElem);
        }
    }
}

void listaOrdenarDescSeleccion(Lista* pl, Cmp cmp)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;
    void* m;

    for(void* i = pl->vec; i < ult; i += pl->tamElem)
    {
        m = buscarMayor(i, ult, pl->tamElem, cmp);
        intercambiar(i, m, pl->tamElem);
    }
}

void listaOrdenarDescInsercion(Lista* pl, Cmp cmp)
{
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;

    for(void* i = pl->vec + pl->tamElem; i <= ult; i += pl->tamElem)
    {
        void* aInsertar = i;
        void* j = i - pl->tamElem;

        while(j >= pl->vec && cmp(j, aInsertar) < 0)
        {
            intercambiar(j, aInsertar, pl->tamElem);
            aInsertar = j;
            j -= pl->tamElem;
        }
    }
}

//Insertar en Lista
int listaInsertarEnOrdAsc(Lista* pl, int elem)
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

    int* i = pl->vec;
    int* ult = pl-> vec + pl->ce - 1;

    while(i <= ult && elem > *i)
        i++;

    if(i <= ult && elem == *i)
        return DUPLICADO;

    for(int* j = ult; j >= i; j--)
        *(j + 1) = *j;

    *i = elem;

    pl->ce++;

    return TODO_OK;
}

int listaInsertarAlInicio(Lista* pl, int elem);

int listaInsertarAlFinal(Lista* pl, const void* elem)
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

int listaInsertarEnPos(Lista* pl, int elem, int pos);

//Eliminar y buscar
bool listaEliminarOrd(Lista* pl, void* elem, Cmp cmp)
{
    void* i = pl->vec;
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;

    while(cmp(i, ult) <= 0 && cmp(elem, i) > 0)
        i += pl->tamElem;

    if(cmp(i, ult) > 0 || cmp(elem, i) < 0)
        return false;

    for(void* j = i; j < ult; j += pl->tamElem)
        memcpy(j, j + pl->tamElem, pl->tamElem);

    pl->ce--;

    if(pl->ce * 3 >= pl->cap)
    {
        pl->cap = max(pl->cap / 2, 8);
        pl->vec = realloc(pl->vec, pl->cap);
    }

    return true;
}

bool listaBuscar(const Lista* pl, int elem);

//Extras
void intercambiar(void* a, void* b, size_t tamElem)
{
    //void* aTemp = malloc(tamElem);
    char aTemp[tamElem];
    memcpy(aTemp, a, tamElem);  //*aTemp = *a;
    memcpy(a, b, tamElem);      //*a = *b;
    memcpy(b, aTemp, tamElem);  //*b = *aTemp;
    //free(aTemp);
}

void* buscarMenor(const void* ini, const void* fin, size_t tamElem, Cmp cmp)
{
    const void* m = ini;

    for(const void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, m) < 0)
            m = j;
    }

    return (void*)m;
}

void* buscarMayor(const void* ini, const void* fin, size_t tamElem, Cmp cmp)
{
    const void* m = ini;

    for(const void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, m) > 0)
            m = j;
    }

    return (void*)m;
}
