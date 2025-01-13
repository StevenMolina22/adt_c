#include <stdio.h>
#include "bst/abb.h"
#include "pa2m.h"

// ----- FUNCIONES AUXILIARES
int comparador_int(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

void destructor_int(void *elemento)
{
	free(elemento);
}

bool imprimir_elemento(void *elemento, void *ctx)
{
	printf("%d ", *(int *)elemento);
	return true;
}

bool contar_elemento(void *elemento, void *contador)
{
	(*(int *)contador)++;
	return true;
}

bool sumar_elementos(void *elemento, void *suma)
{
	*(int *)suma += *(int *)elemento;
	return true;
}

// ----- PRUEBAS CREAR
void prueba_crear_abb()
{
	BST *abb = bst_new(comparador_int);
	pa2m_afirmar(abb != NULL, "Se puede crear un ABB");
	bst_destroy(abb);
}

// ----- PRUEBAS DESTRUIR
void destruir_abb_vacio_no_rompe()
{
	BST *abb = bst_new(comparador_int);
	bst_destroy(abb);
	pa2m_afirmar(true, "Destruir un ABB vacío no produce errores");
}

void destruir_abb_con_elementos_no_rompe()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 20;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);

	bst_destroy(abb);
	pa2m_afirmar(true, "Destruir un ABB con elementos no produce errores");
}

void destruir_abb_con_elementos_y_funcion_destructora()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	*elemento1 = 10;
	*elemento2 = 20;

	bst_insert(abb, elemento1);
	bst_insert(abb, elemento2);

	bst_destroy_all(abb, destructor_int);
	pa2m_afirmar(
		true,
		"Destruir un ABB con función destructora libera la memoria de los elementos");
}

// ----- INSERTAR
void insertar_elementos_devuelve_cantidad_correcta()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	*elemento1 = 10, *elemento2 = 20, *elemento3 = 5;

	pa2m_afirmar(bst_insert(abb, elemento1),
		     "Se puede insertar el elemento 10");
	pa2m_afirmar(bst_insert(abb, elemento2),
		     "Se puede insertar el elemento 20");
	pa2m_afirmar(bst_insert(abb, elemento3),
		     "Se puede insertar el elemento 5");

	pa2m_afirmar(bst_size(abb) == 3, "El ABB tiene 3 elementos");

	bst_destroy_all(abb, destructor_int);
}

void insertar_elementos_en_orden_diferente()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	*elemento1 = 20, *elemento2 = 10, *elemento3 = 30;

	pa2m_afirmar(bst_insert(abb, elemento1),
		     "Se puede insertar el elemento 20");
	pa2m_afirmar(bst_insert(abb, elemento2),
		     "Se puede insertar el elemento 10");
	pa2m_afirmar(bst_insert(abb, elemento3),
		     "Se puede insertar el elemento 30");

	pa2m_afirmar(bst_size(abb) == 3, "El ABB tiene 3 elementos");

	bst_destroy_all(abb, destructor_int);
}

void insertar_elementos_duplicados()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	*elemento1 = 10, *elemento2 = 10;

	pa2m_afirmar(bst_insert(abb, elemento1),
		     "Se puede insertar el elemento 10");
	pa2m_afirmar(bst_insert(abb, elemento2),
		     "Se puede insertar el elemento 10 duplicado");

	pa2m_afirmar(bst_size(abb) == 2, "El ABB tiene 2 elemento");

	bst_destroy_all(abb, destructor_int);
}

void insertar_multiples_elementos()
{
	BST *abb = bst_new(comparador_int);
	int elementos[10];
	for (int i = 0; i < 10; i++) {
		elementos[i] = i;
		pa2m_afirmar(bst_insert(abb, &elementos[i]),
			     "Se puede insertar el elemento");
	}

	pa2m_afirmar(bst_size(abb) == 10, "El ABB tiene 10 elementos");

	bst_destroy(abb);
}

// ----- QUITAR
void quitar_elementos_da_resultados_correctos()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	*elemento1 = 10, *elemento2 = 20, *elemento3 = 5,

	bst_insert(abb, elemento1);
	bst_insert(abb, elemento2);
	bst_insert(abb, elemento3);

	int *encontrado = NULL;
	pa2m_afirmar(bst_remove(abb, elemento1, (void **)&encontrado),
		     "Se puede quitar el elemento 10");
	pa2m_afirmar(encontrado == elemento1,
		     "El elemento quitado es el correcto");
	free(encontrado);

	pa2m_afirmar(bst_size(abb) == 2,
		     "El ABB tiene 2 elementos después de quitar uno");

	bst_destroy_all(abb, destructor_int);
}

void quitar_en_arbol_vacio_devuelve_false()
{
	BST *abb = bst_new(comparador_int);
	int elemento = 10;
	void *encontrado = NULL;
	pa2m_afirmar(bst_remove(abb, &elemento, &encontrado) == false,
		     "No se puede quitar de un árbol vacío");
	pa2m_afirmar(encontrado == NULL, "El elemento no se encontró");
	bst_destroy(abb);
}

