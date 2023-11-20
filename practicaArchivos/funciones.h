#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_MEM 2
#define ERR_LINEA_LARGA 3

#define TAM_APYN 50
#define TAM_LINEA 1000

#define CANT_EMPLEADOS 10
#define CANT_ACTS 5
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

typedef struct
{
    int dni;
    float porcentajeAumento;
}
ActSueldo;

typedef int(*TxtABin)(char* linea, void* registro, bool* errorFatal);

int archivoTxtABin(const char* nombreTxt, const char* nombreBin, TxtABin txtABin, size_t tamReg);

//Funciones para el ejercicio
int crearArchivoTxtEmpleadosVariable(const char* nombreTxt);
int crearArchivoBinActSueldos(const char* nombreBin);
int leerArchivoBinActSueldos(const char* nombreBin);
#endif // FUNCIONES_H_INCLUDED
