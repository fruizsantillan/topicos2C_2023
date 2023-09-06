#include "funciones.h"

int main()
{
    /*

    TDA: Tipo de dato abstracto
    Ejemplo: Fecha

    ****************
    int dia;
    int mes;
    int anio;

    sumar_dias(); \
    restar_dias(); --> Funciones primitivas
    dif_fechas(); /
    ****************

    Si usamos dia relativo -> un solo entero para toda la fecha
    typedef int Fecha;

    *************************************************************

    TDA LISTA

    Lo definimos como vector.
    Tenemos que guardar la cantidad de elementos, ya que cuando eliminamos alguno deberemos modificarla.

    insertar();
        * en orden
        * en posicion
        * al inicio
        * al final
    eliminar();
        * por clave
        * de posicion
        * primero
        * ultimo
    buscar();
    ordenar();
    vaciar();
    crear();
    eliminarDuplicados();


    */

    Lista lista;
    crear_lista(&lista);

    return 0;
}
