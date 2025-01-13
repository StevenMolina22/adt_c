#include "cola.h"

Cola *cola_crear()
{
	return (Cola *)list_new();
}

void cola_destruir(Cola *cola)
{
	list_destroy((List *)cola);
}

void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	list_destroy_all((List *)cola, f);
}

// cada una de estas funciones es O(1)
size_t cola_cantidad(Cola *cola)
{
	return list_size((List *)cola);
}

void *cola_frente(Cola *cola)
{
	if (list_size((List *)cola) == 0)
		return NULL;
	void *found = NULL;
	list_get((List *)cola, 0, &found);
	return found;
}

bool cola_encolar(Cola *cola, void *data)
{
	return list_append((List *)cola, data);
}

void *cola_desencolar(Cola *cola)
{
	if (list_size((List *)cola) == 0)
		return NULL;
	void *removido = NULL;
	list_remove((List *)cola, 0, &removido);
	return removido;
}

bool cola_esta_vacía(Cola *cola)
{
	return list_size((List *)cola) == 0;
}
