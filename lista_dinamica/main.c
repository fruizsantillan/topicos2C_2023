#include "lista_dinamica.h"

int main()
{
    Lista l;
    listaCrearRandom(&l, 100, 1);

    time_t iniT = time(NULL);

    listaOrdenarAsc(&l, BURBUJEO);

    time_t finT = time(NULL);

    long result = finT - iniT;

    printf("Tiempo: %ld", result);

    destruirLista(&l);
    return 0;
}
