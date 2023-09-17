// para usar pila
#include "include/TpAutomata.h"

int main()
{
   char funcion[30];
   printf("Que funcion quiere utilizar?: ");
   scanf("%s", funcion);

   // finalizador de programa, en consola tengo que escribir \0
   while (strcmp(funcion, "exit") != 0)
   {
      if (strcmp(funcion, "evaluadorDeCadenas") == 0)
      {
         evaluadorDeCadenas();
      }
      else if (strcmp(funcion, "operacionEntreCaracteres") == 0)
      {
         operacionEntreCaracteres();
      }
      else
      {
         printf("\nLa funcion pedida no existe\n");
      }
      printf("Que funcion quiere utilizar?: ");
      scanf("%s", funcion);
   }
   printf("El programa ha finalizado");
   return 0;
}

int evaluadorDeCadenas()
{
   char metodo[30];
   printf("Por donde se desea leer la cadena?: ");
   scanf("%s", metodo);

   char cadena[100]; // aca voy a guardar mi cadena a evaluar

   while (strcmp(metodo, "exit") != 0)
   {

      if (strcmp(metodo, "consola") == 0)
      {
         // recibo cadena por consola
         printf("\nIngrese una cadena: ");
         scanf("%s", cadena);
         strcpy(metodo, "exit");
      }
      else if (strcmp(metodo, "archivo") == 0)
      {
         // aca me traigo de archivo el valor de cadena
         FILE *fp;
         fp = fopen("tests/test.txt", "r");

         // en caso de no poder abrirlo
         if (fp == NULL)
         {
            printf("\nArchivo NO se pudo abrir");
         }
         else
         {
            printf("\nArchivo abierto con exito");

            // leo linea de comando
            fscanf(fp, "%s", cadena);
            // cierro el archivo
            fclose(fp);

            // para salir del loop
            strcpy(metodo, "exit");
         }
      }
      else
      {
         printf("\nEl metodo pedido no existe\n");
         printf("Por donde se desea leer la cadena?: ");
         scanf("%s", metodo);
      }

      // manejo separacion de subcadenas
      const char delim[] = "$";

      // si escribo exit por consola la funcion finaliza
      while (strcmp(cadena, "exit") != 0)
      {
         // contadores para cada tipo de numero
         int cantidadDecimales = 0;
         int cantidadOctales = 0;
         int cantidadHexadecimales = 0;

         // Primera llamada para obtener el primer sub cadena
         char *subCadena = strtok(cadena, delim);
         // Voy recorriendo cada sub cadena de a una
         while (subCadena != NULL)
         {

            printf("La sub cadena actual es: %s\n", subCadena);
            // Verifico que los chars estén en el alfabeto
            if (!verificacionAlfabeto(subCadena))
            {
               printf("ESTA CADENA TIENE AL MENOS UN CARACTER QUE NO PERTENECE A NINGUN ALFABETO\n");
            }
            // Ahora pregunto si es un número decimal
            else if (esDecimal(subCadena))
            {
               printf("ESTA CADENA ES UN NUMERO DECIMAL\n");
               cantidadDecimales = cantidadDecimales + 1; // sumo uno al contador
            }
            // En caso de no serlo, se puede agregar aquí la verificación de octal o hexadecimal
            else if (esOctal(subCadena))
            {
               printf("ESTA CADENA ES UN NUMERO OCTAL\n");
               cantidadOctales++; // sumo uno al contador
            }
            else if (esHexadecimal(subCadena))
            {
               printf("ESTA CADENA ES UN NUMERO HEXADECIMAL\n");
               cantidadHexadecimales++; // sumo uno al contador
            }

            printf("la evaluacion de esta cadena:%s ha finalizado\n", subCadena);
            // para q automaticamente tome proxima cadena le paso NULL
            subCadena = strtok(NULL, delim);
         }
         // imprimo contadores en pantalla
         printf("La cantidad de numeros decimales evaluados fue: %d\n", cantidadDecimales);
         printf("La cantidad de numeros octales evaluados fue: %d\n", cantidadOctales);
         printf("La cantidad de numeros hexadecimales evaluados fue: %d\n", cantidadHexadecimales);

         // vuelvo a pedir cadena
         printf("\nIngrese una cadena: ");
         scanf("%s", cadena);
      }
      printf("Que metodo quiere utilizar?: ");
      scanf("%s", metodo);
   }

   printf("Saliendo del evaluador de cadenas\n");
   return 0;
}
// ##########################FUNCIONES GENERALES##########################
// Función que verifica que todos los chars de la cadena pertenezcan al alfabeto
int verificacionAlfabeto(const char *s)
{
   // Defino una variable que usaré para recorrer de a un caracter la cadena
   unsigned i;
   for (i = 0; s[i]; i++)
   {
      // Uso comillas simples para representar caracteres individuales
      if (!(s[i] == '+' || s[i] == '-' || s[i] == '$' || isxdigit(s[i]) || s[i] == 'x' || s[i] == 'X'))
      {
         return 0;
      }
   }
   printf("ESTA CADENA ESTA EN ALGUNO DE LOS 3 ALFABETOS\n");
   return 1; // Si no se encontraron caracteres no permitidos, la cadena es válida
}

