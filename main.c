/*

 * Este software implementa una versión del juego clásico
 * “El Último Palito Pierde”. Permite configurar la cantidad
 * inicial de palitos, el máximo a retirar por turno y elegir
 * entre jugar contra otro jugador o contra la computadora.
 * El programa gestiona los turnos, muestra visualmente el estado
 * de la pila de palitos y determina quién pierde al tomar el último.
 *
 * Autor: Miguel Pereyra
 */

// directivas de pre procesador
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "funciones.h"

#define MAX_PALITOS 100
#define MIN_PALITOS 20
#define default_PALITOS 30
#define PORC_MAX_RETIRO 0.1
#define MIN_RETIRO 1
#define MIN_MAX_RETIRO 3
#define MAX_NOMBRE_JUGADOR 40

#define RESET "\033[0m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"

enum opciones_menu_principal
{
    SALIR = 0,
    JUGAR = 1,
    CAMBIAR_PALITOS_INICIALES,
    CAMBIAR_MAXIMO_RETIRO,
};
enum opciones_modalidad_juego
{
    VOLVER_MENU_PRINCIPAL = 0,
    CONTRA_OTRO_JUGADOR = 1,
    CONTRA_COMPUTADORA,
};

// Prototipos de funciones
void jugar(int palitos_iniciales, int max_retiro, int *total_palitos, const char *nombre_jugador1, const char *nombre_jugador2, bool contra_computadora);
void opcion_jugar(int palitos_iniciales, int max_retiro, int *total_palitos);
void cambiar_maximo_retiro(int palitos_iniciales, int *max_retiro);
void cambiar_palitos_iniciales(int *palitos_iniciales, int *max_retiro);
void mostrar_palitos(int total_palitos);
void menu_modalidad_juego();
void menu_principal(int palitos_iniciales, int max_retiro);
void separador();

// Funcion principal
int main()
{
    int palitos_iniciales = default_PALITOS;
    int max_retiro = default_PALITOS * PORC_MAX_RETIRO;
    int total_palitos;
    bool salir = false;
    habilitarANSI(); // Habilitar secuencias ANSI en Windows
    do
    {
        menu_principal(palitos_iniciales, max_retiro);
        switch (pedir_entero_entre("\nIngrese opcion:", SALIR, CAMBIAR_MAXIMO_RETIRO))
        {
        case JUGAR:
            opcion_jugar(palitos_iniciales, max_retiro, &total_palitos);
            break;
        case CAMBIAR_PALITOS_INICIALES:
            cambiar_palitos_iniciales(&palitos_iniciales, &max_retiro);
            break;
        case CAMBIAR_MAXIMO_RETIRO:
            cambiar_maximo_retiro(palitos_iniciales, &max_retiro);
            break;
        case SALIR:
            puts("\nGracias por jugar. Hasta luego!");
            salir = true;
            break;
        }
    } while (!salir);
    return 0;
}

// Definicion de funciones
void jugar(int palitos_iniciales, int max_retiro, int *total_palitos, const char *nombre_jugador1, const char *nombre_jugador2, const bool contra_computadora)
{
    int retiro;
    int limite_sup;
    bool fin_de_juego = false;
    bool turno_jugador1 = true; // true = jugador1, false = jugador2 o computadora
    *total_palitos = palitos_iniciales;
    while (!fin_de_juego)
    {
        mostrar_palitos(*total_palitos);
        separador();
        printf("%s\nTurno de %s.\n" RESET, turno_jugador1 ? ROJO : AZUL, turno_jugador1 ? nombre_jugador1 : nombre_jugador2);
        limite_sup = max_retiro;
        if (*total_palitos < max_retiro)
        {
            limite_sup = *total_palitos;
        }
        if (contra_computadora && !turno_jugador1)
        {
            retiro = (rand() % limite_sup) + 1;
        }
        else
        {
            retiro = pedir_entero_entre("\nIngrese la cantidad de palitos a retirar: ", MIN_RETIRO, limite_sup);
        }
        *total_palitos -= retiro;
        printf("%s\n%s ha retirado %d palitos.\n" RESET, turno_jugador1 ? ROJO : AZUL, turno_jugador1 ? nombre_jugador1 : nombre_jugador2, retiro);
        if (*total_palitos <= 0)
        {
            separador();
            separador();
            printf("%s\n==%s ha perdido==\n" RESET, turno_jugador1 ? ROJO : AZUL, turno_jugador1 ? nombre_jugador1 : nombre_jugador2);
            separador();
            fin_de_juego = true;
        }
        turno_jugador1 = !turno_jugador1; // alternar turno
    }
}

