#include "abb.h"
#include "abb_estructura_privada.h"

static size_t nodo_iterar_inorden(nodo_t *nodo, bool (*f)(void *, void *),
				  void *ctx, bool *seguir_iterando)
{
	if (!nodo || !f || !*seguir_iterando)
		return 0;
	size_t contador = 0;
	contador += nodo_iterar_inorden(nodo->izq, f, ctx, seguir_iterando);
	if (*seguir_iterando) {
		*seguir_iterando = f(nodo->elemento, ctx);
		contador++;
		if (*seguir_iterando)
			contador += nodo_iterar_inorden(nodo->der, f, ctx,
							seguir_iterando);
	}
	return contador;
}

static size_t nodo_iterar_preorden(nodo_t *nodo, bool (*f)(void *, void *),
				   void *ctx, bool *seguir_iterando)
{
	if (!nodo || !f || !*seguir_iterando)
		return 0;
	size_t contador = 0;
	*seguir_iterando = f(nodo->elemento, ctx);
	contador++;
	if (*seguir_iterando) {
		contador += nodo_iterar_preorden(nodo->izq, f, ctx,
						 seguir_iterando);
		if (*seguir_iterando)
			contador += nodo_iterar_preorden(nodo->der, f, ctx,
							 seguir_iterando);
	}
	return contador;
}

static size_t nodo_iterar_postorden(nodo_t *nodo, bool (*f)(void *, void *),
				    void *ctx, bool *seguir_iterando)
{
	if (!nodo || !f || !*seguir_iterando)
		return 0;
	size_t contador = 0;
	contador += nodo_iterar_postorden(nodo->izq, f, ctx, seguir_iterando);
	if (*seguir_iterando)
		contador += nodo_iterar_postorden(nodo->der, f, ctx,
						  seguir_iterando);
	if (*seguir_iterando) {
		*seguir_iterando = f(nodo->elemento, ctx);
		contador++;
	}
	return contador;
}

size_t bst_map_inorder(BST *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f)
		return 0;
	bool seguir_iterando = true;
	return nodo_iterar_inorden(abb->raiz, f, ctx, &seguir_iterando);
}

size_t bst_map_preorder(BST *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f)
		return 0;
	bool seguir_iterando = true;
	return nodo_iterar_preorden(abb->raiz, f, ctx, &seguir_iterando);
}

size_t bst_map_postorder(BST *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f)
		return 0;
	bool seguir_iterando = true;
	return nodo_iterar_postorden(abb->raiz, f, ctx, &seguir_iterando);
}
