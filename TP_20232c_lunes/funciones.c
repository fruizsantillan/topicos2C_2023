#include "funciones.h"

/* aquí deben declarar sus funciones */
float calculaVelDesdePeriodo(const float periodo)
{
    return GRAVEDAD * (periodo / 2);
}

float calculaAlturaDesdeVelocidad(const float velocidad)
{
    return (pow(velocidad, 2)) / (2 * GRAVEDAD);
}

float calculaVelDesdeAltura(const float alturaMaxima)
{
    return sqrt(2 * alturaMaxima * GRAVEDAD);
}

float calculaTiempoDesdeVelocidad(const float velocidad)
{
    return velocidad / GRAVEDAD;
}

float calculaPendiente(const t_coordenada* coordenada1, const t_coordenada* coordenada2)
{
    return (coordenada2->y - coordenada1->y)/(coordenada2->x - coordenada1->x);
}

double milisegASeg(double miliseg)
{
    return miliseg / 1000.0;
}

double milisegAMin(double miliseg)
{
    return miliseg / 60000.0;
}

float calculaAlturaEnFuncionTiempo(const float tiempo, const float velocidad, const float alturaMaximaDeLaPelota, const float alturaGolpe)
{
    float alturaCalculada = velocidad * tiempo + ((1/2.0) * GRAVEDAD * pow(tiempo, 2));
    int subiendo = 1;

    if(alturaCalculada > alturaMaximaDeLaPelota)
    {
        alturaCalculada = alturaMaximaDeLaPelota - (alturaCalculada - alturaMaximaDeLaPelota);
        subiendo = 0;
        if(alturaCalculada == 0)
        {
            alturaCalculada = alturaGolpe;
        }
    } else if (alturaCalculada < alturaGolpe) {
        alturaCalculada = alturaGolpe + (alturaGolpe - alturaCalculada);
        subiendo = 1;
    }

    return alturaCalculada;
}

float calcularDistanciaRecorrida(float duracionJuegoEnMinutos, float velocidadInicial, float alturaMaximaDeLaPelota, float periodo)
{
    return ((duracionJuegoEnMinutos * 60) * alturaMaximaDeLaPelota) / periodo;
}

int calculaCantAlineamientos(t_juego* juegos)
{
    t_coordenada coordenadas[CANT_JUGADORES];
    int duracionAlineamiento = 0;
    t_instante instanteAlineamiento;
    int subiendo = 1;
    int cantAlineamientos = 0;

    for(int i = 0; i < CANT_JUGADORES; i++)
        coordenadas[i].x = juegos->jugadores[i].posicion;

    for(int j = 1; j < CANT_MILISEG; j++)
    {
        for(int k = 0; k < CANT_JUGADORES; k++)
        {
            double alturaCalculada = calculaAlturaEnFuncionTiempo(milisegASeg(j), juegos->jugadores[k].velocidadInicial,
                                                           juegos->jugadores[k].alturaMaximaDeLaPelota,
                                                           juegos->jugadores[k].alturaGolpe);

            if (alturaCalculada >= juegos->jugadores[k].alturaMaximaDeLaPelota) {
                subiendo = 0;
            } else if (alturaCalculada <= juegos->jugadores[k].alturaGolpe) {
                subiendo = 1;
            }

            if (subiendo) {
                // La pelota sube por lo tanto la altura no necesita ajustes.
            } else {
                alturaCalculada = juegos->jugadores[k].alturaMaximaDeLaPelota - (alturaCalculada - juegos->jugadores[k].alturaMaximaDeLaPelota);
            }
        }

        float pendienteAB = fabs(calculaPendiente(&coordenadas[0], &coordenadas[1]));
        float pendienteBC = fabs(calculaPendiente(&coordenadas[1], &coordenadas[2]));

        if (fabs(pendienteAB - pendienteBC) < DELTA && duracionAlineamiento == 0)
        {
            instanteAlineamiento.milisegundo = j;
            instanteAlineamiento.segundo = milisegASeg(j);
            instanteAlineamiento.minuto = milisegAMin(j);

            juegos->alineamientos[cantAlineamientos].duracion = 0;
            juegos->alineamientos[cantAlineamientos].instanteInicial = instanteAlineamiento;
            juegos->alineamientos[cantAlineamientos].pendiente = fabs(pendienteAB - pendienteBC);
            juegos->alineamientos[cantAlineamientos].pos1 = coordenadas[0];
            juegos->alineamientos[cantAlineamientos].pos2 = coordenadas[1];
            juegos->alineamientos[cantAlineamientos].pos3 = coordenadas[2];

            cantAlineamientos++;
            duracionAlineamiento = 1;
        }
        else if (fabs(pendienteAB - pendienteBC) < DELTA)
            duracionAlineamiento++;
        else
            duracionAlineamiento = 0;
    }
    juegos->cantidadAlineamientos = cantAlineamientos;
}

