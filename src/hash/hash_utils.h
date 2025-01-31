#ifndef TIPOS_H
#define TIPOS_H

#include "hash.h"

typedef struct entrada {
	char *clave;
	void *valor;
} entrada_t;

typedef struct nodo {
	entrada_t *entrada;
	struct nodo *sig;
	struct nodo *ant;
} nodo_t;

struct hash {
	nodo_t **tabla;
	size_t size;
	size_t cap;
};

size_t hasher(const char *str);
nodo_t *nodo_crear(char *clave, void *valor);
void nodo_destruir(nodo_t *nodo);
nodo_t *encontrar_nodo(Hash *hash, char *clave);
bool agregar_entrada(Hash *hash, char *clave, void *valor);
bool hash_rehash(Hash *hash);
#endif
