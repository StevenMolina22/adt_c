#ifndef POKEMON_H
#define POKEMON_H

#include <stdbool.h>
#include "lista.h"
#include "../utils/io_utils.h"
#include "../utils/csv.h"

#define ERROR -1
#define DELIMITADOR ';'
#define N_COLUMNAS 5

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

struct pokemon *leer_pokemon(struct archivo_csv *archivo);
bool agregar_pokemones(struct archivo_csv *archivo, List *pokedex);
void liberar_pokemon(void *pokemon);
int comparar_nombre_pokemon(void *pokemon1, void *pokemon2);
bool print_pokemon(void *pokemon, void *ctx);
void buscar_pokemon(List *pokedex);

#endif // POKEMON_H
