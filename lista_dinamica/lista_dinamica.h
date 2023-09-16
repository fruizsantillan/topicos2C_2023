#ifndef LISTA_DINAMICA_H_INCLUDED
#define LISTA_DINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIN_MEM -1
#define DUPLICADO -2
#define TODO_OK 0

typedef struct {
    int* vec;
    int ce;
    size_t capacidad;
} Lista;

bool crearLista(Lista* pl);
void destruirLista(Lista* pl);
int listaInsertarOrd(Lista* pl, int elem);
int listaEliminarOrd(Lista* pl, int elem);

#endif // LISTA_DINAMICA_H_INCLUDED
