#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.h"              // a completar
#include "funciones_enunciado.h"    // brindadas con el enunciado
int main()
{
    t_juego juegos[CANT_JUEGOS];
    char mostrarDetalles;

    cargoDatosInicialesDelJugador(&juegos[0].jugadores[0],"Messi"   ,   1.70,  1);
    cargoDatosInicialesDelJugador(&juegos[0].jugadores[1],"Di Maria",   1.78,  0.5);
    cargoDatosInicialesDelJugador(&juegos[0].jugadores[2],"Acuna"   ,   1.72,  0);

    cargoDatosInicialesDelJugador(&juegos[1].jugadores[0],"Messi"   ,   1.70,  1.6);
    cargoDatosInicialesDelJugador(&juegos[1].jugadores[1],"Di Maria",   1.78,  0.8);
    cargoDatosInicialesDelJugador(&juegos[1].jugadores[2],"Acuna"   ,   1.72,  0);

    cargoDatosInicialesDelJugador(&juegos[2].jugadores[0],"Messi"   ,   1.70,  3);
    cargoDatosInicialesDelJugador(&juegos[2].jugadores[1],"Di Maria",   1.78,   1);
    cargoDatosInicialesDelJugador(&juegos[2].jugadores[2],"Acuna"   ,   1.72,   0);

    // dentro de esta función debererían estar todo los llamados necesarios para resolver el TP (su desarrollo debe estar en funciones.c)
    solucionTP(juegos);

    // mostramos los resultados obtenidos
    for (int i = 0 ; i < CANT_JUEGOS ; i++)
    {
        mostrarDatosDelJuego(i+1, &juegos[i]);
        mostrarCantidadDeAlineamientos(i+1, &juegos[i]);
    }


    mostrarDetalles = obtenerValorPorTeclado("sn","Desea ver detalles extendidos sobre los alineamientos? (s/n):", "Opcion incorrecta, debe ingresar s/n." );
    if (mostrarDetalles == 's')
        for (int i = 0 ; i< CANT_JUEGOS ; i++)
            mostrarDetalleAlineamientos(i+1, &juegos[i]);

    return 0;
}
