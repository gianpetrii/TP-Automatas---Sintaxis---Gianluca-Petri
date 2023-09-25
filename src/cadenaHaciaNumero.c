#include <stdio.h>
#include <ctype.h>
#include <string.h>

int charHaciaNumero(char *cadena);
void revertirString(char *str); // cuando vienen de la pila estan al reves los chars por eso esta funcion

int charHaciaNumero(char *cadena)
{
   int pos = 0, resultado = 0;

   while (cadena[pos] != '\0')
   {
      resultado = resultado * 10 + (cadena[pos] - '0');
      pos++;
   }
   return resultado;
}

void revertirString(char *cadena)
{
   int length = strlen(cadena);
   int i, j;
   char temp;

   for (i = 0, j = length - 1; i < j; i++, j--)
   {
      // Intercambia los caracteres cadena[i] y cadena[j]
      temp = cadena[i];
      cadena[i] = cadena[j];
      cadena[j] = temp;
   }
}