char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{
    /* Aquí deben hacer todas las validaciones necesarias para que el reporte extendido se muestre a pedido del usuario */
    char teclaIngresada;

    printf(primerMensaje);
    scanf("%c", &teclaIngresada);

    while(teclaIngresada != opcionesValidas[0] && teclaIngresada != opcionesValidas[1])
    {
        printf(segundoMensaje);
        scanf("%c", &teclaIngresada);
    }

    return teclaIngresada;
}

void calcularDatosJugador(t_jugador *jugador, int juegoIndex, int jugadorIndex)
{
    //Datos brindados por el enunciado.
    const float duracionJuegoEnMinutos = 3.0;
    const float periodosMessiSegundos[CANT_JUEGOS] = {1.5, 3.0, 5.0};
    const float alturaTotalAcunaMetros[CANT_JUEGOS] = {3.0, 11.11, 14.14};
    const int frecuenciasDiMariaMinuto[CANT_JUEGOS] = {10, 15, 30};

    switch (jugadorIndex)
    {
        case 0: // Messi
            jugador->velocidadInicial = calculaVelDesdePeriodo(periodosMessiSegundos[juegoIndex]);
            float alturaTempMessi = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
            jugador->alturaGolpe = (alturaTempMessi > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->alturaMaximaDeLaPelota = alturaTempMessi + jugador->alturaGolpe;
            jugador->golpesPorMinuto = (duracionJuegoEnMinutos * 60) / periodosMessiSegundos[juegoIndex];
            jugador->distanciaRecorrida = ((duracionJuegoEnMinutos * 60) * jugador->alturaMaximaDeLaPelota) / periodosMessiSegundos[juegoIndex];
            break;
        case 1: // DiMaria
            jugador->golpesPorMinuto = frecuenciasDiMariaMinuto[juegoIndex];
            jugador->velocidadInicial = calculaVelDesdePeriodo(60.0 / jugador->golpesPorMinuto);
            float alturaTempDiMaria = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
            jugador->alturaGolpe = (alturaTempDiMaria > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->alturaMaximaDeLaPelota = alturaTempDiMaria + jugador->alturaGolpe;
            jugador->distanciaRecorrida = ((duracionJuegoEnMinutos * 60) * jugador->alturaMaximaDeLaPelota) / (60.0 / jugador->golpesPorMinuto);
            break;
        case 2: // Acuna
            jugador->alturaMaximaDeLaPelota = alturaTotalAcunaMetros[juegoIndex];
            jugador->velocidadInicial = calculaVelDesdeAltura(jugador->alturaMaximaDeLaPelota);
            jugador->alturaGolpe = (jugador->alturaMaximaDeLaPelota > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->golpesPorMinuto = (duracionJuegoEnMinutos * 60) / (calculaTiempoDesdeVelocidad(jugador->velocidadInicial) * 2);
            jugador->distanciaRecorrida = ((duracionJuegoEnMinutos * 60) * jugador->alturaMaximaDeLaPelota) / (calculaTiempoDesdeVelocidad(jugador->velocidadInicial) * 2);
            break;
    }
}

void solucionTP(t_juego* juegos)
{
    for (int i = 0; i < CANT_JUEGOS; i++)
    {
        for (int j = 0; j < CANT_JUGADORES; j++)
        {
            calcularDatosJugador(&(juegos + i)->jugadores[j], i, j);
        }
        calculaCantAlineamientos(juegos + i);
    }
  /* Aquí deben estar los llamados a las funciones creadas por ustedes */
}
