#include <stdio.h>
#include <ctype.h>
#include <string.h>
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

int main()
{
   // Cadena de prueba
   char cadena[100];
   printf("\nIngrese una cadena: ");
   scanf("%s", cadena);

   // manejo separacion de subcadenas
   const char delim[] = "$";

   while (strcmp(cadena, "exit") != 0)
   {

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
         }
         // En caso de no serlo, se puede agregar aquí la verificación de octal o hexadecimal
         else if (esOctal(subCadena))
         {
            printf("ESTA CADENA ES UN NUMERO OCTAL\n");
         }
         else if (esHexadecimal(subCadena))
         {
            printf("ESTA CADENA ES UN NUMERO HEXADECIMAL\n");
         }

         printf("la evaluacion de esta cadena:%s ha finalizado\n", subCadena);
         // para q automaticamente tome proxima cadena le paso NULL
         subCadena = strtok(NULL, delim);
      }
      printf("\nIngrese una cadena: ");
      scanf("%s", cadena);
   }
   printf("Ya se han evaluado todas las cadenas\n");
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
