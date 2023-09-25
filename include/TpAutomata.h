#ifndef TP_AUTOMATA
#define TP_AUTOMATA

#include "../src/otraResolucion.c"

#include <stdio.h>
#include <ctype.h>
#include <string.h> // para usar strtok

// Declaración de funciones
int verificacionAlfabeto(const char *s);
int verificacionAlfabetoDecimal(const char *s);
int verificacionAlfabetoOctal(const char *s);
int verificacionAlfabetoHexadecimal(const char *s);

int esDecimal(const char *s);
int esOctal(const char *s);
int esHexadecimal(const char *s);

int columnaDecimal(int c);
int columnaOctal(int c);
int columnaHexadecimal(int c);

int evaluadorDeCadenas();

int operacionEntreCaracteres();
int verificacionAlfabetoOperacion(const char *s);

#endif