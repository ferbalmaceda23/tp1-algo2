#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define MAX_FUNCIONES 5
#define MAX_TRASLADOS 5
#define ROJO "rojo"
#define VIOLETA "violeta"
#define VELOCIDAD_LENTA 25
#define PESO_BAJO 50

#define DEFAULT "\e[0m"
#define SUBRAYADO "\e[4m"

#define L_NEGRO "\e[30m"
#define L_ROJO "\e[31m"
#define L_VERDE "\e[32m"
#define L_AMARILLO "\e[33m"
#define L_AZUL "\e[34m"
#define L_MAGENTA "\e[35m"
#define L_CIAN "\e[36m"
#define L_BLANCO "\e[37m"

#define F_NEGRO "\e[40m"
#define F_ROJO "\e[41m"
#define F_VERDE "\e[42m"
#define F_AMARILLO "\e[43m"
#define F_AZUL "\e[44m"
#define F_MAGENTA "\e[45m"
#define F_CIAN "\e[46m"
#define F_BLANCO "\e[47m"

/*Procedimiento que chequea la primer letra de la especie del pokemon.
 *Recibe un struct de pokemon_t por referencia e inicializado.
 *Devuelve true si se cumple la condicion dentro del return, sino devuelve false.
 */
bool especie_empieza_con_s(pokemon_t* pokemon){
	return ((*pokemon).especie[0] == 's' || (*pokemon).especie[0] == 'S');
}

/*Procedimiento que chequea el color del pokemon.
 *Recibe un struct de pokemon_t por referencia e inicializado.
 *Devuelve true si se cumple la condicion dentro del return, sino devuelve false.
 */
bool es_rojo(pokemon_t* pokemon){
	return (strcmp((*pokemon).color, ROJO) == 0);
}

/*Procedimiento que chequea el color del pokemon.
 *Recibe un struct de pokemon_t por referencia e inicializado.
 *Devuelve true si se cumple la condicion dentro del return, sino devuelve false.
 */
bool es_violeta(pokemon_t* pokemon){
	return (strcmp((*pokemon).color, VIOLETA) == 0);
}

/*Procedimiento que chequea el peso del pokemon.
 *Recibe un struct de pokemon_t por referencia e inicializado.
 *Devuelve true si se cumple la condicion dentro del return, sino devuelve false.
 */
bool es_rapido(pokemon_t* pokemon){
	return ((*pokemon).velocidad > VELOCIDAD_LENTA);
}

/*Procedimiento que chequea el peso del pokemon.
 *Recibe un struct de pokemon_t por referencia e inicializado.
 *Devuelve true si se cumple la condicion dentro del return, sino devuelve false.
 */
bool es_flaco(pokemon_t* pokemon){
	return ((*pokemon).peso < PESO_BAJO);
}

/*Procedimiento que muestra por terminal un pokemones con un formato en especifico.
 *Recibe un struct pokemon_t por referencia e inicializado.
 *Devuelve una impresion por pantalla.
 */
void imprimir_pokemon_en_rojo(pokemon_t* pokemon){
	printf( F_ROJO L_NEGRO SUBRAYADO "|%10s|%9i|%4i|%12s|" DEFAULT "\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso,
		(*pokemon).color);
}

/*Procedimiento que muestra por terminal un pokemones con un formato en especifico.
 *Recibe un struct pokemon_t por referencia e inicializado.
 *Devuelve una impresion por pantalla.
 */
void imprimir_pokemon_en_azul(pokemon_t* pokemon){
	printf( F_AZUL L_NEGRO SUBRAYADO "|%10s|%9i|%4i|%12s|" DEFAULT "\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso,
		(*pokemon).color);
}

/*Procedimiento que muestra por terminal un pokemones con un formato en especifico.
 *Recibe un struct pokemon_t por referencia e inicializado.
 *Devuelve una impresion por pantalla.
 */
void imprimir_pokemon_en_verde(pokemon_t* pokemon){
	printf( F_VERDE L_NEGRO SUBRAYADO "|%10s|%9i|%4i|%12s|" DEFAULT "\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso,
		(*pokemon).color);
}

/*Procedimiento que muestra por terminal un pokemones con un formato en especifico.
 *Recibe un struct pokemon_t por referencia e inicializado.
 *Devuelve una impresion por pantalla.
 */
