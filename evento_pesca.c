#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>

#define FORMATO_R_POKEMON "%50[^;];%i;%i;%50[^\n]\n"
#define FORMATO_W_POKEMON "%s;%i;%i;%s\n"

#define EXITO 0
#define ERROR -1

#define UN_POKEMON 4

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

/*Funcion que agrega 1 pokemon al vector de struct pokemon_t y aumenta el tamaño de este en la memoria dinamica.
 *Recibe un puntero a un vector de struct pokemon_t, un struct pokemon_t y la cantidad de pokemones en el vector, en ese momento.
 *(todos valores inicializados)
 *Devuelve un puntero a un vector de struct pokemon_t.
 */

pokemon_t* agregar_pokemon(pokemon_t* p_pokemon, pokemon_t pokemon, int cant_pokemon){

	int nuevo_tam = cant_pokemon + 1;

	pokemon_t* p_pokemon_aux = realloc(p_pokemon, (size_t)nuevo_tam*sizeof(pokemon_t));
	if (p_pokemon_aux == NULL)
		return NULL;

	p_pokemon = p_pokemon_aux;
	p_pokemon[cant_pokemon] = pokemon;

	return p_pokemon;
}
/* es una funcion publica, corroborar la biblioteca correspondiente */
arrecife_t* crear_arrecife(const char* ruta_archivo){

	FILE* arch_arrecife = fopen(ruta_archivo, "r");

	if (!arch_arrecife) return NULL;

	arrecife_t* arrecife = malloc(sizeof(arrecife_t));
	if (arrecife == NULL){
		printf(F_ROJO L_NEGRO "No se pudo reservar memoria para el arrecife." DEFAULT "\n");
		fclose(arch_arrecife);
		return NULL;
	}

	(*arrecife).cantidad_pokemon = 0;
	(*arrecife).pokemon = NULL;

	pokemon_t pokemon;
	int leidos = fscanf(arch_arrecife, FORMATO_R_POKEMON, pokemon.especie, &(pokemon.velocidad), &(pokemon.peso), pokemon.color);
	bool hay_error = false;

	while ( (leidos == UN_POKEMON) && !hay_error){

		pokemon_t* pokemon_aux = agregar_pokemon((*arrecife).pokemon, pokemon, (*arrecife).cantidad_pokemon);

		if (pokemon_aux != NULL){
			(*arrecife).pokemon = pokemon_aux;
			(*arrecife).cantidad_pokemon+= 1;
			leidos = fscanf(arch_arrecife, FORMATO_R_POKEMON, pokemon.especie, &(pokemon.velocidad), &(pokemon.peso), pokemon.color);
		}
		else {
			hay_error = true;
		}
	}

	if ((*arrecife).cantidad_pokemon == 0){
		printf(F_ROJO L_NEGRO "No se pudieron agregar los pokemones en el arrecife." DEFAULT "\n");
		fclose(arch_arrecife);
		free(arrecife);
		return NULL;
	}

	fclose(arch_arrecife);
	return arrecife;
}

/* es una funcion publica, corroborar la biblioteca correspondiente */
acuario_t* crear_acuario(){
	acuario_t* acuario = malloc(sizeof(acuario_t));
	
	if (acuario == NULL){
		printf(F_ROJO L_NEGRO "No se pudo crear el acuario." DEFAULT "\n");
		return NULL;
	}
	
	(*acuario).pokemon = NULL;
	(*acuario).cantidad_pokemon = 0;

	return acuario;
}

/*Procedimiento que recorre el vector de pokemones reacomodando las posiciones para realizar la eliminacion
 *Recibe un puntero al vector de struct pokemon_t, el tope del vector y la posicion a eliminar (todos valores inicializados).
 *Devuelve el vector actualizado.
 */
void eliminar_ordenadamente(pokemon_t* vector_pokemones, int tope_vector, int pos_a_eliminar){

	for (int i = pos_a_eliminar; i < (tope_vector - 1); i++) vector_pokemones[i] = vector_pokemones[i + 1];
}

/*Funcion que elimina ordenadamente 1 elemento del vector de pokemones y disminuye su tamaño en la memoria dinamica.
 *Recibe un puntero a struct arrecife inicializado y la posicion a eliminar (debe ser mayor a cero y menor al tope del vector).
 *Devuelve un puntero a un nuevo vector de pokemones actualizado.
 */
