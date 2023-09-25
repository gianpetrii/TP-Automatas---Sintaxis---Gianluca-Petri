#ifndef OTRA_RESOLUCION_H
#define OTRA_RESOLUCION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/cadenaHaciaNumero.c"

#define MAX_ELEMENTOS 100

typedef struct
{
   int tipo; // Tipo de elemento (0 para char, 1 para int)
   union
   {
      char caracter;
      int entero;
   } dato;
} Elemento;

typedef struct
{
   Elemento datos[MAX_ELEMENTOS];
   int indice;
   int total;
} Pila;

int esOperadorSumaResta(char caracter);
int esOperadorMultiDivi(char caracter);
int nivelPrecedencia(char operador);
int estaVacia(Pila pila);
int estaLlena(Pila pila);
int pushChar(Pila *pila, char dato);
int pushInt(Pila *pila, int dato);
Elemento pop(Pila *pila);
int nivelPrecedencia(char operador);
int esOperador(char caracter);
int esOperando(char elemento);
void juntadorDeDigitos(int contadorDig, Pila *miPila);
int realizarCuenta(char *cadena);

#endif