void opcion_jugar(int palitos_iniciales, int max_retiro, int *total_palitos)
{
    char nombre1[MAX_NOMBRE_JUGADOR], nombre2[MAX_NOMBRE_JUGADOR];
    menu_modalidad_juego();
    switch (pedir_entero_entre("\nIngrese opcion: ", VOLVER_MENU_PRINCIPAL, CONTRA_COMPUTADORA))
    {
    case CONTRA_OTRO_JUGADOR:
        pedir_texto(ROJO "Ingrese el nombre del Jugador 1: " RESET, nombre1, MAX_NOMBRE_JUGADOR);
        pedir_texto(AZUL "Ingrese el nombre del Jugador 2: " RESET, nombre2, MAX_NOMBRE_JUGADOR);
        jugar(palitos_iniciales, max_retiro, total_palitos, nombre1, nombre2, false);
        break;
    case CONTRA_COMPUTADORA:
        pedir_texto(ROJO "Ingrese el nombre del Jugador 1: " RESET, nombre1, MAX_NOMBRE_JUGADOR);
        jugar(palitos_iniciales, max_retiro, total_palitos, nombre1, "Computadora", true);
        break;
    case VOLVER_MENU_PRINCIPAL:
        puts("\nVolviendo al menu principal...");
        break;
    }
}

void cambiar_maximo_retiro(int palitos_iniciales, int *max_retiro)
{
    int max_teorico = (int)(palitos_iniciales * PORC_MAX_RETIRO);
    if (max_teorico < MIN_MAX_RETIRO)
        max_teorico = MIN_MAX_RETIRO;

    int nuevo_valor = pedir_entero_entre(
        "\nIngrese la cantidad maxima a retirar por turno: ",
        MIN_MAX_RETIRO,
        max_teorico);

    *max_retiro = nuevo_valor;
}

void cambiar_palitos_iniciales(int *palitos_iniciales, int *max_retiro)
{
    // 1) Pedir el nuevo valor dentro del rango permitido
    int nuevo_valor = pedir_entero_entre(
        "\nIngrese la cantidad inicial de palitos (20-100): ",
        MIN_PALITOS,
        MAX_PALITOS);

    *palitos_iniciales = nuevo_valor;

    // 2) Calcular el nuevo máximo teórico (10% de los palitos)
    int max_teorico = (int)(nuevo_valor * PORC_MAX_RETIRO);

    // 3) Asegurar que el límite nunca sea menor a 3
    if (max_teorico < MIN_MAX_RETIRO)
        max_teorico = MIN_MAX_RETIRO;

    // 4) Actualizar el valor
    *max_retiro = max_teorico;

    printf("\nNuevo maximo a retirar por turno: %d\n", *max_retiro);
}

void mostrar_palitos(int total_palitos)
{
    separador();
    printf("\nPalitos restantes: " AMARILLO);
    for (int i = 0; i < total_palitos; i++)
    {
        putchar('|');
    }
    printf(RESET "\n");
}

void menu_modalidad_juego()
{
    separador();
    printf("\n*** Modalidad de juego ***"
           "\n1. Jugar contra otro jugador"
           "\n2. Jugar contra la computadora"
           "\n0. Volver al menu principal");
}

void menu_principal(int palitos_iniciales, int max_retiro)
{
    separador();
    printf(VERDE "\n%3s \n" RESET, "== Ultimo Palito Pierde ==");
    separador();
    printf("\n*** Menu principal ***"
           "\n1. Jugar"
           "\n2. Cambiar palitos iniciales (valor actual: %i)"
           "\n3. Cambiar cantidad maxima a sacar (valor actual: %i)"
           "\n0. Salir",
           palitos_iniciales, max_retiro);
}
void separador()
{
    printf("========================================");
}
