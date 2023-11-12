#include "funciones.h"

void empleadoBinATxtV(const void* registro, FILE* archivoTxt)
{
    Empleado* empleado = (Empleado*) registro;
    fprintf(archivoTxt, "%d|%s|%c|%d/%d/%d|%.2f\n", empleado->dni, empleado->apyn, empleado->sexo, empleado->fechaIngreso.dia,
                                                    empleado->fechaIngreso.mes, empleado->fechaIngreso.anio, empleado->sueldo);
}

void empleadoBinATxtF(const void* registro, FILE* archivoTxt)
{
    Empleado* empleado = (Empleado*) registro;
    fprintf(archivoTxt, "%08d%-50s%c%02d%02d%04d%011.2f\n", empleado->dni, empleado->apyn, empleado->sexo, empleado->fechaIngreso.dia,
                                                    empleado->fechaIngreso.mes, empleado->fechaIngreso.anio, empleado->sueldo);
}

int archivoBinATxt(const char* nombreBin, const char* nombreTxt, BinATxt binATxt, size_t tamReg)
{
    FILE* archBin = fopen(nombreBin, "rb");

    if(!archBin)
    {
        printf("ERROR. No se pudo abrir el archivo binario.");
        return ERR_ARCH;
    }

    FILE* archTxt = fopen(nombreTxt, "wt");

    if(!archTxt)
    {
        printf("ERROR. No se pudo abrir el archivo de texto.");
        fclose(archBin);
        return ERR_ARCH;
    }

    void* reg = malloc(tamReg);

    if(!reg)
    {
        printf("ERROR. No hay memoria disponible");
        fclose(archBin);
        fclose(archTxt);
        return ERR_MEM;
    }

    //Leo del binario una cantidad de bytes determinados por el parametro tamReg
    fread(reg, tamReg, 1, archBin);
    while(!feof(archBin))
    {
        binATxt(reg, archTxt);
        fread(reg, tamReg, 1, archBin);
    }

    free(reg);
    fclose(archBin);
    fclose(archTxt);

    return 0;
}

/////////////////////////////////ARCHIVOS TXT A BINARIO////////////////////////////////////////////////////
int empleadoTxtVABin(char* linea, void* registro, bool* errorFatal)
{
    Empleado* empleado = (Empleado*)registro;
    char* act = strchr(linea, '\n');

    if(!act)
    {
        *errorFatal = true;
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%f", &empleado->sueldo);
    //Si se solicita, hacer la validacion sobre lo leido. Ej: si es < a un sueldo minimo.

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%d/%d/%d", &empleado->fechaIngreso.dia, &empleado->fechaIngreso.mes, &empleado->fechaIngreso.anio);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%c", &empleado->sexo);

    *act = '\0';
    act = strrchr(linea, '|');
    strncpy(empleado->apyn, act + 1, TAM_APYN);
    empleado->apyn[TAM_APYN] = '\0';

    *act = '\0';
    sscanf(linea, "%d", &empleado->dni);

    return TODO_OK;
}

