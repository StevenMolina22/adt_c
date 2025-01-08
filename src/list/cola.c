#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"

Cola *cola_crear()
{
	return (Cola *)lista_crear();
}

void cola_destruir(Cola *cola)
{
	lista_destruir((Lista *)cola);
}

void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	lista_destruir_todo((Lista *)cola, f);
}

// cada una de estas funciones es O(1)
size_t cola_cantidad(Cola *cola)
{
	return lista_cantidad_elementos((Lista *)cola);
}

void *cola_frente(Cola *cola)
{
	if (lista_cantidad_elementos((Lista *)cola) == 0)
		return NULL;
	void *found = NULL;
	lista_obtener_elemento((Lista *)cola, 0, &found);
	return found;
}

bool cola_encolar(Cola *cola, void *data)
{
	return lista_agregar_al_final((Lista *)cola, data);
}

void *cola_desencolar(Cola *cola)
{
	if (lista_cantidad_elementos((Lista *)cola) == 0)
		return NULL;
	void *removido = NULL;
	lista_quitar_elemento((Lista *)cola, 0, &removido);
	return removido;
}

bool cola_esta_vacía(Cola *cola)
{
	return lista_cantidad_elementos((Lista *)cola) == 0;
}
