#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

Pila *pila_crear()
{
	return (Pila *)lista_crear();
}

//cada una de estas funciones es O(1)
size_t pila_cantidad(Pila *pila)
{
	return lista_cantidad_elementos((Lista *)pila);
}

void *pila_tope(Pila *pila)
{
	if (!pila || lista_cantidad_elementos((Lista *)pila) == 0)
		return NULL;

	void *element = NULL;
	if (lista_obtener_elemento((Lista *)pila,
				   lista_cantidad_elementos((Lista *)pila) - 1,
				   &element))
		return element;
	return NULL;
}

bool pila_apilar(Pila *pila, void *data)
{
	return lista_agregar_al_final((Lista *)pila, data);
}

void *pila_desapilar(Pila *pila)
{
	if (!pila || lista_cantidad_elementos((Lista *)pila) == 0)
		return NULL;
	void *removed = NULL;
	if (lista_quitar_elemento((Lista *)pila,
				  lista_cantidad_elementos((Lista *)pila) - 1,
				  &removed))
		return removed;
	return NULL;
}

bool pila_esta_vacía(Pila *pila)
{
	return !pila || lista_cantidad_elementos((Lista *)pila) == 0;
}

void pila_destruir(Pila *pila)
{
	lista_destruir((Lista *)pila);
	return;
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	lista_destruir_todo((Lista *)pila, f);
	return;
}
