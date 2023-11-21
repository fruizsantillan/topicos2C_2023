/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Cadena/Cadena.h"

#define TDA_LISTA_IMPL_DINAMICA_VEC
#include "../TDALista/TDALista.h"

#include "../SolucionBibliotecaTopicos/SolucionBiblioteca.h"

#define NOMBRE_ARCH_LIBROS "Libros.dat"
#define NOMBRE_ARCH_LIBROS_INDICE "Libros.idx"
#define NOMBRE_ARCH_MOVIMIENTOS "Movimientos.txt"


/************************************************************************/
#define TAM_LINEA


bool listaCrear_ALU(Lista* pl, size_t tamElem);
int cargarListaMovimientosLibro_ALU(Lista* plistaMov, const char* nombreArchMov);
void txtAMovimiento_ALU(MovLibro* movimiento, char* linea);
int listaInsertarOrd_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int cmpCodLibroMov(const void* a, const void* b);
void actualizaCantLibro(void* actualizado, void* actualizador);

int actualizarArchivoLibros_ALU(const char* nombreArchivoLibros, const char* nombreArchivoLibrosIndice, Lista* plistaMov);
/************************************************************************/

int main()
{
	generarArchMovimientosLibro(NOMBRE_ARCH_MOVIMIENTOS);
	generarArchLibros(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE);

	mostrarLibros(NOMBRE_ARCH_LIBROS);

	Lista listaMov;
    listaCrear_ALU(&listaMov, sizeof(MovLibro));
	///listaCrear(&listaMov, sizeof(MovLibro));

	///Debe generar la lista de movimientos, consolidando los movimientos de los libros, a fin de que quede 1 sólo elemento en la lista por cada libro.
	///Aumentando o disminuyendo la cantidad según se trate de una devolución o un préstamo respectivamente.
	cargarListaMovimientosLibro_ALU(&listaMov, NOMBRE_ARCH_MOVIMIENTOS);
	///cargarListaMovimientosLibro(&listaMov, NOMBRE_ARCH_MOVIMIENTOS);


	///Para test
	puts("Lista movimientos");
	puts("Cod. Libro | Cant.");
	listaRecorrer(&listaMov, mostrarMovimientoLibro, NULL);

	puts("");

	///Debe actualizar el archivo binario de Libros, sumando o restando la cantidad.
	///La cantidad en el archivo no puede quedar negativa. Si eso sucede, se deberá descartar el movimiento y continuar con el siguiente.
	///Para acceder a cada registro, debe hacer uso del archivo índice, que tiene cada registro, el código del libro y su ubicación en el archivo(Nro de registro empezando por el 0).
	///Debe cargar el índice en memoria, para trabajar con él.
	actualizarArchivoLibros_ALU(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE, &listaMov);
	///actualizarArchivoLibros(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE, &listaMov);

	puts("");

	///Debe normalizar los nombres de los libros en el archivo.
	///Dejando sólo 1 espacio entre palabras, sin espacios ni caracteres antes de la primer palábra y después de la última.
	///Quedando la primer letra de cada palabra en mayúscula y el resto en minúscula.
	/// normalizarNombresLibros_ALU(NOMBRE_ARCH_LIBROS);
	normalizarNombresLibros(NOMBRE_ARCH_LIBROS);

	mostrarLibros(NOMBRE_ARCH_LIBROS);

	/// listaDestruir_ALU(&listaMov);
	listaDestruir(&listaMov);

    return 0;
}

bool listaCrear_ALU(Lista* pl, size_t tamElem)
{
    pl->vec = malloc(8 * tamElem);

    if(!pl->vec)
    {
        printf("ERROR. No se pudo reservar memoria\n");
        return false;
    }

    pl->ce = 0;
    pl->cap = 8;
    pl->tamElem = tamElem;

    return true;
}

int cargarListaMovimientosLibro_ALU(Lista* plistaMov, const char* nombreArchMov)
{
    FILE* archMov = fopen(nombreArchMov, "rt");

    if(!archMov)
    {
        printf("ERROR. No se pudo abrir el archivo de movimientos.\n");
        return ERR_ARCHIVO;
    }

    char* linea = malloc(plistaMov->tamElem);

    if(!linea)
    {
        printf("ERROR. No se pudo reservar memoria.\n");
        fclose(archMov);
        return SIN_MEM;
    }

    MovLibro movimiento;
    movimiento.cantidad = 0;

    while(fgets(linea, plistaMov->tamElem, archMov))
    {
        txtAMovimiento_ALU(&movimiento, linea);
        listaInsertarOrd(plistaMov, &movimiento, sizeof(MovLibro), cmpCodLibroMov, actualizaCantLibro);
    }

    return TODO_OK;
}

void txtAMovimiento_ALU(MovLibro* movimiento, char* linea)
{
    char* act = strchr(linea, '\n');
    char* tipoMov;

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%c", tipoMov);

    if(*tipoMov == 'D')
        movimiento->cantidad = 1;
    else
        movimiento->cantidad = -1;

    *act = '\0';
    act = strrchr(linea, '|');
    strncpy(movimiento->codigoSocio, act + 1, 11);
    movimiento->codigoSocio[11] = '\0';

    *act = '\0';
    strncpy(movimiento->codigoLibro, linea, 7);
    movimiento->codigoLibro[7] = '\0';

    return TODO_OK;
}

int cmpCodLibroMov(const void* a, const void* b)
{
    MovLibro* movA = (MovLibro*)a;
    MovLibro* movB = (MovLibro*)b;

    return strcmp(movA->codigoLibro, movB->codigoLibro);
}

void actualizaCantLibro(void* actualizado, void* actualizador)
{
    MovLibro* movLibroOrig = (MovLibro*)actualizado;
    const MovLibro* nuevoStock = (const MovLibro*)actualizador;

    movLibroOrig->cantidad += nuevoStock->cantidad;
}

int actualizarArchivoLibros_ALU(const char* nombreArchivoLibros, const char* nombreArchivoLibrosIndice, Lista* plistaMov)
{
    ///Cargar indice en lista
    Lista indiceLibros;
    listaCrearDeArchivo(&indiceLibros, nombreArchivoLibrosIndice, sizeof(IndLibro));

    ///Leer de la lista de movimientos.
    MovLibro temp;
    listaIteradorActual()
    ///Buscar en el indice para encontrar la posicion.
    ///Ir al registro encontrado y actualizar la cantidad.
    ///Se debe validar que la cantidad no sea negativa, sino se descarta.



}
