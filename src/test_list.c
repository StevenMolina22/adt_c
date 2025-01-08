#include "pa2m.h"
#include "list/cola.h"
#include "list/pila.h"
#include "list/lista.h"

//
// ----- UTILS
int comparar_enteros(void *a, void *b)
{
	return (*(int *)a) - (*(int *)b);
}

bool contar_elementos(void *element, void *count)
{
	(void)element;
	(*(int *)count)++;
	return true;
}

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2 * i == 10, "2*i es igual a 2 (%d)", 2 * i);
}

//
//
//
// ----- TEST PILA
void pila_esta_vacio_al_inicializar()
{
	Pila *stack = pila_crear();
	pa2m_afirmar(pila_esta_vacía(stack),
		     "La pila debe estar vacía al inicializar.");
	pila_destruir(stack);
}

void pila_no_esta_vacia_despues_de_apilar()
{
	Pila *stack = pila_crear();
	int value = 42;
	pila_apilar(stack, &value);
	pa2m_afirmar(!pila_esta_vacía(stack),
		     "La pila no debe estar vacía después de un push.");
	pila_destruir(stack);
}

// Casos borde
void pila_desapilar_pila_vacia()
{
	Pila *stack = pila_crear();
	pa2m_afirmar(pila_desapilar(stack) == NULL,
		     "Pop en una pila vacía debe devolver NULL.");
	pila_destruir(stack);
}

void pila_tope_pila_vacia()
{
	Pila *stack = pila_crear();
	pa2m_afirmar(pila_tope(stack) == NULL,
		     "Peek en una pila vacía debe devolver NULL.");
	pila_destruir(stack);
}

void pila_tamano_pila_nula()
{
	pa2m_afirmar(pila_cantidad(NULL) == 0,
		     "Size de una pila NULL debe ser 0.");
}

void pila_esta_vacia_pila_nula()
{
	pa2m_afirmar(pila_esta_vacía(NULL) == true,
		     "Is_empty en una pila NULL debe devolver true.");
}

void pila_apilar_muchos_elementos()
{
	Pila *stack = pila_crear();
	int values[1000];
	bool success = true;
	for (int i = 0; i < 1000 && success; i++) {
		values[i] = i;
		success = pila_apilar(stack, &values[i]);
	}
	pa2m_afirmar(success && pila_cantidad(stack) == 1000,
		     "Debe poder hacer push de 1000 elementos.");
	pila_destruir(stack);
}

void pila_desapilar_todos_los_elementos()
{
	Pila *stack = pila_crear();
	int values[100];
	for (int i = 0; i < 100; i++) {
		values[i] = i;
		pila_apilar(stack, &values[i]);
	}
	bool success = true;
	for (int i = 99; i >= 0 && success; i--) {
		int *popped = pila_desapilar(stack);
		success = (popped != NULL && *popped == i);
	}
	pa2m_afirmar(
		success && pila_esta_vacía(stack),
		"Debe poder hacer pop de todos los elementos correctamente.");
	pila_destruir(stack);
}

void pila_apilar_nulo()
{
	Pila *stack = pila_crear();
	bool success = pila_apilar(stack, NULL);
	pa2m_afirmar(!success, "No debe poder apilar un elemento NULL.");
	pila_destruir(stack);
}

//
//
//
// ----- TEST QUEUE
void cola_crear_no_nula()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola != NULL,
		     "La cola debe ser creada y no debe ser nula.");
	cola_destruir(cola);
}

void cola_tamano_cero_al_inicializar()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "La cola debe tener tamaño cero al inicializar.");
	cola_destruir(cola);
}

void cola_encolar_incrementa_tamano()
{
	Cola *cola = cola_crear();
	int valor = 42;
	cola_encolar(cola, &valor);
	pa2m_afirmar(cola_cantidad(cola) == 1,
		     "El tamaño de la cola debe ser 1 después de un enqueue.");
	cola_destruir(cola);
}

void cola_desencolar_disminuye_tamano()
{
	Cola *cola = cola_crear();
	int valor = 42;
	cola_encolar(cola, &valor);
	cola_desencolar(cola);
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "El tamaño de la cola debe ser 0 después de un dequeue.");
	cola_destruir(cola);
}

void cola_frente_devuelve_elemento_frontal()
{
	Cola *cola = cola_crear();
	int valor1 = 42;
	int valor2 = 84;
	cola_encolar(cola, &valor1);
	cola_encolar(cola, &valor2);
	int *frente = (int *)cola_frente(cola);
	pa2m_afirmar(
		*frente == valor1,
		"El elemento en la parte frontal de la cola debe ser el primero agregado.");
	cola_destruir(cola);
}

