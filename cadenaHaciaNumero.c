// pseudocodigo

// para usar pila
#include "cadenaHaciaNumero.h"

int charHaciaNumero(char cadena[])
{
   int posicion = 0, resultado = 0;

   while (strcmp(cadena, "") != 0)
   {
      resultado = resultado * 10 + (cadena[posicion] - '0');
      posicion++;
   }
   return resultado;
}