pokemon_t* disminuir_arrecife(arrecife_t* arrecife, int pos_a_eliminar){

	eliminar_ordenadamente((*arrecife).pokemon, (*arrecife).cantidad_pokemon, pos_a_eliminar);

	int nuevo_tam = (*arrecife).cantidad_pokemon - 1;

	pokemon_t* pokemon_aux = realloc((*arrecife).pokemon, (size_t)nuevo_tam*sizeof(pokemon_t));
	
	if ( (pokemon_aux == NULL) && (nuevo_tam != 0) ) return NULL;

	return pokemon_aux;
}

/* es una funcion publica, corroborar la biblioteca correspondiente */
int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
	
	bool hay_error = false;
	int max_vector = (*arrecife).cantidad_pokemon;
	int vector_posiciones[max_vector];
	int tope_vector = 0;

	if ((*arrecife).pokemon == NULL){
		printf(F_ROJO L_NEGRO "Arrecife vacio o invalido." DEFAULT "\n");
		return ERROR;
	}
	if ((*arrecife).cantidad_pokemon <= 0){
		printf(F_ROJO L_NEGRO "No hay pokemones en el arrecife." DEFAULT "\n");
		return ERROR;
	}
	if ((*arrecife).cantidad_pokemon < cant_seleccion){
		printf(F_ROJO L_NEGRO "No se pudo trasladar, arrecife a punto de vaciarse." DEFAULT "\n");
		return ERROR;
	}

	int i = 0;
	int j = 0;
	while ( (i < (*arrecife).cantidad_pokemon) && (j < cant_seleccion) ){

		if (seleccionar_pokemon( &((*arrecife).pokemon[i]) ) == true){
			vector_posiciones[tope_vector] = i;
			tope_vector+= 1;
			j++;
		}
		i++;
	}

	if (tope_vector < cant_seleccion){
		printf(F_ROJO L_NEGRO "No hay cantidad suficientes de pokemones solicitados." DEFAULT "\n");
		hay_error = true;
	}
	else {
		int i = 0;
		while ( (i < cant_seleccion) && (!hay_error) ){
			
			(*acuario).pokemon = agregar_pokemon((*acuario).pokemon, (*arrecife).pokemon[vector_posiciones[i]],
				(*acuario).cantidad_pokemon);

			if ((*acuario).pokemon == NULL){
				printf(F_ROJO L_NEGRO "No se pudo agregar el pokemon al acuario." DEFAULT "\n");
				hay_error = true;
			}

			(*acuario).cantidad_pokemon+= 1;
			i++;
		}
		
		i = 0;
		for (int j = 0; j < tope_vector; j++){
			(*arrecife).pokemon = disminuir_arrecife(arrecife, vector_posiciones[j] - i);
			(*arrecife).cantidad_pokemon-= 1;
			i++;
		}
	
		if ( ((*arrecife).pokemon == NULL) && ((*arrecife).cantidad_pokemon != 0)){
			printf(F_ROJO L_NEGRO "No se pudo disminuir el arrecife.\n" DEFAULT);
			hay_error = true;
		}
	}

	if (hay_error) return ERROR;

	return EXITO;
}

/* es una funcion publica, corroborar la biblioteca correspondiente */
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
	
	for (int i = 0; i < (*arrecife).cantidad_pokemon; i++) mostrar_pokemon( &((*arrecife).pokemon[i]) );
}

/* es una funcion publica, corroborar la biblioteca correspondiente */
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	
	FILE* arch_acuario = fopen(nombre_archivo, "w");
	if (!arch_acuario){
		printf(F_ROJO L_NEGRO "No se pudo crear el archivo de acuario." DEFAULT "\n");
		return ERROR;
	}

	if ((*acuario).pokemon == NULL){
		fclose(arch_acuario);
		return EXITO;
	}

	for (int i = 0; i < (*acuario).cantidad_pokemon; i++){

		fprintf(arch_acuario, FORMATO_W_POKEMON, (*acuario).pokemon[i].especie, (*acuario).pokemon[i].velocidad,
			(*acuario).pokemon[i].peso, (*acuario).pokemon[i].color);
	}

	fclose(arch_acuario);
	return EXITO;
}

/* es una funcion publica, corroborar la biblioteca correspondiente */
void liberar_acuario(acuario_t* acuario){
	
	if ((*acuario).pokemon != NULL) free((*acuario).pokemon);
	
	free(acuario);
}

/* es una funcion publica, corroborar la biblioteca correspondiente */
void liberar_arrecife(arrecife_t* arrecife){
	
	if ((*arrecife).pokemon != NULL) free((*arrecife).pokemon);
	
	free(arrecife);
}