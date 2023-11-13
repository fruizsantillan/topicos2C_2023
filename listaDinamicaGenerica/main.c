#include "listaDinamicaGenerica.h"

int cmpInt(const void* a, const void* b);
void mostrarInt(void* a, void* b);

int main()
{
    Lista pl;
    listaCrear(&pl, sizeof(int));

    int elem = 10;
    listaInsertarAlFinal(&pl, &elem);
    elem = 3;
    listaInsertarAlFinal(&pl, &elem);
    elem = 6;
    listaInsertarAlFinal(&pl, &elem);
    elem = 1;
    listaInsertarAlFinal(&pl, &elem);
    elem = 17;
    listaInsertarAlFinal(&pl, &elem);
    elem = 9;
    listaInsertarAlFinal(&pl, &elem);
    elem = 12;
    listaInsertarAlFinal(&pl, &elem);

    puts("Lista original:");
    listaRecorrer(&pl, mostrarInt, NULL);

    puts("\n\nInserto al principio:");
    elem = 193;
    listaInsertarAlInicio(&pl, &elem);
    elem = 39;
    listaInsertarAlInicio(&pl, &elem);
    listaRecorrer(&pl, mostrarInt, NULL);

    puts("\n\nLista ordenada:");
    listaOrdenarAsc(&pl, SELECCION, cmpInt);
    listaRecorrer(&pl, mostrarInt, NULL);

    int aEliminar = 1;
    printf("\n\nLista sin el elemento %d:\n", aEliminar);
    listaEliminarOrd(&pl, &aEliminar, cmpInt);
    listaRecorrer(&pl, mostrarInt, NULL);

    int aInsertar = 11;
    printf("\n\nInserto en orden el numero %d:\n", aInsertar);
    listaInsertarEnOrdAsc(&pl, &aInsertar, cmpInt);
    listaRecorrer(&pl, mostrarInt, NULL);

    puts("\n\nLista vacia:");
    listaVaciar(&pl);
    listaRecorrer(&pl, mostrarInt, NULL);

    elem = 159;
    listaInsertarAlFinal(&pl, &elem);
    puts("\n\nInserto en la lista vacia:");
    listaRecorrer(&pl, mostrarInt, NULL);

    listaDestruir(&pl);
    return 0;
}

int cmpInt(const void* a, const void* b)
{
    int* aInt = (int*)a;
    int* bInt = (int*)b;

    return *aInt - *bInt;
}

void mostrarInt(void* a, void* b)
{
    int* elem = (int*)a;

    printf("%d ", *elem);
}
