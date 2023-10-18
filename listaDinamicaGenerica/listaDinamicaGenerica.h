#ifndef LISTADINAMICAGENERICA_H_INCLUDED
#define LISTADINAMICAGENERICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define TODO_OK 0
#define SIN_MEM 1
#define DUPLICADO 2

#define BURBUJEO 1
#define SELECCION 2
#define INSERCION 3

#define max(x,y) ((x) > (y) ? (x) : (y))

typedef struct {
    void* vec;
    int ce;
    size_t cap;
    size_t tamElem;
} Lista;

//Funciones como parametros
typedef int (*Cmp)(const void*, const void*);
typedef void (*Accion)(void*, void*);

//Genericas Lista
bool listaCrear(Lista* pl, size_t tamElem);
bool listaCrearRandom(Lista* pl, int ce);
void listaDestruir(Lista* pl);
void listaRecorrer(const Lista* pl, Accion accion, void* extra);
void listaVaciar(Lista* pl);

//Ordenar Lista Ascendente
void listaOrdenarAsc(Lista* pl, int metodo, Cmp cmp);
void listaOrdenarAscBurbujeo(Lista* pl, Cmp cmp);
void listaOrdenarAscSeleccion(Lista* pl, Cmp cmp);
void listaOrdenarAscInsercion(Lista* pl, Cmp cmp);

//Ordenar Lista Descendente
void listaOrdenarDesc(Lista* pl, int metodo, Cmp cmp);
void listaOrdenarDescBurbujeo(Lista* pl, Cmp cmp);
void listaOrdenarDescSeleccion(Lista* pl, Cmp cmp);
void listaOrdenarDescInsercion(Lista* pl, Cmp cmp);

//Insertar en Lista
int listaInsertarEnOrdAsc(Lista* pl, void* elem, Cmp cmp);
int listaInsertarAlInicio(Lista* pl, int elem);
int listaInsertarAlFinal(Lista* pl, const void* elem);
int listaInsertarEnPos(Lista* pl, int elem, int pos);

//Eliminar y buscar
bool listaEliminarOrd(Lista* pl, void* elem, Cmp cmp);
bool listaBuscar(const Lista* pl, int elem);

//Extras
void intercambiar(void* a, void* b, size_t tamElem);
void* buscarMenor(const void* ini, const void* fin, size_t tamElem, Cmp cmp);
void* buscarMayor(const void* ini, const void* fin, size_t tamElem, Cmp cmp);
#endif // LISTADINAMICAGENERICA_H_INCLUDED
