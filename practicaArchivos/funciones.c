#include "funciones.h"

void empleado



int crearArchivoTxtEmpleadosVariable(const char* nombreTxt)
{
    FILE* archivoTxt = fopen(nombreTxt, "wt");

    if(!archivoTxt)
    {
        printf("ERROR. No se pudo crear el archivo de texto\n");
        return ERR_ARCH;
    }

    Empleado empleados[CANT_EMPLEADOS] = {
        {12345678, "Juan Perez", 'M', {1, 1, 2020}, 3500.50},
        {23456789, "Maria Gonzalez", 'F', {15, 3, 2019}, 2800.75},
        {34567890, "Carlos Rodriguez", 'M', {10, 5, 2021}, 2200.30},
        {45678901, "Laura Lopez", 'F', {5, 7, 2022}, 3900.40},
        {56789012, "Pedro Martinez", 'M', {20, 9, 2020}, 2700.60},
        {67890123, "Ana Sanchez", 'F', {8, 11, 2018}, 4600.80},
        {78901234, "Luis Fernandez", 'M', {25, 12, 2017}, 2400.45},
        {89012345, "Elena Torres", 'F', {10, 2, 2019}, 3000.25},
        {90123456, "David Ramirez", 'M', {5, 4, 2023}, 3100.70},
        {12345067, "Sofia Castro", 'F', {15, 6, 2022}, 2700.55}
    };

    for(int i = 0; i < CANT_EMPLEADOS; i++)
        fprintf(archivoTxt, "%d|%s|%c|%d/%d/%d|%.2f\n",
                empleados[i].dni,
                empleados[i].apyn,
                empleados[i].sexo,
                empleados[i].fechaIngreso.dia,
                empleados[i].fechaIngreso.mes,
                empleados[i].fechaIngreso.anio,
                empleados[i].sueldo);

    fclose(archivoTxt);

    return TODO_OK;
}

int crearArchivoBinActSueldos(const char* nombreBin)
{
    FILE* archBin = fopen(nombreBin, "wb");

    if(!archBin)
    {
        printf("ERROR. No se pudo crear el archivo binario\n");
        return ERR_ARCH;
    }

    ActSueldo actSueldos[CANT_ACTS] = {
        {56789012, 0.14},
        {23456789, 0.31},
        {78901234, 0.06},
        {55193414, 0.55},
        {12345678, 0.33}
    };

    fwrite(actSueldos, sizeof(ActSueldo), CANT_ACTS, archBin);

    fclose(archBin);

    return TODO_OK;
}

int leerArchivoBinActSueldos(const char* nombreBin)
{
    FILE* archBin = fopen(nombreBin, "rb");

    if(!archBin)
        return ERR_ARCH;

    ActSueldo actSueldo;

    fread(&actSueldo, sizeof(ActSueldo), 1, archBin);

    while(!feof(archBin))
    {
        printf("%d|%.2f\n", actSueldo.dni, actSueldo.porcentajeAumento);
        fread(&actSueldo, sizeof(ActSueldo), 1, archBin);
    }

    fclose(archBin);

    return TODO_OK;
}