// ##########################FUNCIONES DECIMALES##########################
// Función que implementa el autómata para números decimales
int esDecimal(const char *s)
{
   // Verifico que los chars estén en el alfabeto
   if (!verificacionAlfabetoDecimal(s))
   {
      return 0; // No es un número decimal válido
   }
   const int tt[4][4] = {
       {1, 1, 2, 3},
       {3, 3, 2, 3},
       {3, 3, 2, 2},
       {3, 3, 3, 3}};

   // inicializo variable donde ire almacenando el estado en el que me encuentro
   int estado = 0;
   printf("estado inicial:%d\n", estado);
   // inicializo variable que usare para recorrer las posiciones en mi cadena
   int i = 0;
   // inicializo mi cadena
   int c = s[i];

   // este es el simbolo de salto de linea
   while (c != '\0')
   {
      // actualizo el estado como el cruce de fila y col (uso f_columna para determinar la columna)
      estado = tt[estado][columnaDecimal(c)];
      printf("nuevo estado actual:%d\n", estado);
      // paso al siguiente caracter
      i++;
      c = s[i];
   }

   if (estado == 2) // estados finales correctos
   {
      return 1; // Es un número decimal válido
   }
   return 0; // No es un número decimal válido
}

// Función que verifica que todos los chars de la cadena pertenezcan al alfabeto decimal
int verificacionAlfabetoDecimal(const char *s)
{
   // Defino una variable que usaré para recorrer de a un caracter la cadena
   unsigned i;
   for (i = 0; s[i]; i++)
   {
      // Uso comillas simples para representar caracteres individuales
      if (!(s[i] == '+' || s[i] == '-' || isdigit(s[i])))
      {
         printf("ESTA CADENA NO ESTA EN EL ALFABETO DECIMAL\n");
         return 0;
      }
   }
   printf("ESTA CADENA ESTA EN EL ALFABETO DECIMAL\n");
   return 1; // Si no se encontraron caracteres no permitidos, la cadena es válida
}

// Función que devuelve la columna correspondiente para el autómata
int columnaDecimal(int c)
{
   switch (c)
   {
   case '+':
      return 0;
   case '-':
      return 1;
   case '0':
      return 3;
   default:
      return 2;
   }
}