void quitar_unico_elemento_resultado_correcto()
{
	BST *abb = bst_new(comparador_int);
	int elemento = 10;
	bst_insert(abb, &elemento);
	void *encontrado = NULL;
	pa2m_afirmar(bst_remove(abb, &elemento, &encontrado) == true,
		     "Se puede quitar la raíz");
	pa2m_afirmar(encontrado == &elemento,
		     "El elemento quitado es el correcto");
	pa2m_afirmar(bst_size(abb) == 0, "El árbol quedó vacío");
	bst_destroy(abb);
}

void quitar_hoja_resultado_correcto()
{
	BST *abb = bst_new(comparador_int);
	int elem1 = 20, elem2 = 10;
	bst_insert(abb, &elem1);
	bst_insert(abb, &elem2); // Insertar hoja
	void *encontrado = NULL;
	pa2m_afirmar(bst_remove(abb, &elem2, &encontrado) == true,
		     "Se puede quitar una hoja");
	pa2m_afirmar(encontrado == &elem2,
		     "Hoja quitada devuelta es la correcta");
	pa2m_afirmar(bst_size(abb) == 1,
		     "La cantidad de elementos es la correcta");
	bst_destroy(abb);
}

void quitar_nodo_con_un_hijo()
{
	BST *abb = bst_new(comparador_int);
	int elem1 = 20, elem2 = 10, elem3 = 5;
	bst_insert(abb, &elem1);
	bst_insert(abb, &elem2);
	bst_insert(abb, &elem3); // Nodo con un solo hijo
	void *encontrado = NULL;
	pa2m_afirmar(bst_remove(abb, &elem2, &encontrado) == true,
		     "Se puede quitar un nodo con un solo hijo");
	pa2m_afirmar(encontrado == &elem2,
		     "El elemento quitado es devuelto correctamente");
	pa2m_afirmar(bst_size(abb) == 2,
		     "Cantidad de elementos es correcta");
	bst_destroy(abb);
}

void quitar_nodo_con_dos_hijos()
{
	BST *abb = bst_new(comparador_int);
	int elem1 = 20, elem2 = 10, elem3 = 30, elem4 = 5, elem5 = 15;
	bst_insert(abb, &elem1);
	bst_insert(abb, &elem2);
	bst_insert(abb, &elem3);
	bst_insert(abb, &elem4);
	bst_insert(abb, &elem5); // Nodo con dos hijos
	void *encontrado = NULL;
	pa2m_afirmar(bst_remove(abb, &elem2, &encontrado) == true,
		     "Se puede quitar un nodo con dos hijos");
	pa2m_afirmar(encontrado == &elem2,
		     "Elemento quitado es devuelto correctamente");
	pa2m_afirmar(bst_size(abb) == 4,
		     "Cantidad de elementos es la correcta");
	bst_destroy(abb);
}

// ----- OBTENER
void obtener_elementos_devuelve_resultados_correctos()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	*elemento1 = 10, *elemento2 = 20, *elemento3 = 5;

	bst_insert(abb, elemento1);
	bst_insert(abb, elemento2);
	bst_insert(abb, elemento3);

	pa2m_afirmar(bst_get(abb, elemento1) == elemento1,
		     "Se puede obtener el elemento 10");
	pa2m_afirmar(bst_get(abb, elemento2) == elemento2,
		     "Se puede obtener el elemento 20");
	pa2m_afirmar(bst_get(abb, elemento3) == elemento3,
		     "Se puede obtener el elemento 5");

	bst_destroy_all(abb, destructor_int);
}

void obtener_elemento_inexistente_devuelve_null()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10, elemento2 = 20;
	int elemento_inexistente = 15;

	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);

	pa2m_afirmar(bst_get(abb, &elemento_inexistente) == NULL,
		     "Obtener un elemento inexistente devuelve NULL");

	bst_destroy(abb);
}

void obtener_en_arbol_vacio_devuelve_null()
{
	BST *abb = bst_new(comparador_int);
	int elemento = 10;

	pa2m_afirmar(bst_get(abb, &elemento) == NULL,
		     "Obtener en un árbol vacío devuelve NULL");

	bst_destroy(abb);
}

void obtener_elemento_en_raiz()
{
	BST *abb = bst_new(comparador_int);
	int elemento = 10;

	bst_insert(abb, &elemento);

	pa2m_afirmar(bst_get(abb, &elemento) == &elemento,
		     "Se puede obtener el elemento en la raíz");

	bst_destroy(abb);
}

void obtener_elemento_en_hoja()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 20, elemento2 = 10, elemento3 = 30;

	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	pa2m_afirmar(bst_get(abb, &elemento3) == &elemento3,
		     "Se puede obtener un elemento en una hoja");

	bst_destroy(abb);
}

void obtener_elemento_interno()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 20, elemento2 = 10, elemento3 = 30, elemento4 = 15;

	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);
	bst_insert(abb, &elemento4);

	pa2m_afirmar(bst_get(abb, &elemento2) == &elemento2,
		     "Se puede obtener un elemento interno del árbol");

	bst_destroy(abb);
}