void cola_esta_vacia_al_inicializar()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_esta_vacía(cola),
		     "La cola debe estar vacía al inicializar.");
	cola_destruir(cola);
}

void cola_no_esta_vacia_despues_de_encolar()
{
	Cola *cola = cola_crear();
	int valor = 42;
	cola_encolar(cola, &valor);
	pa2m_afirmar(!cola_esta_vacía(cola),
		     "La cola no debe estar vacía después de un enqueue.");
	cola_destruir(cola);
}

// Casos límite
void cola_encolar_falla_con_cola_nula()
{
	int valor = 42;
	pa2m_afirmar(!cola_encolar(NULL, &valor),
		     "Enqueue en una cola NULL debe fallar.");
}

void cola_desencolar_cola_vacia_devuelve_null()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Dequeue en una cola vacía debe devolver NULL.");
	cola_destruir(cola);
}

void cola_desencolar_cola_nula_devuelve_null()
{
	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "Dequeue en una cola NULL debe devolver NULL.");
}

void cola_frente_cola_vacia_devuelve_null()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "Peek en una cola vacía debe devolver NULL.");
	cola_destruir(cola);
}

void cola_frente_cola_nula_devuelve_null()
{
	pa2m_afirmar(cola_frente(NULL) == NULL,
		     "Peek en una cola NULL debe devolver NULL.");
}

void cola_tamano_cola_nula_devuelve_cero()
{
	pa2m_afirmar(cola_cantidad(NULL) == 0,
		     "Size de una cola NULL debe devolver 0.");
}

void cola_esta_vacia_cola_nula_devuelve_true()
{
	pa2m_afirmar(cola_esta_vacía(NULL),
		     "Is_empty en una cola NULL debe devolver true.");
}

//
//
//
// ----- TEST LISTA
void lista_crear_no_nula()
{
	Lista *l = lista_crear();

	pa2m_afirmar(l != NULL, "La lista recién creada no debe ser nula.");
	lista_destruir(l);
}

void lista_tamano_cero_al_inicializar()
{
	Lista *l = lista_crear();

	pa2m_afirmar(lista_cantidad_elementos(l) == 0,
		     "La lista recién creada tiene tamaño cero.");
	lista_destruir(l);
}

void lista_agregar_elemento_incrementa_tamano()
{
	Lista *lista = lista_crear();
	int valor = 41;
	lista_agregar_elemento(lista, 0, &valor);

	pa2m_afirmar(true, "Se incrementa el tamaño.");
	pa2m_afirmar(
		lista_cantidad_elementos(lista) == 1,
		"El tamaño de la lista debe ser 1 después de agregar un elemento.");
	lista_destruir(lista);
}

void lista_agregar_multiples_elementos_incrementa_tamano()
{
	Lista *lista = lista_crear();
	int valores[] = { 10, 20, 30, 40, 50 };
	size_t cantidad_valores = sizeof(valores) / sizeof(valores[0]);

	for (size_t i = 0; i < cantidad_valores; i++) {
		pa2m_afirmar(lista_agregar_elemento(lista, i, &valores[i]),
			     "Se puede agregar el elemento %zu", i + 1);
	}

	pa2m_afirmar(
		lista_cantidad_elementos(lista) == cantidad_valores,
		"El tamaño de la lista debe ser %zu después de agregar %zu elementos",
		cantidad_valores, cantidad_valores);

	// Verificar que los elementos se agregaron correctamente
	for (size_t i = 0; i < cantidad_valores; i++) {
		int *encontrado = NULL;
		pa2m_afirmar(lista_obtener_elemento(lista, i,
						    (void **)&encontrado),
			     "Se puede obtener el elemento %zu", i + 1);
		pa2m_afirmar(encontrado != NULL && *encontrado == valores[i],
			     "El elemento %zu debe ser %d", i + 1, valores[i]);
	}

	lista_destruir(lista);
}

void lista_eliminar_elemento_disminuye_tamano()
{
	Lista *lista = lista_crear();
	int valor = 42;
	lista_agregar_elemento(lista, 0, &valor);
	lista_quitar_elemento(lista, 0, NULL);
	pa2m_afirmar(
		lista_cantidad_elementos(lista) == 0,
		"El tamaño de la lista debe ser 0 después de eliminar un elemento.");
	lista_destruir(lista);
}

