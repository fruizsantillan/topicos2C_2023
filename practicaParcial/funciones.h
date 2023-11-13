#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIN_MEM 1
#define DUPLICADO 2
#define ERR_ARCHIVO 3
#define TODO_OK 0

#define CANT_PRODS 5
#define CANT_MOVS 8

//**************************************************************
//                          Estructuras
//**************************************************************
typedef struct
{
    void* vec;
    int ce;
    size_t cap;
    size_t tamElem;
}
Lista;

typedef struct
{
    char codigo[11];
    char descripcion[31];
    float precio;
    int stock;
}
Producto;

typedef struct
{
    char codigo[11];
    int cantidad;
    float precio;
}
Movimiento;

typedef struct
{
    char codigo[11];
    unsigned nroReg;
}
IndProd;

typedef int (*Cmp)(const void*, const void*);

//**************************************************************
//                  Funciones de lista
//**************************************************************
bool listaCrear(Lista* pl, size_t tamElem);
void listaDestruir(Lista* pl);
bool listaCrearDeArchivo(Lista* pl, const char* nomArchivo, size_t tamElem);
int listaInsertarEnOrdAsc(Lista* pl, void* elem, Cmp cmp);
bool listaGrabarEnArchivo(Lista* pl, const void* nomArchivo);

//**************************************************************
//                  Funciones de archivos
//**************************************************************
void generarProductos(const char* nomArchivo);
void generarMovimientos(const char* nomArchivo);
void generarIndice(const char* nomProds, const char* nomIdx);
int mostrarProductos(const char* nomProds);

//**************************************************************
//                  Funciones de comparacion
//**************************************************************
int cmpIndProd(const void* a, const void* b);

#endif // FUNCIONES_H_INCLUDED
