#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_MEM 2
#define ERR_LINEA_LARGA 3

#define TAM_APYN 50
#define TAM_LINEA 1000

#define CANT_EMPLEADOS 10

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

typedef struct
{
    int dni;
    char apyn[TAM_APYN + 1];
    char sexo;
    Fecha fechaIngreso;
    float sueldo;
}
Empleado;

typedef int(*TxtADato)(char* linea, )

int crearArchivoTxtEmpleadosVariable(const char* nombreTxt);
int crearArchivoTxtEmpleadosFijo(const char* nombreTxt);

int archivoTxtALista(const char* nombreTxt, Lista* lista, TxtADato txtADato, size_t tamReg);

#endif // FUNCIONES_H_INCLUDED
