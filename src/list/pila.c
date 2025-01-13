#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

Pila *pila_crear()
{
	return (Pila *)list_new();
}

//cada una de estas funciones es O(1)
size_t pila_cantidad(Pila *pila)
{
	return list_size((List *)pila);
}

void *pila_tope(Pila *pila)
{
    if (!pila || list_size((List *)pila) == 0)
		return NULL;

	void *element = NULL;
	if (list_get((List *)pila,
				   list_size((List *)pila) - 1,
				   &element))
		return element;
	return NULL;
}

bool pila_apilar(Pila *pila, void *data)
{
	return list_append((List *)pila, data);
}

void *pila_desapilar(Pila *pila)
{
    if (!pila || list_size((List *)pila) == 0)
		return NULL;
	void *removed = NULL;
	if (list_remove((List *)pila,
				  list_size((List *)pila) - 1,
				  &removed))
		return removed;
	return NULL;
}

bool pila_esta_vacía(Pila *pila)
{
	return !pila || list_size((List *)pila) == 0;
}

void pila_destruir(Pila *pila)
{
	list_destroy((List *)pila);
	return;
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	list_destroy_all((List *)pila, f);
	return;
}
