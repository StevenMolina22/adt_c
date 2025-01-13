#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct list List;
typedef struct lista_iterador Lista_iterador;

List *list_new();
void list_destroy(List *);

/**
 * Destruye la lista aplicando la funcion destructora (si no es NULL) a cada elemento.
 * */
void list_destroy_all(List *, void (*destructor)(void *));

/*
 * Devuelve la cantidad de elementos de la lista.
 * Una lista NULL tiene 0 elementos.
 */
size_t list_size(List *);

/**
 * Inserta un elemento en la lista en la posicion dada.
 *
 * Si la posición es mayor a la cantidad de elementos, es un error.
 *
 * Devuelve true si pudo, false en caso de error.
 *
 */
bool list_insert(List *list, size_t posicion, void *cosa);

/**
  * Inserta un elemento al final de la lista.
  */
bool list_append(List *list, void *cosa);

/**
 * Elimina un elemento de la posicion dada.
 *
 * El elemento quitado se guarda en elemento_quitado (si se puede quitar y si no es null).
 *
 * En caso de error devuelve false, caso contrario true.
 */
bool list_remove(List *list, size_t posicion,
			   void **elemento_quitado);

/**
 * Busca el elemento buscado en la lista y lo devuelve si lo encuentra.
 *
 * Para buscar el elemento, se aplica la función de comparacion.
 *
 * En caso de no encontrarlo devuelve NULL.
 */
void *list_search(List *list, void *buscado,
			    int (*comparador)(void *, void *));

/**
 * Obtiene el elemento almacenado en una posición
 *
 * Si la posicion es inválida es un error.
 *
 * El elemento encontrado se almacena en elemento_encontrado (a menos que sea NULL);
 *
 * Devuelve true si pudo obtener el elemento o false en caso de error.
 */
bool list_get(List *list, size_t posicion,
			    void **elemento_encontrado);

/**
 * Recorre la lista aplicando la funcion f a cada elemento en orden.
 *
 * ctx se le pasa como segundo parámetro a f.
 *
 * Si la funcion devuelve true se debe seguir iterando, caso contrario no.
 *
 * Devuelve la cantidad de elementos iterados.
 * */
size_t list_map(List *list, bool (*f)(void *, void *),
			      void *ctx);

/**
 * Crea un iterador externo para una lista
 *
 * En caso de error devuelve NULL
 */
Lista_iterador *l_iter_new(List *list);

/**
 * Devuelve true si hay siguiente.
 */
bool l_iter_has_next(Lista_iterador *);

/**
 *
 * Hace que el iterador avance al siguiente elemento de la lista.
 *
 */
void l_iter_next(Lista_iterador *);

/**
 * Devuelve el elemento iterado
 */
void *l_iter_get(Lista_iterador *);

/**
 * Eso
 */
void l_iter_destroy(Lista_iterador *);

#endif /* LISTA_H */