// ----- ITERADORES
void iterar_elementos_muestra_elementos()
{
	BST *abb = bst_new(comparador_int);
	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	*elemento1 = 10, *elemento2 = 20, *elemento3 = 5;

	bst_insert(abb, elemento1);
	bst_insert(abb, elemento2);
	bst_insert(abb, elemento3);

	printf("Elementos en orden: ");
	bst_map_inorder(abb, imprimir_elemento, NULL);
	printf("\n");

	bst_destroy_all(abb, destructor_int);
}

void iterar_inorden_aplica_funcion_correctamente()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	int suma = 0;
	bst_map_inorder(abb, sumar_elementos, &suma);

	pa2m_afirmar(suma == 30,
		     "La suma de los elementos inorden es correcta");
	bst_destroy(abb);
}

void iterar_preorden_aplica_funcion_correctamente()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	int suma = 0;
	bst_map_preorder(abb, sumar_elementos, &suma);

	pa2m_afirmar(suma == 30,
		     "La suma de los elementos preorden es correcta");
	bst_destroy(abb);
}

void iterar_postorden_aplica_funcion_correctamente()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	int suma = 0;
	bst_map_postorder(abb, sumar_elementos, &suma);

	pa2m_afirmar(suma == 30,
		     "La suma de los elementos postorden es correcta");
	bst_destroy(abb);
}

// ----- VECTORIZADOR
void vectorizar_inorden_guarda_en_vector_correctamente()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	void *vector[3];
	size_t cantidad = bst_tovec_inorder(abb, vector, 3);

	pa2m_afirmar(cantidad == 3,
		     "Vectorizar inorden guarda todos los elementos");
	pa2m_afirmar(*(int *)vector[0] == 5, "El primer elemento es correcto");
	pa2m_afirmar(*(int *)vector[1] == 10,
		     "El segundo elemento es correcto");
	pa2m_afirmar(*(int *)vector[2] == 15, "El tercer elemento es correcto");

	bst_destroy(abb);
}

void vectorizar_preorden_guarda_en_vector_correctamente()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	void *vector[3];
	size_t cantidad = bst_tovec_preorder(abb, vector, 3);

	pa2m_afirmar(cantidad == 3,
		     "Vectorizar preorden guarda todos los elementos");
	pa2m_afirmar(*(int *)vector[0] == 10, "El primer elemento es correcto");
	pa2m_afirmar(*(int *)vector[1] == 5, "El segundo elemento es correcto");
	pa2m_afirmar(*(int *)vector[2] == 15, "El tercer elemento es correcto");

	bst_destroy(abb);
}

void vectorizar_postorden_guarda_en_vector_correctamente()
{
	BST *abb = bst_new(comparador_int);
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	bst_insert(abb, &elemento1);
	bst_insert(abb, &elemento2);
	bst_insert(abb, &elemento3);

	void *vector[3];
	size_t cantidad = bst_tovec_postorder(abb, vector, 3);

	pa2m_afirmar(cantidad == 3,
		     "Vectorizar postorden guarda todos los elementos");
	pa2m_afirmar(*(int *)vector[0] == 5, "El primer elemento es correcto");
	pa2m_afirmar(*(int *)vector[1] == 15,
		     "El segundo elemento es correcto");
	pa2m_afirmar(*(int *)vector[2] == 10, "El tercer elemento es correcto");

	bst_destroy(abb);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");
	prueba_crear_abb();

	// INSERTAR
	pa2m_nuevo_grupo("Pruebas funcion insertar");
	insertar_elementos_devuelve_cantidad_correcta();
	insertar_elementos_en_orden_diferente();
	insertar_elementos_duplicados();
	insertar_multiples_elementos();

	// QUITAR
	pa2m_nuevo_grupo("Pruebas funcion quitar");
	quitar_elementos_da_resultados_correctos();
	quitar_en_arbol_vacio_devuelve_false();
	quitar_hoja_resultado_correcto();
	quitar_nodo_con_un_hijo();
	quitar_nodo_con_dos_hijos();

	// OBTENER
	pa2m_nuevo_grupo("Pruebas funcion obtener");
	obtener_elementos_devuelve_resultados_correctos();
	obtener_elemento_inexistente_devuelve_null();
	obtener_en_arbol_vacio_devuelve_null();
	obtener_elemento_en_raiz();
	obtener_elemento_en_hoja();
	obtener_elemento_interno();

	// DESTRUIR
	pa2m_nuevo_grupo("Pruebas funcion destruir");
	destruir_abb_vacio_no_rompe();
	destruir_abb_con_elementos_no_rompe();
	destruir_abb_con_elementos_y_funcion_destructora();

	// ITERAR
	pa2m_nuevo_grupo("Pruebas de iteración");
	iterar_inorden_aplica_funcion_correctamente();
	iterar_preorden_aplica_funcion_correctamente();
	iterar_postorden_aplica_funcion_correctamente();

	// VECTORIZAR
	pa2m_nuevo_grupo("Pruebas de vectorización");
	vectorizar_inorden_guarda_en_vector_correctamente();
	vectorizar_preorden_guarda_en_vector_correctamente();
	vectorizar_postorden_guarda_en_vector_correctamente();

	return pa2m_mostrar_reporte();
}
