#include "funciones.h"

int main(int argc, char* argv[])
{
    char tipoTxt = argv[3][0];

    int retorno = crearArchivoTxtEmpleadosVariable(argv[2]);

//    archivoBinATxt(argv[1], argv[2], tipoTxt == 'V' ? empleadoBinATxtV : empleadoBinATxtF, sizeof(Empleado));
    retorno = archivoTxtABin(argv[2], argv[1], tipoTxt == 'V' ? empleadoTxtVABin : empleadoTxtFABin, sizeof(Empleado));

    leerArchivoBinarioEmpleados(argv[1]);
//    return 0;//Para Bin a Txt
    return retorno; //Para Txt a Bin, ya que puede haber campos corruptos en el archivo de texto
}
