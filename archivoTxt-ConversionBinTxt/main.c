#include "funciones.h"

int main(int argc, char* argv[])
{
    int retorno;
    char tipoTxt = argv[3][0];

    archivoBinATxt(argv[1], argv[2], tipoTxt == 'V' ? empleadoBinATxtV : empleadoBinATxtF, sizeof(Empleado));
    retorno = archivoTxtABin(argv[1], argv[2], tipoTxt == 'V' ? empleadoTxtVABin : empleadoTxtFABin, sizeof(Empleado));

    return 0;//Para Bin a Txt
    return retorno; //Para Txt a Bin, ya que puede haber campos corruptos en el archivo de texto
}
