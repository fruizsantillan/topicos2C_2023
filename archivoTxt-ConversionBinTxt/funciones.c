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
    empleado->sexo = *(act + 1);

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