void imprimir_pokemon_en_cian(pokemon_t* pokemon){
	printf( F_CIAN L_NEGRO SUBRAYADO "|%10s|%9i|%4i|%12s|" DEFAULT "\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso,
		(*pokemon).color);
}

/*Procedimiento que muestra por terminal un pokemones con un formato en especifico.
 *Recibe un struct pokemon_t por referencia e inicializado.
 *Devuelve una impresion por pantalla.
 */
void imprimir_pokemon_en_magenta(pokemon_t* pokemon){
	printf( F_MAGENTA L_NEGRO SUBRAYADO "|%10s|%9i|%4i|%12s|" DEFAULT "\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso,
		(*pokemon).color);
}

int main(int argc, char* argv[]){

	if (argc < 3){
		printf("Comando incorrecto. Corrobore el README.txt.\n");
		return 0;
	}

	arrecife_t* arrecife = crear_arrecife(argv[1]);
	if (arrecife == NULL){
		printf("No se pudo crear el arrecife.\n");
		return 0;
	}

	acuario_t* acuario = crear_acuario();
	if (acuario == NULL){
		printf("No se pudo crear el acuario.\n");
		liberar_arrecife(arrecife);
		return 0;
	}

	bool (*seleccionar_pokemon[MAX_FUNCIONES])(pokemon_t*);

	seleccionar_pokemon[0] = especie_empieza_con_s;
	seleccionar_pokemon[1] = es_rojo;
	seleccionar_pokemon[2] = es_violeta;
	seleccionar_pokemon[3] = es_rapido;
	seleccionar_pokemon[4] = es_flaco;

	void (*mostrar_pokemon[MAX_FUNCIONES])(pokemon_t*);

	mostrar_pokemon[0] = imprimir_pokemon_en_rojo;
	mostrar_pokemon[1] = imprimir_pokemon_en_azul;
	mostrar_pokemon[2] = imprimir_pokemon_en_verde;
	mostrar_pokemon[3] = imprimir_pokemon_en_cian;
	mostrar_pokemon[4] = imprimir_pokemon_en_magenta;

	int tandas_traslado[MAX_TRASLADOS] = {25, 20, 19, 18, 17};

	system("clear");
	printf(L_AMARILLO "BIENVENID@ AL SIMULADOR DE PESCA 3000.\n\n");
	printf("A contiuacion se realizara una muestra\n");
	printf("de los cambios que se generan en el\n");
	printf("arrecife en base a la cantidad y tipo\n");
	printf("de pokemones que elige para llevarse\n");
	printf("al acuario.\n\n");
	printf("Presione [ENTER] para continuar..." DEFAULT "\n");
	getchar();

	int i = 0;

	while ( (i < MAX_TRASLADOS) && (trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i], tandas_traslado[i]) == EXITO) ){
		
		system("clear");
		
		if ((*arrecife).cantidad_pokemon != 0){
			printf("\n" F_AMARILLO "LISTA DE POKEMONES EN ARRECIFE LUEGO DE TRASLADO #%i:" DEFAULT "\n\n", i+1);
			printf( F_AMARILLO L_NEGRO SUBRAYADO "|%10s|%s|%s|%12s|" DEFAULT "\n", "ESPECIE", "VELOCIDAD", "PESO", "COLOR");
			censar_arrecife(arrecife, mostrar_pokemon[i]);
		}
		else{
			printf( L_AMARILLO "ARRECIFE VACIO.\n" DEFAULT);
		}

		printf("\n");
		printf(F_AMARILLO "Pokemones en el arrecife: %i." DEFAULT "\n", (*arrecife).cantidad_pokemon);
		printf(F_AMARILLO "Pokemones en el acuario: %i." DEFAULT "\n\n", (*acuario).cantidad_pokemon);
		
		if (i < 4){
			printf(L_AMARILLO "Presione [ENTER] para continuar...\n" DEFAULT);
			getchar();
		}

		i++;
	}


	guardar_datos_acuario(acuario, argv[2]);

	if (arrecife != NULL) liberar_arrecife(arrecife);

	if (acuario != NULL) liberar_acuario(acuario);

	printf("\n"F_AMARILLO L_NEGRO "SIMULACION TERMINADA." DEFAULT "\n\n");
	
	return 0;
}