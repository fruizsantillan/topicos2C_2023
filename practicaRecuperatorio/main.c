#include "funciones.h"

int main()
{
    const char nomArchEmpleadosVar[] = "empleadosVar.txt";
    const char nomArchEmpleadosFijo[] = "empleadosFijo.txt";

    crearArchivoTxtEmpleadosVariable(nomArchEmpleadosVar);
    crearArchivoTxtEmpleadosFijo(nomArchEmpleadosFijo);


    parsearArchivoTxtVariable(nomArchEmpleadosVar);
    parsearArchivoTxtFijo(nomArchEmpleadosFijo);

    return 0;
}
