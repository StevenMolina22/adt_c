#include "abb.h"
#include "abb_estructura_privada.h"

static void nodo_destruir_todo(nodo_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;
	nodo_destruir_todo(nodo->izq, destructor);
	nodo_destruir_todo(nodo->der, destructor);
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
}

BST *bst_new(int (*comparador)(void *, void *))
{
	if (!comparador)
		return NULL;
	BST *abb = calloc(sizeof(BST), 1);
	if (!abb)
		return NULL;
	abb->comparador = comparador;
	return abb;
}

void bst_destroy(BST *abb)
{
	if (!abb)
		return;
	nodo_destruir_todo(abb->raiz, NULL);
	free(abb);
}

void bst_destroy_all(BST *abb, void (*destructor)(void *))
{
	if (!abb)
		return;
	nodo_destruir_todo(abb->raiz, destructor);
	free(abb);
}