void lista_buscar_elemento_devuelve_valor_correcto()
{
	Lista *lista = lista_crear();
	int valor = 42;
	lista_agregar_elemento(lista, 0, &valor);
	int *encontrado =
		(int *)lista_buscar_elemento(lista, &valor, comparar_enteros);
	pa2m_afirmar(encontrado != NULL && *encontrado == valor,
		     "La búsqueda debe devolver el elemento correcto.");
	lista_destruir(lista);
}

void lista_obtener_elemento_devuelve_valor_correcto()
{
	Lista *lista = lista_crear();
	int valor = 42;
	lista_agregar_elemento(lista, 0, &valor);
	int *encontrado = NULL;
	lista_obtener_elemento(lista, 0, (void **)&encontrado);
	pa2m_afirmar(encontrado != NULL && *encontrado == valor,
		     "El elemento obtenido debe ser el correcto.");
	lista_destruir(lista);
}

void lista_iterar_elementos_llama_funcion()
{
	Lista *lista = lista_crear();
	int valor1 = 42;
	int valor2 = 84;
	lista_agregar_elemento(lista, 0, &valor1);
	lista_agregar_elemento(lista, 1, &valor2);

	int contador = 0;
	size_t iterados =
		lista_iterar_elementos(lista, contar_elementos, &contador);
	pa2m_afirmar(iterados == 2, "Se deben iterar 2 elementos.");
	pa2m_afirmar(contador == 2, "Se deben contar 2 elementos.");
	lista_destruir(lista);
}
// Casos borde para lista
void lista_agregar_elemento_a_lista_null_falla()
{
	Lista *lista = NULL;
	int valor = 42;
	pa2m_afirmar(lista_agregar_elemento(lista, 0, &valor) == false,
		     "Agregar un elemento a una lista NULL debe fallar.");
}

void lista_agregar_elemento_en_posicion_invalida_falla()
{
	Lista *lista = lista_crear();
	int valor = 42;
	pa2m_afirmar(
		lista_agregar_elemento(lista, 1, &valor) == false,
		"Agregar un elemento en una posición inválida debe fallar.");
	lista_destruir(lista);
}

void lista_remover_elemento_de_lista_vacia_falla()
{
	Lista *lista = lista_crear();
	void *removido = NULL;
	pa2m_afirmar(lista_quitar_elemento(lista, 0, &removido) == false,
		     "Remover un elemento de una lista vacía debe fallar.");
	lista_destruir(lista);
}

void lista_remover_elemento_en_posicion_invalida_falla()
{
	Lista *lista = lista_crear();
	int valor = 42;
	lista_agregar_elemento(lista, 0, &valor);
	void *removido = NULL;
	pa2m_afirmar(
		lista_quitar_elemento(lista, 1, &removido) == false,
		"Remover un elemento de una posición inválida debe fallar.");
	lista_destruir(lista);
}

void lista_buscar_elemento_en_lista_vacia_devuelve_null()
{
	Lista *lista = lista_crear();
	int valor = 42;
	pa2m_afirmar(lista_buscar_elemento(lista, &valor, comparar_enteros) ==
			     NULL,
		     "Buscar en una lista vacía debe devolver NULL.");
	lista_destruir(lista);
}

void lista_obtener_elemento_en_posicion_invalida_falla()
{
	Lista *lista = lista_crear();
	int valor = 42;
	lista_agregar_elemento(lista, 0, &valor);
	void *encontrado = NULL;
	pa2m_afirmar(
		lista_obtener_elemento(lista, 1, &encontrado) == false,
		"Obtener un elemento de una posición inválida debe fallar.");
	lista_destruir(lista);
}

void lista_iterar_lista_vacia_devuelve_cero()
{
	Lista *lista = lista_crear();
	int contador = 0;
	size_t iterados =
		lista_iterar_elementos(lista, contar_elementos, &contador);
	pa2m_afirmar(iterados == 0, "Iterar una lista vacía debe devolver 0.");
	pa2m_afirmar(contador == 0,
		     "No se deben contar elementos en una lista vacía.");
	lista_destruir(lista);
}

void lista_iterar_elementos_en_lista_vacia_devuelve_cero()
{
	Lista *lista = lista_crear();
	int contador = 0;
	size_t iterados =
		lista_iterar_elementos(lista, contar_elementos, &contador);
	pa2m_afirmar(iterados == 0, "Iterar una lista vacía debe devolver 0.");
	pa2m_afirmar(contador == 0,
		     "No se deben contar elementos en una lista vacía.");
	lista_destruir(lista);
}

