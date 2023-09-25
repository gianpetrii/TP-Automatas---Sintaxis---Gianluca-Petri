#include "../include/otraResolucion.h"

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
   return pila.total == 0;
}

int estaLlena(Pila pila)
{
   return pila.total == MAX_ELEMENTOS;
}

int pushChar(Pila *pila, char dato)
{
   if (pila->total < MAX_ELEMENTOS)
   {
      pila->datos[pila->indice].tipo = 0; // Indica que es un char
      pila->datos[pila->indice].dato.caracter = dato;
      pila->indice++;
      pila->total++;
      return 1;
   }
   else
   {
      return 0; // Pila llena
   }
}

int pushInt(Pila *pila, int dato)
{
   if (pila->total < MAX_ELEMENTOS)
   {
      pila->datos[pila->indice].tipo = 1; // Indica que es un int
      pila->datos[pila->indice].dato.entero = dato;
      pila->indice++;
      pila->total++;
      return 1;
   }
   else
   {
      return 0; // Pila llena
   }
}

Elemento pop(Pila *pila)
{
   Elemento aux;
   if (pila->total > 0)
   {
      aux = pila->datos[pila->indice - 1];
      pila->indice--;
      pila->total--;
      return aux;
   }
   else
   {
      // Devuelve un elemento especial para indicar que la pila está vacía
      Elemento vacio;
      vacio.tipo = -1;
      return vacio;
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

int esOperadorSumaResta(char caracter)
{
   if (caracter == '+' || caracter == '-')
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int esOperadorMultiDivi(char caracter)
{
   if (caracter == '*' || caracter == '/')
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

int realizarCuenta(char *cadena)
{
   Pila *miPila = crear();

   int sem_suma_resta = 0;
   int contadorDig = 0;
   printf("Ingrese una cadena: ");

   int i = 0;

   while (cadena[i] != '\0')
   {
      if (esOperando(cadena[i])) // si es un digito
      {
         // Si es un dígito, lo pongo en la pila y sumo 1 al contador
         contadorDig++;
         pushChar(miPila, cadena[i]);
         printf("\nEste simbolo se identifico como operando: %c", cadena[i]);
      }
      else if (esOperador(cadena[i])) // caso de ser una cadena quedan varios pasos
      {
         printf("\nEste simbolo se identifico como operador: %c", cadena[i]);
         // si es operador tengo que primero juntar los digitos anteriores y pasarlo a numero
         if (contadorDig > 0)
         { // caso de que un numero tenga mas de 1 digito
            juntadorDeDigitos(contadorDig, miPila);
            contadorDig = 0;
         }
         if (esOperadorSumaResta(cadena[i]))
         {

            // ya me encargue de que todo lo que es un numero esta pusheado en la pila como tal y se que lo que no lo es, es un operador
            if (sem_suma_resta == 0) // si todavia no tengo que resolver cuenta solo lo agrego a la pila
            {
               sem_suma_resta = 1;
            }
            else if (sem_suma_resta == 1)
            { // caso que ya tenia un operando suma o resta antes asi q lo puedo resolver
               // trayendome los 3 valores anteriores y resolviendo la cuenta y repusheando
               char pop1 = pop(miPila).dato.entero;
               char pop2 = pop(miPila).dato.caracter;
               char pop3 = pop(miPila).dato.entero;

               int resultado; // aca guardo el resultado de operacion para desp pushear
               if (pop2 == '+')
               {
                  resultado = pop3 + pop1;
               }
               else if (pop2 == '-')
               {
                  resultado = pop3 - pop1;
               }
               else
               {
                  printf("\nno pude determinar signo de: %c\n", pop2);
                  break;
               }
               printf("\nresolvi cuenta y pusheo: %d\n", resultado);
               pushInt(miPila, resultado);
            }
            pushChar(miPila, cadena[i]);
         }
         else if (esOperadorMultiDivi(cadena[i]))
         { // caso que lei un * o /
            // aca tengo que popear el int anterior y hacer lo que tengo en cadena[i] junto a los siguientes int hasta que aparezca otro operador
            char numerador = pop(miPila).dato.entero;
            int j = i + 1; // necesito recordar la posicion de la lista mas 1 para buscar proximo operando
            while (esOperando(cadena[j]))
            {
               contadorDig++;
               pushChar(miPila, cadena[j]);
               j++;
            }
            juntadorDeDigitos(contadorDig, miPila); // aca ya repushee el numero combinado
            contadorDig = 0;
            char denominador = pop(miPila).dato.entero; // me traigo el nuevo denominador pusheado
            int resultado;
            if (cadena[i] == '*')
            {
               resultado = numerador * denominador;
            }
            else if (cadena[i] == '/')
            {
               if (denominador == 0)
               {
                  printf("NO SE PUEDE DIVIDIR POR 0");
                  return 0;
               }
               resultado = numerador / denominador;
            }
            printf("la cuenta de * o / me dio: %d", resultado);
            pushInt(miPila, resultado);
            i = j - 1;
         }
      }
      else
      {
         printf("\nNo se renococe el simbolo: %c", cadena[i]);
         break;
      }
      i++;
   }
   // aca tengo que chequear xq puede que haya quedado sin resolver una suma o resta
   if (sem_suma_resta == 1)
   {
      // primero paso ultimo numero a int
      juntadorDeDigitos(contadorDig, miPila);

      // luego me traigo los valores
      int pop1 = pop(miPila).dato.entero;
      char pop2 = pop(miPila).dato.caracter;
      int pop3 = pop(miPila).dato.entero;

      int resultado; // aca guardo el resultado de operacion para desp pushear
      if (pop2 == '+')
      {
         resultado = pop3 + pop1;
      }
      else if (pop2 == '-')
      {
         resultado = pop3 - pop1;
      }
      else
      {
         printf("\nno pude determinar signo de: %c\n", pop2);
      }
      printf("\nresolvi cuenta y pusheo: %d\n", resultado);
      pushInt(miPila, resultado);
   }
   printf("\nEl resultado final es: %d", pop(miPila).dato.entero);
   free(miPila);
   return 0;
}

void juntadorDeDigitos(int contadorDig, Pila *miPila)
{
   if (contadorDig > 0)
   {
      printf("\nAcabo de entrar en el juntador de digitos");
      char popeadoTotal[100] = "";
      printf("\nDigito en popeadoTotal antes de asignarle nada: %c", popeadoTotal[0]);
      for (int j = 0; j < contadorDig; j++)
      {
         Elemento popeado;
         popeado = pop(miPila);
         char caracPopeado;
         caracPopeado = popeado.dato.caracter;
         printf("\nDigito leido: %c", caracPopeado);
         // tengo que ir concatenando los pops que hice
         strcat(popeadoTotal, &caracPopeado);
         printf("\nDigito en popeadoTotal dentro de for loop: %s", popeadoTotal);
      }
      printf("\nLo que quedo concatenado es: %s", popeadoTotal);
      revertirString(popeadoTotal); // aca lo revierto xq queda al reves el string
      int resultado = charHaciaNumero(popeadoTotal);
      printf("\nPasado a int queda: %d\n", resultado);
      pushInt(miPila, resultado); // lo vuelvo a meter a la pila pero ya como char
   }
}