// ##########################FUNCIONES OCTALES##########################
// Función que implementa el autómata para números octales
int esOctal(const char *s)
{
   // Verifico que los chars estén en el alfabeto
   if (!verificacionAlfabetoOctal(s))
   {
      return 0; // No es un número octal válido
   }
   const int tt[3][2] = {
       {1, 2},
       {1, 1},
       {2, 2}};

   // inicializo variable donde ire almacenando el estado en el que me encuentro
   int estado = 0;
   printf("estado inicial:%d\n", estado);
   // inicializo variable que usare para recorrer las posiciones en mi cadena
   int i = 0;
   // inicializo mi cadena
   int c = s[i];

   // este es el simbolo de salto de linea
   while (c != '\0')
   {
      // actualizo el estado como el cruce de fila y col (uso f_columna para determinar la columna)
      estado = tt[estado][columnaOctal(c)];
      printf("nuevo estado actual:%d\n", estado);
      // paso al siguiente caracter
      i++;
      c = s[i];
   }

   if (estado == 1) // estados finales correctos
   {
      return 1; // Es un número octal válido
   }
   return 0; // No es un número octal válido
}

// Función que verifica que todos los chars de la cadena pertenezcan al alfabeto octal
int verificacionAlfabetoOctal(const char *s)
{
   // Defino una variable que usaré para recorrer de a un caracter la cadena
   unsigned i;
   for (i = 0; s[i]; i++)
   {
      // Uso comillas simples para representar caracteres individuales
      if (!isdigit(s[i]) || s[i] == '9' || s[i] == '8')
      {
         printf("ESTA CADENA NO ESTA EN EL ALFABETO OCTAL\n");
         return 0;
      }
   }
   printf("ESTA CADENA ESTA EN EL ALFABETO OCTAL\n");
   return 1; // Si no se encontraron caracteres no permitidos, la cadena es válida
}

// Función que devuelve la columna correspondiente para el autómata
int columnaOctal(int c)
{
   switch (c)
   {
   case '0':
      return 0;
   default:
      return 1;
   }
}
// ##########################FUNCIONES HEXADECIMALES##########################
// Función que implementa el autómata para números Hexadecimales
int esHexadecimal(const char *s)
{
   // Verifico que los chars estén en el alfabeto
   if (!verificacionAlfabetoHexadecimal(s))
   {
      return 0; // No es un número Hexadecimal válido
   }
   const int tt[4][3] = {
       {1, 3, 3},
       {3, 2, 3},
       {2, 3, 2},
       {3, 3, 3}};

   // inicializo variable donde ire almacenando el estado en el que me encuentro
   int estado = 0;
   printf("estado inicial:%d\n", estado);
   // inicializo variable que usare para recorrer las posiciones en mi cadena
   int i = 0;
   // inicializo mi cadena
   int c = s[i];

   // este es el simbolo de salto de linea
   while (c != '\0')
   {
      // actualizo el estado como el cruce de fila y col (uso f_columna para determinar la columna)
      estado = tt[estado][columnaHexadecimal(c)];
      printf("nuevo estado actual:%d\n", estado);
      // paso al siguiente caracter
      i++;
      c = s[i];
   }

   if (estado == 2) // estados finales correctos
   {
      return 1; // Es un número Hexadecimal válido
   }
   return 0; // No es un número Hexadecimal válido
}

// Función que verifica que todos los chars de la cadena pertenezcan al alfabeto Hexadecimal
int verificacionAlfabetoHexadecimal(const char *s)
{
   // Defino una variable que usaré para recorrer de a un caracter la cadena
   unsigned i;
   for (i = 0; s[i]; i++)
   {
      // Uso comillas simples para representar caracteres individuales
      if (!(isxdigit(s[i]) || s[i] == 'x' || s[i] == 'X'))
      {
         printf("ESTA CADENA NO ESTA EN EL ALFABETO HEXADECIMAL\n");
         return 0;
      }
   }
   printf("ESTA CADENA ESTA EN EL ALFABETO HEXADECIMAL\n");
   return 1; // Si no se encontraron caracteres no permitidos, la cadena es válida
}

