INTRODUCCION AL TRABAJO:


EL siguiente trabajo realiza una simulacion de pesca, informandole al usuario como va quedando el arrecife del cual saca los pokemones
que cumplen con cierta condicion, y al final guarda los datos de los pokemones que traslado del arrecife al acuario en un archivo .txt

----------------------------------------------------------------------------------------------------------------------------------------

COMPILACION:

[SOLO CORRE DE MANERA CORRECTA EN UNA TERMINAL DE LINUX QUE TENGA GCC, MAKEFILE Y VALGRIND INSTALADOS]

El trabajo se compila de la siguiente forma:

	gcc *.c -o evento_pesca -Wall -Werror -Wconversion -std=c99

Y para corroborar el correcto uso de memoria dinamica se utiliza el comando:

	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca arrecife.txt acuario.txt

Una vez compilado y corroborado el correcto uso de memoria, se lo ejecuta de la siguiente forma:
	
	./evento_pesca [RUTA ARCHIVO ARRECIFE] [RUTA ARCHIVO ACUARIO]
	|
	|->	./evento_pesca = buscara el archivo generado por la compilacion y lo ejecutará.
	|
	|->	[RUTA ARCHIVO ARRECIFE] = es el archivo .txt donde tiene alojado los datos de todos los pokemones en el arrecife.
	|	Sin este archivo no se podra ejecutar ningun funcionamiento.
	|
	|->	[RUTA ARCHIVO ACUARIO] = es el archivo .txt donde guardara los datos de todos los pokemones que traslado del arrecife
		al acuario. Sin este archivo no se podra ejecutar ningun funcionamiento.

----------------------------------------------------------------------------------------------------------------------------------------

EXPLICACION DE CONCEPTOS:


Punteros: son variables que almacenan una o mas (en este caso es un vector) direcciones de memoria. Pueden ser de cualquier tipo de dato.

NOTACION: [TIPO DE DATO]* puntero;

---------------------------------------------------

Aritmetica de punteros: es lo que se utiliza para acceder a las direcciones de memoria de un vector vinculado a un puntero.
Se realiza sumando o restando un numero, teniendo en cuenta de no querer acceder a memoria inexistente o que no nos corresponde.

Ejemplo: para acceder a la posicion 1 se puede hacer:
													*(puntero + 1);--|
																	 |--> significan lo mismo.
													puntero[1];------|

---------------------------------------------------

Punteros a funciones: son tipos de dato que guardan la direccion de memoria de una o varias funciones (en este caso es un vector).
Se los puede utilizar por ejemplo para enviarlos como parametro a una funcion de otra biblioteca, o guardar varias funciones en un
vector de puntero a funciones y utilizarlos iterativamente.

Ejemplo:	int mostrar_numero(int numero){}		//firma de una funcion que imprime un nombre
			int (*puntero_a_funcion)(int); 			//defino un puntero a funcion
			puntero_a_funcion = mostrar_numero; 	//le asigno la funcion mostrar_numero

			puntero_a_funcion(1); 					//puedo llamar a la funcion "mostrar numero" de esta forma

---------------------------------------------------

Malloc: funcion que reserva cierta cantidad de memoria en el heap que le pasemos, y devuelve la direccion de memoria
(se debe guardar en un puntero). Devuelve "NULL" en caso de no poder reservar la memoria.

Ejemplo: 	int* puntero_entero = malloc(sizeof(int));

---------------------------------------------------

Realloc: funcion que reasigna una cierta cantidad de memoria (en el heap) que le pasemos, junto a un tamaño. Devuelve la nueva
direccion de memoria, o "NULL" en caso de fallar.

Ejemplo: 	char* puntero = malloc(sizeof(char)); // puntero con una direccion de memoria asignada con malloc
			size_t nuevo_tamanio = 2;
			char* nuevo_puntero = realloc(puntero, nuevo_tamanio * sizeof(char));
