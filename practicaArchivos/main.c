#include "funciones.h"

int main()
{
    const char nomTxt[] = "empleados.txt";
    const char nomBin[] = "actSueldos.bin";
    //Actualizar sueldos en base al porcentaje definido en el archivo


    int retorno = crearArchivoTxtEmpleadosVariable(nomTxt);
    retorno = crearArchivoBinActSueldos(nomBin);
    retorno = leerArchivoBinActSueldos(nomBin);

    //pasar txt a bin
    archivoTxtABin(nomTxt, "empleados.bin", empleado)
    return retorno;
}