// Función que devuelve la columna correspondiente para el autómata
int columnaHexadecimal(int c)
{
   switch (c)
   {
   case '0':
      return 0;
   case 'x':
      return 1;
   case 'X':
      return 1;
   default:
      return 2;
   }
}

int operacionEntreCaracteres()
{
   char operacion[100];
   printf("\nIngrese una operacion a realizar: ");
   scanf("%s", operacion);

   while (strcmp(operacion, "exit") != 0)
   {
      printf("La operacion a realizar es: %s\n", operacion);

      // chequeo cadena
      if (!verificacionAlfabetoOperacion(operacion))
      {
         printf("ESTA CADENA NO ESTA EN EL ALFABETO OPERABLE\n");
      }
      else
      {
         printf("ESTA CADENA ESTA EN EL ALFABETO OPERABLE\n");
         char *postfija;
         postfija = infijaHaciaPostfija(operacion);
         printf("Primero reescribo la expresion como postfija: %s\n", postfija);
      }
      // vuelvo a preguntar para ver si se quiere hacer nueva operacion
      printf("\nIngrese una operacion a realizar: ");
      scanf("%s", operacion);
   }

   printf("La funcion operacionEntreCaracteres ha terminado\n");
   return 0;
}

// Función que verifica que todos los chars de la cadena pertenezcan al alfabeto de operaciones
int verificacionAlfabetoOperacion(const char *s)
{
   // Defino una variable que usaré para recorrer de a un caracter la cadena
   unsigned i;
   for (i = 0; s[i]; i++)
   {
      // Uso comillas simples para representar caracteres individuales
      if (!(s[i] == '+' || s[i] == '-' || isdigit(s[i]) || s[i] == '/' || s[i] == '*'))
      {
         return 0;
      }
   }
   return 1; // Si no se encontraron caracteres no permitidos, la cadena es válida
}

char *infijaHaciaPostfija(char *infija)

{
   char charActual, operador; // mi char actual y el operador cuando lo tenga q evaluar
   char *postfija;
   postfija = malloc(sizeof(char) * 100); // aca voy a ir poniendo expresion postfija
   int j = 0;                             // posicion en la cadena postfija
   int pos = 0;                           // posicion en la recorrida de la cadena de prueba
   Pila *pila = crear();
   int longitud = strlen(infija); // longitud de la cadena

   while (pos < longitud) // condicion de no haber recorrido todos los chars en cadena
   {
      charActual = infija[pos];

      if (esOperando(charActual)) // si es operando escribo en postfija y reubico la posicion
      {
         postfija[j] = charActual;
         j++;
      }
      else if (esOperador(charActual)) // si es operador
      {
         if (!estaVacia(*pila)) // si esta vacia meto directo en pila
         {
            int sem_rechequear = 1; // defino un semaforo para saber si tengo que volver a comparar con int en la cima de la pila

            while (!estaVacia(*pila) && sem_rechequear) // ingreso siempre que la pila tenga algo y tenga q rechequear
            {
               operador = pop(pila);                     // me traigo tope de pila
               if (tieneMasPriori(operador, charActual)) // comparo precedencia con mi charActual
               {
                  postfija[j] = operador; // si tiene mas o igual prioridad pongo el operador en postfija y vuelvo a chequear pila con charActual
                  j++;
                  sem_rechequear = 1;
               }
               else
               {
                  sem_rechequear = 0;
                  push(pila, operador); // como operador no tiene mayor prioridad lo devuelvo a la pila
               }
            }
         }
         push(pila, charActual); // meto charActual actual al final de cola
      }
      pos++; // analizo el proximo caracter
   }
   while (!estaVacia(*pila)) // esto es al final para agregar todos los operadores restantes de menor precedencia
   {
      operador = pop(pila); // traigo tope de pila y lo agrego a postfija repitiendo hasta que no queden operadores
      postfija[j] = operador;
      j++;
   }
   postfija[j] = '\0'; // agrego el final de cadena para saber cuando finaliza

   return postfija;
}