#ifndef LISTA_DINAMICA_H_INCLUDED
#define LISTA_DINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIN_MEM -1
#define DUPLICADO -2
#define TODO_OK 0

#define BURBUJEO 1
#define SELECCION 2
#define INSERCION 3

typedef struct {
    int* vec;
    int ce;
    size_t capacidad;
} Lista;

void intercambiar(int* a, int* b);

bool listaCrearRandom(Lista* pl, int cantElem, int semilla);
void listaMostrar(Lista* pl);
bool crearLista(Lista* pl);
void destruirLista(Lista* pl);
int listaInsertarOrd(Lista* pl, int elem);
int listaInsertarAlFinal(Lista* pl, int elem);
int listaEliminarOrd(Lista* pl, int elem);
void listaOrdenarAsc(Lista* pLista, int metodo);
void listaOrdenarAscBurbujeo(Lista* pLista);
void listaOrdenarAscSeleccion(Lista* pl);
int* buscarMenor(int* ini, int* fin);
void listaOrdenarAscInsercion(Lista* pl);
#endif // LISTA_DINAMICA_H_INCLUDED
