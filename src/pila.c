#include "../include/pila.h"

Pila *crear()
{
   Pila *p;
   p = (Pila *)malloc(sizeof(Pila));
   p->indice = 0;
   p->total = 0;

   return p;
}

int estaVacia(Pila pila)
{
   if (pila.total == 0)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int estaLlena(Pila pila)
{
   if (pila.total == MAX_ELEMENTOS)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int push(Pila *pila, char dato)
{
   if (pila->total < MAX_ELEMENTOS)
   {
      pila->datos[pila->indice] = dato;
      pila->indice++;
      pila->total++;
      return 1;
   }
   else
   {
      return 0;
   }
}

char pop(Pila *pila)
{
   int aux;
   if (pila->total > 0)
   {
      aux = pila->datos[pila->indice - 1];
      pila->indice--;
      pila->total--;
      return aux;
   }
   else
   {
      return -1;
   }
}

int nivelPrecedencia(char operador)
{
   int nivel = 0;
   switch (operador)
   {
   case '+':
      nivel = 1;
      break;

   case '-':
      nivel = 1;
      break;

   case '*':
      nivel = 2;
      break;

   case '/':
      nivel = 2;
      break;
   }
   return nivel;
}

int tieneMasPriori(char operador1, char operador2)
{
   int preceOperador1 = nivelPrecedencia(operador1);
   int preceOperador2 = nivelPrecedencia(operador2);

   if (preceOperador1 >= preceOperador2)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int esOperador(char caracter)
{
   if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/')
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int esOperando(char elemento)
{
   if (elemento >= '0' && elemento <= '9')
   {
      return 1;
   }
   else
   {
      return 0;
   }
}