int empleadoTxtFABin(char* linea, void* registro, bool* errorFatal)
{
    Empleado* empleado = (Empleado*)registro;
    char* act = strchr(linea, '\n');

    if(!act)
    {
        *errorFatal = true;
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act -= 11;
    sscanf(act, "%f", &empleado->sueldo);
    //Si se solicita, hacer la validacion sobre lo leido. Ej: si es < a un sueldo minimo.

    *act = '\0';
    act -= 8;
    sscanf(act, "%2d/%2d/%4d", &empleado->fechaIngreso.dia, &empleado->fechaIngreso.mes, &empleado->fechaIngreso.anio);

    *act = '\0';
    act--;
    empleado->sexo = *act;

    *act = '\0';
    act -= TAM_APYN;
    //Usar rtrim para sacar los espacios de la derecha
    strncpy(empleado->apyn, act, TAM_APYN);
    empleado->apyn[TAM_APYN] = '\0';

    *act = '\0';
    sscanf(linea, "%d", &empleado->dni);

    return TODO_OK;
}

int archivoTxtABin(const char* nombreTxt, const char* nombreBin, TxtABin txtABin, size_t tamReg)
{
    FILE* archTxt = fopen(nombreTxt, "rt");

    if(!archTxt)
    {
        printf("ERROR. No se pudo abrir el archivo de texto");
        return ERR_ARCH;
    }

    FILE* archBin = fopen(nombreBin, "wb");

    if(!archBin)
    {
        printf("ERROR. No se pudo abrir el archivo binario");
        fclose(archTxt);
        return ERR_ARCH;
    }

    void* reg = malloc(tamReg);

    if(!reg)
    {
        printf("ERROR. No se pudo crear la variable");
        fclose(archTxt);
        fclose(archBin);
        return ERR_MEM;
    }

    char linea[TAM_LINEA];
    bool errorFatal = false;
    int ret;
    fgets(linea, TAM_LINEA, archTxt);

    while(!feof(archTxt) && !errorFatal)
    {
        ret = txtABin(linea, reg, &errorFatal);

        if(ret == TODO_OK)
        {
            fwrite(reg, tamReg, 1, archBin);
        }

        fgets(linea, TAM_LINEA, archTxt);
    }

    free(reg);
    fclose(archTxt);
    fclose(archBin);

    return !errorFatal ? TODO_OK : ret;
}

//Prueba crear archivos
int crearArchivoBinEmpleados(const char* nombreBin)
{
    FILE* archivoBin = fopen(nombreBin, "wb");

    if(!archivoBin)
    {
        printf("ERROR. No se pudo crear el archivo de empleados");
        return ERR_ARCH;
    }

    Empleado empleados[CANT_EMPLEADOS] = {
        {12345678, "Juan Perez", 'M', {1, 1, 2020}, 2500.50},
        {23456789, "Maria Gonzalez", 'F', {15, 3, 2019}, 2800.75},
        {34567890, "Carlos Rodriguez", 'M', {10, 5, 2021}, 2200.30},
        {45678901, "Laura Lopez", 'F', {5, 7, 2022}, 2900.40},
        {56789012, "Pedro Martinez", 'M', {20, 9, 2020}, 2700.60},
        {67890123, "Ana Sanchez", 'F', {8, 11, 2018}, 2600.80},
        {78901234, "Luis Fernandez", 'M', {25, 12, 2017}, 2400.45},
        {89012345, "Elena Torres", 'F', {10, 2, 2019}, 3000.25},
        {90123456, "David Ramirez", 'M', {5, 4, 2023}, 3100.70},
        {12345067, "Sofia Castro", 'F', {15, 6, 2022}, 2700.55}
    };

    fwrite(empleados, sizeof(Empleado), CANT_EMPLEADOS, archivoBin);

    fclose(archivoBin);

    return TODO_OK;
}

int crearArchivoTxtEmpleadosVariable(const char* nombreTxt)
{
    FILE* archivoTxt = fopen(nombreTxt, "wt");


    if(!archivoTxt)
    {
        printf("ERROR. No se pudo crear el archivo de empleados");
        return ERR_ARCH;
    }

    Empleado empleados[CANT_EMPLEADOS] = {
        {12345678, "Juan Perez", 'M', {1, 1, 2020}, 2500.50},
        {23456789, "Maria Gonzalez", 'F', {15, 3, 2019}, 2800.75},
        {34567890, "Carlos Rodriguez", 'M', {10, 5, 2021}, 2200.30},
        {45678901, "Laura Lopez", 'F', {5, 7, 2022}, 2900.40},
        {56789012, "Pedro Martinez", 'M', {20, 9, 2020}, 2700.60},
        {67890123, "Ana Sanchez", 'F', {8, 11, 2018}, 2600.80},
        {78901234, "Luis Fernandez", 'M', {25, 12, 2017}, 2400.45},
        {89012345, "Elena Torres", 'F', {10, 2, 2019}, 3000.25},
        {90123456, "David Ramirez", 'M', {5, 4, 2023}, 3100.70},
        {12345067, "Sofia Castro", 'F', {15, 6, 2022}, 2700.55}
    };

    for (int i = 0; i < CANT_EMPLEADOS; i++) {
        fprintf(archivoTxt, "%d|%s|%c|%d/%d/%d|%.2f\n", empleados[i].dni, empleados[i].apyn, empleados[i].sexo, empleados[i].fechaIngreso.dia, empleados[i].fechaIngreso.mes, empleados[i].fechaIngreso.anio, empleados[i].sueldo);
    }

    fclose(archivoTxt);

    return TODO_OK;
}

int leerArchivoBinarioEmpleados(const char* nombreBin)
{
    FILE* archivoBin = fopen(nombreBin, "rb");

    if(!archivoBin)
    {
        printf("ERROR. No se pudo abrir el archivo empleados para lectura.");
        return ERR_ARCH;
    }

    Empleado empleado;

    fread(&empleado, sizeof(Empleado), 1, archivoBin);

    while(!feof(archivoBin))
    {
        printf("%d|%s|%c|%d/%d/%d|%.2f\n", empleado.dni, empleado.apyn, empleado.sexo, empleado.fechaIngreso.dia, empleado.fechaIngreso.mes, empleado.fechaIngreso.anio, empleado.sueldo);
        fread(&empleado, sizeof(Empleado), 1, archivoBin);
    }

    fclose(archivoBin);

    return TODO_OK;
}
