#include "funciones.h"

/* aquï¿½ deben declarar sus funciones */
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

double milisegASeg(int miliseg)
{
    miliseg  %= (60 * 1000);
    return miliseg / 1000;
}

double milisegAMin(double miliseg)
{
    return miliseg / (60 * 1000);
}

float calcularDistanciaRecorrida(float duracionJuegoEnMinutos, float velocidadInicial, float alturaMaximaDeLaPelota, float periodo)
{
    return ((duracionJuegoEnMinutos * 60) * alturaMaximaDeLaPelota) / periodo;
}

double calculaAlturaDesdeTiempo(double velocidad, double tiempo)
{
    return velocidad * tiempo + 0.5 * GRAVEDAD * pow(tiempo, 2);
}

float calculaPosicionAlineamiento(float* trayectoriaPelota, float* tiempoAAlturaMaxima, float* tiempoTemp, float* velocidadInicial, float* alturaGolpe)
{
    if(*trayectoriaPelota)
    {
        if(*tiempoTemp >= *tiempoAAlturaMaxima)
        {
            *trayectoriaPelota = FALSE;
            *tiempoTemp = *tiempoAAlturaMaxima;
        }
    } else
    {
        if(*tiempoTemp <= 0)
        {
            *trayectoriaPelota = TRUE;
            *tiempoTemp = 0;
        }
    }

    if(*trayectoriaPelota)
        *tiempoTemp += 0.001;
    else
        *tiempoTemp -= 0.001;

    return (calculaAlturaDesdeTiempo(*velocidadInicial, *tiempoTemp) + *(alturaGolpe));
}

void calculaCantAlineamientos(t_juego* juegos)
{
    bool trayectoriaPelota[CANT_JUGADORES]; //TRUE -> Subiendo : FALSE -> Bajando
    bool flagAlineacion = FALSE;
    t_coordenada coordenadas[CANT_JUGADORES];
    float tiempoAAlturaMaxima[CANT_JUGADORES];
    float tiempoTemp[CANT_JUGADORES];

    for(int i = 0; i < CANT_JUGADORES; i++)
    {
        coordenadas[i].x = juegos->jugadores[i].posicion;
        coordenadas[i].y = juegos->jugadores[i].alturaGolpe;
        trayectoriaPelota[i] = TRUE;
        tiempoAAlturaMaxima[i] = calculaTiempoDesdeVelocidad(juegos->jugadores[i].velocidadInicial);
        tiempoTemp[i] = 0;
    }

    bool esAlineamiento = FALSE;
    juegos->cantidadAlineamientos = 0;
    juegos->alineamientos->duracion = 0;

    for(int j = 1; j < CANT_MILISEG; j++)
    {
        for(int k = 0; k < CANT_JUGADORES; k++)
        {
            coordenadas[k].y = calculaPosicionAlineamiento(&trayectoriaPelota[k], &tiempoAAlturaMaxima[k], &tiempoTemp[k], &juegos->jugadores[k].velocidadInicial, &juegos->jugadores[k].alturaGolpe);
        }

        float pendienteAB = fabs(calculaPendiente(&coordenadas[0], &coordenadas[1]));
        float pendienteBC = fabs(calculaPendiente(&coordenadas[1], &coordenadas[2]));

        if(pendienteAB - pendienteBC < DELTA)
            esAlineamiento = TRUE;
        else
            esAlineamiento = FALSE;

        if(esAlineamiento && !flagAlineacion)
        {
            flagAlineacion = TRUE;
            juegos->alineamientos->duracion++;

            juegos->alineamientos->instanteInicial.minuto= milisegAMin(j);
            juegos->alineamientos->instanteInicial.segundo = milisegASeg(j);
            juegos->alineamientos->instanteInicial.milisegundo = j % 1000;

            for(int l = 0; l < CANT_JUGADORES; l++)
            {
                juegos->alineamientos[juegos->cantidadAlineamientos].pos1.x = coordenadas[l].x;
                juegos->alineamientos[juegos->cantidadAlineamientos].pos1.x = coordenadas[l].y;
            }
            juegos->alineamientos[juegos->cantidadAlineamientos].pendiente = (pendienteAB + pendienteBC) / 2;
        }

        if(flagAlineacion && !esAlineamiento)
        {
            juegos->alineamientos[juegos->cantidadAlineamientos].duracion = juegos->alineamientos->duracion;
            juegos->alineamientos->duracion = 0;
            juegos->cantidadAlineamientos++;
            flagAlineacion = FALSE;
        }

        if(flagAlineacion && esAlineamiento)
        {
            juegos->alineamientos->duracion++;
        }
    }

}

char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{
    /* Aquï¿½ deben hacer todas las validaciones necesarias para que el reporte extendido se muestre a pedido del usuario */
    char teclaIngresada='n';

    printf("%s\n",primerMensaje);
    scanf("%s", &teclaIngresada);

    char* esLetraValida = strstr(opcionesValidas, &teclaIngresada);

    while(!esLetraValida)
    {
        printf("%s\n", segundoMensaje);
        printf("%s\n", primerMensaje);
        scanf("%s", &teclaIngresada);
        esLetraValida = strstr(opcionesValidas, &teclaIngresada);
    }

    return teclaIngresada;
}

void calcularDatosJugador(t_jugador *jugador, int juegoIndex, int jugadorIndex)
{
    //Datos brindados por el enunciado.
    const float periodosMessiSegundos[CANT_JUEGOS] = {1.5, 3.0, 5.0};
    const float alturaTotalAcunaMetros[CANT_JUEGOS] = {3.0, 11.11, 14.14};
    const float frecuenciasDiMariaMinuto[CANT_JUEGOS] = {10.0, 15.0, 30.0};

    switch (jugadorIndex)
    {
        case 0: // Messi
            jugador->velocidadInicial = calculaVelDesdePeriodo(periodosMessiSegundos[juegoIndex]);
            float alturaTempMessi = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
            jugador->alturaGolpe = (alturaTempMessi > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->alturaMaximaDeLaPelota = alturaTempMessi + jugador->alturaGolpe;
            jugador->golpesPorMinuto = 60 / periodosMessiSegundos[juegoIndex];
            jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
            break;
        case 1: // DiMaria
            jugador->golpesPorMinuto = frecuenciasDiMariaMinuto[juegoIndex];
            jugador->velocidadInicial = calculaVelDesdePeriodo(60.0 / jugador->golpesPorMinuto);
            float alturaTempDiMaria = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
            jugador->alturaGolpe = (alturaTempDiMaria > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->alturaMaximaDeLaPelota = alturaTempDiMaria + jugador->alturaGolpe;
            jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
            break;
        case 2: // Acuna
            jugador->alturaMaximaDeLaPelota = alturaTotalAcunaMetros[juegoIndex];
            jugador->velocidadInicial = calculaVelDesdeAltura(jugador->alturaMaximaDeLaPelota  - jugador->estatura * 0.15);
            jugador->alturaGolpe = (jugador->alturaMaximaDeLaPelota > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->golpesPorMinuto = (60) / (calculaTiempoDesdeVelocidad(jugador->velocidadInicial) * 2);
            jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
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
  /* Aquï¿½ deben estar los llamados a las funciones creadas por ustedes */
}
