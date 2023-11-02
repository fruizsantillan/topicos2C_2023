#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "funciones_enunciado.h"
#include <math.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#include "funciones.h"
typedef char booleano;

/* aqu� deben declarar sus prototipos de funciones */
void solucionTP(t_juego* juegos);
char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje);

//Definimos los 3 minutos del juego en milisegundos.
#define CANT_MILISEG 180000

float calculaVelDesdePeriodo(const float periodo);
float calculaAlturaDesdeVelocidad(const float velocidad);
float calculaVelDesdeAltura(const float alturaMaxima);
float calculaTiempoDesdeVelocidad(const float velocidad);
float calculaPendiente(const t_coordenada* coordenada1, const t_coordenada* coordenada2);
void calculaCantAlineamientos(t_juego* juegos);
double milisegASeg(int miliseg);
double calculaAlturaDesdeTiempo(double velocidad, double tiempo);
#endif // FUNCIONES_H_INCLUDED
