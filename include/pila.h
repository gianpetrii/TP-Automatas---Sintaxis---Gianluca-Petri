#ifndef PILA
#define PILA

#include <stdlib.h>
#define MAX_ELEMENTOS 100

typedef struct pila
{
   int indice;
   int total;
   char datos[MAX_ELEMENTOS];
} Pila; // defino la pila para guardar operadores

// prototipos
int estaVacia(Pila pila);
int estaLlena(Pila pila);
int push(Pila *pila, char dato);
char pop(Pila *pila);
int nivelPrecedencia(char operador);
int tieneMasPriori(char operador1, char operador2);
int esOperador(char caracter);
int esOperando(char elemento);

#endif