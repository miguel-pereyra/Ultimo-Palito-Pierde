# El Último Palito Pierde (C)

Implementación en lenguaje C del clásico juego **“El Último Palito Pierde”**.  
Dos jugadores —o un jugador contra la computadora— se turnan para retirar palitos de una pila.  
El jugador que se ve obligado a tomar el **último palito pierde**.

Autor: **Miguel Pereyra**  

---

## Objetivos del proyecto

- Practicar **programación modular** con archivos `.c` y `.h`.
- Implementar funciones genéricas reutilizables.
- Validar correctamente el **input del usuario**.
- Gestionar un juego con **menú**, reglas y turnos.
- Decorar la interfaz con **colores ANSI** en consola.
- Incluir una modalidad de juego contra la **Computadora (CPU)**.

---

## Estructura del proyecto
```text
.
├── main.c         # Lógica principal del juego
├── funciones.c    # Implementación de funciones genéricas (input, ANSI, etc.)
└── funciones.h    # Prototipos de funciones y contrato del módulo
```

main.c incluye:

Menú principal

Selección de modalidad de juego

Turnos del jugador y la computadora

Configuración dinámica del juego

Mensajes y colores

Lo podés ver aquí: main.c

funciones.c / funciones.h implementan:

```text

pedir_entero, pedir_entero_entre

pedir_texto

pedir_double

Validaciones de buffer y rangos

Limpieza de stdin

habilitarANSI() para colores en Windows

Mensajes de error e información

```

Archivos: funciones.c y funciones.h


# Reglas del juego

Se inicia con una cantidad configurable de 20 a 100 palitos (por defecto: 30).

Cada jugador puede retirar entre 1 y N palitos.

El valor N (máximo por turno) está limitado a:

mínimo 3

máximo 10% del total de palitos iniciales

Quien retire el último palito pierde.

Los palitos se representan visualmente como:

```text
|||||||||||||||
```

# Funcionalidades
-  Menú principal

1 → Jugar

2 → Cambiar palitos iniciales

3 → Cambiar máximo a retirar por turno

0 → Salir

- Modos de juego

 Jugador vs Jugador (con nombres personalizados)

 Jugador vs Computadora

La CPU realiza jugadas válidas aleatorias

- Validación de entrada

Reinicia la lectura si el usuario ingresa texto inválido

Manejo de errores con errno

Limpieza de buffer para evitar comportamientos inesperados

Respuesta amigable al usuario en cada error

- Interfaz con colores ANSI

Rojo, azul, verde, amarillo

Separadores visuales

Nombres colorizados según el turno

Compatible con Windows 10+ (usa habilitarANSI())

# Requisitos

Compilador C compatible con C99:

```text
gcc

clang

mingw
```

Windows 10+ para soporte de colores ANSI
(habilitado automáticamente por habilitarANSI())

🔧 Compilación
En Linux / Mac:
```text
gcc main.c funciones.c -o ultimo_palito_pierde
```
En Windows (MinGW):
```text
gcc main.c funciones.c -o upp.exe
```

# Ejemplo visual (simulado)
```text
========================================
== Ultimo Palito Pierde ==
========================================

*** Menu principal ***
1. Jugar
2. Cambiar palitos iniciales (30)
3. Cambiar cantidad maxima a sacar (3)
0. Salir
```

# Ideas de mejoras futuras

Agregar una IA más inteligente en modo CPU (estrategia óptima tipo Nim).

Guardar un historial de partidas (ganador, configuración, fecha).

Top 10 de jugadores

Hacer una versión en otro lenguaje (Python, C++, etc.).

Internacionalización (español / inglés).