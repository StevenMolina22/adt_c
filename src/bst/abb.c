#include "abb.h"
#include "abb_estructura_privada.h"

// ----- FUNCIONES AUXILIARES -----
nodo_t *nodo_crear(void *elemento)
{
	nodo_t *nodo = calloc(sizeof(nodo_t), 1);
	if (!nodo)
		return NULL;
	nodo->elemento = elemento;
	return nodo;
}

static nodo_t *buscar_predecesor_inorden(nodo_t *nodo)
{
	while (nodo->der)
		nodo = nodo->der;
	return nodo;
}

// ----- FIN FUNCIONES AUXILIARES
static nodo_t *nodo_buscar(nodo_t *nodo, void *elemento,
			   int (*fn_cmp)(void *, void *), nodo_t **padre)
{
	if (!nodo || !fn_cmp) {
    	return NULL;
	} else if (padre) {
    	*padre = nodo;
	}

	int cmp = fn_cmp(elemento, nodo->elemento);
	if (cmp > 0) {
    	return nodo_buscar(nodo->der, elemento, fn_cmp, padre);
	} else if (cmp < 0) {
		return nodo_buscar(nodo->izq, elemento, fn_cmp, padre);
	} else {
    	return nodo;
	}
}

static nodo_t *nodo_insertar(abb_t *abb, nodo_t *nodo, void *elemento)
{
	if (!nodo) {
		nodo_t *nuevo = nodo_crear(elemento);
		if (nuevo)
			abb->nodos++;
		return nuevo;
	}

	if (!abb->comparador)
		return NULL;
	int cmp = abb->comparador(elemento, nodo->elemento);
	if (cmp > 0) {
		nodo->der = nodo_insertar(abb, nodo->der, elemento);
	} else {
		nodo->izq = nodo_insertar(abb, nodo->izq, elemento);
	}
	return nodo;
}

static nodo_t *nodo_quitar_un_hijo(nodo_t *nodo)
{
	// Funcion asume que nodo existe y tiene un solo hijo
	nodo_t *temp = (nodo->izq) ? nodo->izq : nodo->der;
	free(nodo);
	return temp;
}

static nodo_t *nodo_quitar(abb_t *abb, nodo_t *node, void *data, bool *is_removed, void **found)
{
	if (!node || !abb->comparador) {
		*is_removed = false;
		return NULL;
	}
	int cmp = abb->comparador(data, node->elemento);
	if (cmp > 0) { // Buscar en subarbol derecho
		node->der = nodo_quitar(abb, node->der, data, is_removed,
					found);
	} else if (cmp < 0) { // Buscar en subarbol izquierdo
		node->izq = nodo_quitar(abb, node->izq, data, is_removed,
					found);
	} else { // Nodo encontrado
		if (found) {
    		*found = node->elemento;
		}
		*is_removed = true;

		if (!node->izq && !node->der) {
			free(node);
			return NULL;
		}

		if (!node->izq || !node->der) {
    		return nodo_quitar_un_hijo(node);
		}

		// Caso: Nodo con dos hijos
		nodo_t *max_nodo = buscar_predecesor_inorden(node->izq);
		void *temp = node->elemento;
		node->elemento = max_nodo->elemento;
		max_nodo->elemento = temp;
		node->izq = nodo_quitar(abb, node->izq, max_nodo->elemento,
					is_removed, &max_nodo->elemento);
	}
	return node;
}

// ----- FUNCIONES DEL ABB -----
bool abb_insertar(abb_t *abb, void *elemento)
{
	if (!abb)
		return false;

	size_t nodos_iniciales = abb->nodos;
	abb->raiz = nodo_insertar(abb, abb->raiz, elemento);

	return abb->nodos > nodos_iniciales;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (!abb) {
		return false;
	}
	bool removido = false;
	abb->raiz = nodo_quitar(abb, abb->raiz, buscado, &removido, encontrado);
	if (removido) {
		abb->nodos--;
	}
	return removido;
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (!abb || !elemento)
		return NULL;
	nodo_t *nodo = nodo_buscar(abb->raiz, elemento, abb->comparador, NULL);
	return nodo ? nodo->elemento : NULL;
}

size_t abb_cantidad(abb_t *abb)
{
	return abb ? abb->nodos : 0;
}
