#include "../include/resolverOperacion.h"

int resolverOperacion(char *operacion)
{
   Pila *pila = crear();
   char sigChar;           // voy a guardar el char actual en cada vuelta
   int resultado;          // aca voy a guardar el resultado
   int sem_suma_resta = 0; // lo voy a usar para saber si estoy dentro de un termino
   int contadorDig = 0;    // lo voy a usar para mandar a charHaciaNumero

   int longitud = strlen(operacion);
   int i = 0;
   while (i < longitud)
   {
      sigChar = operacion[i];
      // caso sigChar es un digito solo sumo uno al contador y pusheo lectura en pila
      if (esOperando(sigChar))
      {
         contadorDig++;
         push(pila, sigChar);
      }
      else if (esOperador(sigChar)) // aca entro en caso de ser un operador
      {
         if (contadorDig > 1)
         { // antes de convertir a int tengo que unir cadena de digitos
            char *popeo;
            for (int j = 0; contadorDig; j++)
            {
               *popeo = *popeo + pop(pila);
            }
            int numero = charHaciaNumero(&popeo);
            push(pila, numero);
         }
         else
         {
         }
      }
      else
      { // caso caracter desconocido
         printf("\nEste char se escapa del dominio:%s\n", sigChar);
         break;
      }
      i++; // vuelvo a evaluar loop condition
   }

   // cuando recorri toda la pila me puede llegar a quedar una cuenta de menor prioridad sin resolver
   while (!estaVacia(*pila))
   {
      // me traigo cada elemento sin resolver
      char *popeado3 = pop(pila);
      char popeado2 = pop(pila);
      char *popeado1 = pop(pila);

      // los paso a ints
      int pop3 = charHaciaNumero(popeado3);
      int pop1 = charHaciaNumero(popeado1);

      // si es una suma hago eso, sino resto
      if (popeado2 == "+")
      {
         resultado = pop1 + pop3;
      }
      else
      {
         resultado = pop1 - pop3;
      }
   }

   return resultado;
}
* /