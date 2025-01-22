#include "cola.h"

Queue *queue_new()
{
	return (Queue *)list_new();
}

void queue_destroy(Queue *cola)
{
	list_destroy((List *)cola);
}

void queue_destroy_all(Queue *cola, void (*f)(void *))
{
	list_destroy_all((List *)cola, f);
}

// cada una de estas funciones es O(1)
size_t queue_size(Queue *cola)
{
	return list_size((List *)cola);
}

void *queue_peek(Queue *cola)
{
	if (list_size((List *)cola) == 0)
		return NULL;
	void *found = NULL;
	list_get((List *)cola, 0, &found);
	return found;
}

bool queue_enqueue(Queue *cola, void *data)
{
	return list_append((List *)cola, data);
}

void *queue_dequeue(Queue *cola)
{
	if (list_size((List *)cola) == 0)
		return NULL;
	void *removido = NULL;
	list_remove((List *)cola, 0, &removido);
	return removido;
}

bool queue_is_empty(Queue *cola)
{
	return list_size((List *)cola) == 0;
}