void lista_iterar_elementos_con_un_solo_elemento()
{
	Lista *lista = lista_crear();
	int valor = 42;
	lista_agregar_elemento(lista, 0, &valor);
	int contador = 0;
	size_t iterados =
		lista_iterar_elementos(lista, contar_elementos, &contador);
	pa2m_afirmar(iterados == 1,
		     "Iterar una lista con un solo elemento debe devolver 1.");
	pa2m_afirmar(
		contador == 1,
		"Se debe contar un elemento en una lista con un solo elemento.");
	lista_destruir(lista);
}

void lista_iterar_elementos_con_multiples_elementos()
{
	Lista *lista = lista_crear();
	int valor1 = 42, valor2 = 43, valor3 = 44;
	lista_agregar_elemento(lista, 0, &valor1);
	lista_agregar_elemento(lista, 1, &valor2);
	lista_agregar_elemento(lista, 2, &valor3);

	int contador = 0;
	size_t iterados =
		lista_iterar_elementos(lista, contar_elementos, &contador);
	pa2m_afirmar(
		iterados == 3,
		"Iterar una lista con múltiples elementos debe devolver 3.");
	pa2m_afirmar(
		contador == 3,
		"Se deben contar tres elementos en una lista con múltiples elementos.");
	lista_destruir(lista);
}

void lista_destruir_lista_null_no_causa_falla()
{
	Lista *lista = NULL;
	lista_destruir(lista);
	pa2m_afirmar(true, "Destruir una lista NULL no debe causar un crash.");
}

void lista_destruir_todos_lista_null_no_causa_falla()
{
	Lista *lista = NULL;
	lista_destruir_todo(lista, free);
	pa2m_afirmar(
		true,
		"Destruir todos los elementos de una lista NULL no debe causar un crash.");
}

