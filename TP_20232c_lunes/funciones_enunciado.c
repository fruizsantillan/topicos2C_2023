#include "funciones_enunciado.h"

/*

Apellido(s): Ruiz Santillan
Nombre(s): Facundo
DNI: 42.536.297

*/


void cargoDatosInicialesDelJugador(t_jugador* jugador, const char* nombre, float estatura, float posicion)
{
    strcpy(jugador->nombre, nombre);
    jugador->estatura = estatura;
    jugador->posicion = posicion;

    // los siguientes datos se deben calcular, quedan inicializados en cero
    jugador->alturaMaximaDeLaPelota = 0;
    jugador->velocidadInicial = 0;
    jugador->golpesPorMinuto = 0;
}

void mostrarDatosDelJugador (int i, const t_jugador* jugador)
{
    printf ("%d) %-15s %6.2fm %8.2fm %8.2fcm %7.2fm %7.2f m/s %10.2f %10.2fm\n"
            ,i
            ,jugador->nombre,
            jugador->estatura,
            jugador->posicion,
            jugador->alturaGolpe*100,
            jugador->alturaMaximaDeLaPelota,
            jugador->velocidadInicial,
            jugador->golpesPorMinuto,
            jugador->distanciaRecorrida);
}

void mostrarDatosDelJuego (int numeroJuego, const t_juego* juego)
{
    /* Esta función muestra los valores obtenidos en los puntos 1, 2, 3, 4 y 5 */
    printf ("************** Datos del juego %d **************\n", numeroJuego);
    printf ("   Nombre         Estatura  Posicion      Golpe   Altura   Velocidad     Golpes   Distancia\n");
    for (int i = 0 ; i< CANT_JUEGOS ; i++)
        mostrarDatosDelJugador(i+1, &(juego->jugadores[i]));
    printf ("\n");
}

void mostrarCantidadDeAlineamientos(int numeroJuego, const t_juego* juego)
{
    /* Esta función muestra los valores obtenidos en el punto 6, sin detalles */

    printf ("En el juego %d hubo %d alineamientos.\n\n" , numeroJuego,  juego->cantidadAlineamientos);
}


void mostrarDetalleAlineamientos(int numeroJuego, const t_juego* juego)
{
    /* Esta función muestra los valores obtenidos en el punto 6, con detalles */
    if (juego->cantidadAlineamientos == 0 )
    {
        printf ("No hay alineamientos para mostrar en el juego %d.\n",numeroJuego);
            return;
    }


    printf ("\nInformacion detallada de los alineamientos del juego %d:\n" , numeroJuego);

    printf ("Alineamiento Instante     Duracion     Pendiente      Coordenadas\n");
    for (int i = 0 ; i < juego->cantidadAlineamientos ; i++ )
    {
        printf ("%-12d %1d:%02d:%03d %10dms %13.3f      (%6.2f;%6.2f) (%6.2f;%6.2f) (%6.2f;%6.2f)\n",
                i+1,
                juego->alineamientos[i].instanteInicial.minuto,
                juego->alineamientos[i].instanteInicial.segundo,
                juego->alineamientos[i].instanteInicial.milisegundo,
                juego->alineamientos[i].duracion,
                juego->alineamientos[i].pendiente,
                juego->alineamientos[i].pos1.x, juego->alineamientos[i].pos1.y,
                juego->alineamientos[i].pos2.x, juego->alineamientos[i].pos2.y,
                juego->alineamientos[i].pos3.x, juego->alineamientos[i].pos3.y);
    }

}
