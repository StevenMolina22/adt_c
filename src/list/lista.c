#include "lista.h"
#include <stdio.h>

typedef struct Nodo {
	void *data;
	struct Nodo *siguiente;
} Node;

struct list {
	size_t cantidad;
	Node *frente;
	Node *fondo;
};

struct lista_iterador {
	Node *actual;
};

List *list_new()
{
	List *lista = malloc(sizeof(List));
	if (!lista)
		return NULL;
	lista->cantidad = 0;
	lista->fondo = NULL;
	lista->frente = NULL;
	return lista;
}

void list_destroy(List *lista)
{
	if (!lista)
		return;
	Node *nodo = lista->frente;
	while (nodo != NULL) {
		Node *temp = nodo;
		nodo = nodo->siguiente;
		free(temp);
	}
	free(lista);
}

void list_destroy_all(List *lista, void (*destructor)(void *))
{
	if (!lista)
		return;
	Node *nodo = lista->frente;
	while (nodo != NULL) {
		if (destructor)
			destructor(nodo->data);
		Node *temp = nodo;
		nodo = nodo->siguiente;
		free(temp);
	}
	free(lista);
}

size_t list_size(List *lista)
{
	if (!lista)
		return 0;
	return lista->cantidad;
}

bool list_insert(List *lista, size_t idx, void *data)
{
	// Invalido
	if (!lista || idx > lista->cantidad)
		return false;
	Node *nuevo = malloc(sizeof(Node));
	if (!nuevo)
		return false;
	nuevo->data = data;
	nuevo->siguiente = NULL;

	if (idx == 0) {
		nuevo->siguiente = lista->frente;
		lista->frente = nuevo;
		if (lista->cantidad == 0)
			lista->fondo = nuevo;
	} else {
		Node *nodo = lista->frente;
		for (int i = 0; i < idx - 1; i++) {
			nodo = nodo->siguiente;
		}

		nuevo->siguiente = nodo->siguiente;
		nodo->siguiente = nuevo;
		if (idx == lista->cantidad)
			lista->fondo = nuevo;
	}
	lista->cantidad++;
	return true;
}

bool list_append(List *lista, void *item)
{
	if (!lista)
		return false;
	Node *nuevo_nodo = malloc(sizeof(Node));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->data = item;
	nuevo_nodo->siguiente = NULL;
	if (!lista->frente)
		lista->frente = nuevo_nodo;

	if (lista->fondo)
		lista->fondo->siguiente = nuevo_nodo;
	lista->fondo = nuevo_nodo;

	lista->cantidad++;
	return true;
}

// Helper function for removal funcs
bool remover_nodo(List *lista, Node *nodo, void **removido)
{
	if (removido) {
		*removido = nodo->data;
	}
	free(nodo);
	lista->cantidad--;
	return true;
}

// ----- Funciones auxiliares para remover -----
// Funcion auxiliar
bool remover_frente(List *lista, void **removido)
{
	Node *nodo = lista->frente;
	lista->frente = nodo->siguiente;
	if (lista->cantidad == 1) {
		lista->fondo = NULL;
	}
	return remover_nodo(lista, nodo, removido);
}

// Funcion auxiliar
bool remover_fondo(List *lista, void **removido)
{
	Node *nodo = lista->fondo;
	Node *previo = lista->frente;
	while (previo->siguiente != nodo) {
		previo = previo->siguiente;
	}
	lista->fondo = previo;
	lista->fondo->siguiente = NULL;
	return remover_nodo(lista, nodo, removido);
}

// Funcion auxiliar
bool remover_mitad(List *lista, size_t idx, void **removido)
{
	Node *previo = lista->frente;
	for (size_t i = 0; i < idx - 1; i++) {
		previo = previo->siguiente;
	}
	Node *nodo = previo->siguiente;
	previo->siguiente = nodo->siguiente;
	if (idx == lista->cantidad - 1) {
		lista->fondo = previo;
	}
	return remover_nodo(lista, nodo, removido);
}

// Remover principal
bool list_remove(List *lista, size_t idx, void **removido)
{
	if (!lista || idx >= lista->cantidad)
		return false;

	if (idx == 0) {
		return remover_frente(lista, removido);
	} else if (idx == lista->cantidad - 1) {
		return remover_fondo(lista, removido);
	} else {
		return remover_mitad(lista, idx, removido);
	}
}

void *list_search(List *lista, void *target,
			    int (*cmp)(void *, void *))
{
	if (!lista || !cmp)
		return NULL;
	Node *nodo = lista->frente;
	while (nodo != NULL) {
		if (cmp(target, nodo->data) == 0)
			return nodo->data;
		nodo = nodo->siguiente;
	}
	return NULL;
}

bool list_get(List *lista, size_t idx, void **encontrado)
{
	if (!lista || idx >= lista->cantidad)
		return false;

	Node *actual = lista->frente;
	for (size_t i = 0; i < idx; i++) {
		actual = actual->siguiente;
	}

	if (encontrado)
		*encontrado = actual->data;
	return true;
}

size_t list_map(List *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (!lista)
		return 0;

	Node *actual = lista->frente;
	size_t i = 0;
	for (i = 0; actual != NULL; i++) {
		if (!f(actual->data, ctx))
			return ++i;
		actual = actual->siguiente;
	}
	return i;
}

Lista_iterador *l_iter_new(List *lista)
{
	if (!lista)
		return NULL;

	Lista_iterador *iter = malloc(sizeof(Lista_iterador));
	iter->actual = lista->frente;
	return iter;
}

bool l_iter_has_next(Lista_iterador *iter)
{
	if (!iter || !iter->actual)
		return false;
	return true;
}

void l_iter_next(Lista_iterador *iter)
{
	if (!iter || !iter->actual)
		return;
	iter->actual = iter->actual->siguiente;
}

void *l_iter_get(Lista_iterador *iter)
{
	if (!iter || !iter->actual)
		return NULL;
	return iter->actual->data;
}

void l_iter_destroy(Lista_iterador *iter)
{
	free(iter);
}
