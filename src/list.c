#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/lista.h"
#include "list/pokemon.h"
#include "utils/csv.h"

int obtener_opcion_usuario(void)
{
    printf("Linked List POKE\n");
	printf("\t1. Buscar pokemon\n");
	printf("\t2. Listar todos los pokemones\n");
	printf("Ingrese una opcion: ");

	int opcion;
	if (scanf("%d", &opcion) != 1) {
		printf("Opcion invalida\n");
		return ERROR;
	}
	return opcion;
}

int main(int argc, char *argv[])
{
	// ----- ABRIR ARCHIVO -----
	if (argc != 2) {
		printf("Uso: %s <archivo.csv>\n", argv[0]);
		return ERROR;
	}

	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], DELIMITADOR);
	if (!archivo) {
		printf("Archivo inexistente");
		return ERROR;
	}

	// ----- CREAR POKEDEX -----
	List *pokedex = list_new();
	if (!pokedex) {
		printf("Error al crear la lista\n");
		cerrar_archivo_csv(archivo);
		return ERROR;
	}

	// ----- ANADIR A POKEDEX -----
	if (!agregar_pokemones(archivo, pokedex)) {
		cerrar_archivo_csv(archivo);
		list_destroy(pokedex);
		return ERROR;
	}
	cerrar_archivo_csv(archivo);

	// ----- OPCION USUARIO -----
	int opcion = obtener_opcion_usuario();
	if (opcion == ERROR) {
		list_destroy_all(pokedex, liberar_pokemon);
		return ERROR;
	}

	switch (opcion) {
	case 1:
		buscar_pokemon(pokedex);
		break;
	case 2:
		list_map(pokedex, print_pokemon, NULL);
		break;
	default:
		printf("Opcion invalida\n");
		list_destroy_all(pokedex, liberar_pokemon);
		return ERROR;
	}

	list_destroy_all(pokedex, liberar_pokemon);
	return 0;
}