// ----- TEST ITERADOR LISTA
void iterador_lista_crear_no_null()
{
	Lista *lista = lista_crear();
	Lista_iterador *iter = lista_iterador_crear(lista);
	pa2m_afirmar(iter != NULL, "El iterador creado no debe ser NULL");
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void iterador_lista_crear_lista_null_devuelve_null()
{
	Lista_iterador *iter = lista_iterador_crear(NULL);
	pa2m_afirmar(iter == NULL,
		     "Crear un iterador con una lista NULL debe devolver NULL");
}

void iterador_lista_hay_siguiente_lista_vacia()
{
	Lista *lista = lista_crear();
	Lista_iterador *iter = lista_iterador_crear(lista);
	pa2m_afirmar(!lista_iterador_hay_siguiente(iter),
		     "Una lista vacía no debe tener siguiente elemento");
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void iterador_lista_hay_siguiente_multiples_elementos()
{
	Lista *lista = lista_crear();
	int valores[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar_elemento(lista, i, &valores[i]);
	}
	Lista_iterador *iter = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_hay_siguiente(iter),
		     "Una lista con múltiples elementos debe tener siguiente");
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void iterador_lista_avanzar_correctamente()
{
	Lista *lista = lista_crear();
	int valores[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar_elemento(lista, i, &valores[i]);
	}
	Lista_iterador *iter = lista_iterador_crear(lista);

	int *actual = lista_iterador_obtener_elemento_actual(iter);
	pa2m_afirmar(actual != NULL && *actual == 1,
		     "El primer elemento debe ser 1");

	lista_iterador_avanzar(iter);
	actual = lista_iterador_obtener_elemento_actual(iter);
	pa2m_afirmar(actual != NULL && *actual == 2,
		     "El segundo elemento debe ser 2");

	lista_iterador_avanzar(iter);
	actual = lista_iterador_obtener_elemento_actual(iter);
	pa2m_afirmar(actual != NULL && *actual == 3,
		     "El tercer elemento debe ser 3");

	lista_iterador_avanzar(iter);
	actual = lista_iterador_obtener_elemento_actual(iter);
	pa2m_afirmar(
		actual == NULL,
		"Después del último elemento, obtener_elemento_actual debe devolver NULL");

	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void iterador_lista_obtener_elemento_actual_iterador_null()
{
	pa2m_afirmar(
		lista_iterador_obtener_elemento_actual(NULL) == NULL,
		"obtener_elemento_actual con iterador NULL debe devolver NULL");
}

// Casos border iterador de lista
void iterador_lista_obtener_elemento_actual_iterador_vacio()
{
	Lista *lista = lista_crear();
	Lista_iterador *iter = lista_iterador_crear(lista);
	void *actual = lista_iterador_obtener_elemento_actual(iter);
	pa2m_afirmar(
		actual == NULL,
		"El elemento actual de un iterador de lista vacío debe ser NULL");
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void iterador_lista_avanzar_iterador_vacio()
{
	Lista *lista = lista_crear();
	Lista_iterador *iter = lista_iterador_crear(lista);
	lista_iterador_avanzar(iter);
	pa2m_afirmar(
		lista_iterador_obtener_elemento_actual(iter) == NULL,
		"Avanzar un iterador de lista vacío no debe cambiar el elemento actual");
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void iterador_lista_hay_siguiente_iterador_null()
{
	pa2m_afirmar(
		!lista_iterador_hay_siguiente(NULL),
		"Un iterador NULL debe indicar que no hay siguiente elemento");
}

void iterador_lista_hay_siguiente_despues_de_avanzar()
{
	Lista *lista = lista_crear();
	int valores[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_agregar_elemento(lista, i, &valores[i]);
	}
	Lista_iterador *iter = lista_iterador_crear(lista);
	lista_iterador_avanzar(iter);
	pa2m_afirmar(
		lista_iterador_hay_siguiente(iter),
		"Después de avanzar, el iterador debe tener siguiente elemento");
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

//
//
//
// ----- MAIN -----
int main()
{
	pa2m_nuevo_grupo("============== Pruebas de Lista ===============");
	lista_crear_no_nula();
	lista_tamano_cero_al_inicializar();
	lista_agregar_elemento_incrementa_tamano();
	lista_agregar_multiples_elementos_incrementa_tamano();
	lista_eliminar_elemento_disminuye_tamano();
	lista_buscar_elemento_devuelve_valor_correcto();
	lista_obtener_elemento_devuelve_valor_correcto();
	lista_iterar_elementos_llama_funcion();
	// Casos borde
	lista_agregar_elemento_a_lista_null_falla();
	lista_agregar_elemento_en_posicion_invalida_falla();
	lista_remover_elemento_de_lista_vacia_falla();
	lista_remover_elemento_en_posicion_invalida_falla();
	lista_buscar_elemento_en_lista_vacia_devuelve_null();
	lista_obtener_elemento_en_posicion_invalida_falla();
	lista_iterar_lista_vacia_devuelve_cero();
	lista_iterar_elementos_en_lista_vacia_devuelve_cero();
	lista_iterar_elementos_con_un_solo_elemento();
	lista_iterar_elementos_con_multiples_elementos();
	lista_destruir_lista_null_no_causa_falla();
	lista_destruir_todos_lista_null_no_causa_falla();

	pa2m_nuevo_grupo(
		"============== Pruebas de Iterador de Lista ===============");
	iterador_lista_crear_no_null();
	iterador_lista_crear_lista_null_devuelve_null();
	iterador_lista_hay_siguiente_lista_vacia();
	iterador_lista_hay_siguiente_multiples_elementos();
	iterador_lista_avanzar_correctamente();
	iterador_lista_obtener_elemento_actual_iterador_null();
	iterador_lista_obtener_elemento_actual_iterador_vacio();
	iterador_lista_avanzar_iterador_vacio();
	iterador_lista_hay_siguiente_iterador_null();
	iterador_lista_hay_siguiente_despues_de_avanzar();

	//
	pa2m_nuevo_grupo("============== Pruebas de Pila ===============");
	pila_esta_vacio_al_inicializar();
	pila_no_esta_vacia_despues_de_apilar();
	pila_desapilar_pila_vacia();
	pila_tope_pila_vacia();
	pila_tamano_pila_nula();
	pila_esta_vacia_pila_nula();
	pila_apilar_muchos_elementos();
	pila_desapilar_todos_los_elementos();
	pila_no_esta_vacia_despues_de_apilar();

	//
	pa2m_nuevo_grupo("============== Pruebas de Cola ===============");
	cola_crear_no_nula();
	cola_tamano_cero_al_inicializar();
	cola_encolar_incrementa_tamano();
	cola_desencolar_disminuye_tamano();
	cola_frente_devuelve_elemento_frontal();
	cola_esta_vacia_al_inicializar();
	cola_no_esta_vacia_despues_de_encolar();
	cola_encolar_falla_con_cola_nula();
	cola_desencolar_cola_vacia_devuelve_null();
	cola_desencolar_cola_nula_devuelve_null();
	cola_frente_cola_vacia_devuelve_null();
	cola_frente_cola_nula_devuelve_null();
	cola_tamano_cola_nula_devuelve_cero();
	cola_esta_vacia_cola_nula_devuelve_true();

	return pa2m_mostrar_reporte();
}
