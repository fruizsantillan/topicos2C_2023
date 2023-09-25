#ifndef FUNCIONES_ENUNCIADO_H_INCLUDED
#include <string.h>
#include <stdio.h>
#define FUNCIONES_ENUNCIADO_H_INCLUDED
#define CANT_MAXIMA_ALINEAMIENTOS 1000
#define GRAVEDAD 9.8
#define CANT_JUEGOS 3
#define CANT_JUGADORES 3
#define TAM_NOMBRE 20
#define FOTOS_POR_SEGUNDO 1000
#define DELTA 0.01

typedef struct
{
    char nombre[TAM_NOMBRE];        // dato
    float estatura;                 // dato, en metros
    float alturaGolpe;              // calcular
    float golpesPorMinuto;          // calcular
    float alturaMaximaDeLaPelota;   // calcular
    float posicion;                 // dato (posición horizontal en el juego)
    float velocidadInicial;         // calcular
    float distanciaRecorrida;       // calcular
}t_jugador;

typedef struct
{
    float x;
    float y;
}t_coordenada;

typedef struct
{
    unsigned char minuto;
    unsigned char segundo;
    unsigned short milisegundo;
}t_instante;

typedef struct
{
    t_instante instanteInicial;
    float pendiente;
    unsigned int duracion;  // en milisegundos
    t_coordenada pos1, pos2, pos3;

}t_alineamiento;

typedef struct
{
    t_jugador jugadores[CANT_JUGADORES];
    int cantidadAlineamientos;
    t_alineamiento alineamientos[CANT_MAXIMA_ALINEAMIENTOS];
}t_juego;

void cargoDatosInicialesDelJugador(t_jugador*,const char*,float, float);
void mostrarDatosDelJuego (int, const t_juego*);
void mostrarDatosDelJugador (int, const t_jugador*);
void mostrarCantidadDeAlineamientos(int, const t_juego*);
void mostrarDetalleAlineamientos(int, const t_juego*);

#endif // FUNCIONES_ENUNCIADO_H_INCLUDED
