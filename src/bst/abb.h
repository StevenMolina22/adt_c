#ifndef ABB_H_
#define ABB_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct bst BST;

/**
 * Crea un ABB con un comparador.
 */
BST *bst_new(int (*comparador)(void *, void *));

/**
 * Destruye el abb.
 */
void bst_destroy(BST *abb);

/**
 * Destruye el abb aplicando el destructor a los elementos del usuario.
 */
void bst_destroy_all(BST *abb, void (*destructor)(void *));

/**
 * Inserta el elemento. Devuelve true si pudo o false si no pudo.
 */
bool bst_insert(BST *abb, void *elemento);

/**
 * Quita el elemento buscado del arbol. Si lo encuentra y encontrado no es NULL,
 * almacena el puntero.
 *
 * Devuelve true si pudo quitar el elemento.
 */
bool bst_remove(BST *abb, void *buscado, void **encontrado);

/**
 * Busca un elemento en el abb. Si lo encuentra lo devuelve. Caso contrario
 * devuelve NULL.
 */
void *bst_get(BST *abb, void *elemento);

/**
 * Devuelve la cantidad de elementos en el abb.
 */
size_t bst_size(BST *abb);

/**
 * Recorre los elementos del abb en el orden específico y aplica la función f a
 * cada uno.
 *
 * Si la función f devuelve false, se deja de iterar.
 *
 * Devuelve la cantidad de veces que fue invocada la función f.
 */
size_t bst_map_inorder(BST *abb, bool (*f)(void *, void *), void *ctx);
size_t bst_map_preorder(BST *abb, bool (*f)(void *, void *), void *ctx);
size_t bst_map_postorder(BST *abb, bool (*f)(void *, void *), void *ctx);

/**
 * Rellena el vector de punteros con los elementos del abb siguiendo un orden
 * dado. Tamaño indica la capacidad del vector.
 *
 * Devuelve la cantidad de elementos guardados en el vector.
 */
size_t bst_tovec_inorder(BST *abb, void **vector, size_t tamaño);
size_t bst_tovec_preorder(BST *abb, void **vector, size_t tamaño);
size_t bst_tovec_postorder(BST *abb, void **vector, size_t tamaño);

#endif // ABB_H_
