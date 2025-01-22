#ifndef COLA_H_
#define COLA_H_

#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

typedef struct cola Queue;

Queue *queue_new();
void queue_destroy(Queue *);
void queue_destroy_all(Queue *, void (*f)(void *));

// cada una de estas funciones es O(1)
size_t queue_size(Queue *);
void *queue_peek(Queue *);
bool queue_enqueue(Queue *, void *);
void *queue_dequeue(Queue *);
bool queue_is_empty(Queue *);

#endif // COLA_H_
