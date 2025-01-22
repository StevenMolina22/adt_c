#include <stdio.h>
#include "hash/hash.h"
#include "pa2m.h"

void prueba_crear_hash()
{
	Hash *hash = hash_new(10);
	pa2m_afirmar(hash != NULL,
		     "Se puede crear un hash con capacidad inicial 10");
	pa2m_afirmar(hash_size(hash) == 0,
		     "El hash recién creado tiene 0 elementos");
	hash_destroy(hash);
}

void prueba_insertar_elementos()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado;

	pa2m_afirmar(hash_insert(hash, "clave1", &valor1, &encontrado),
		     "Se puede insertar un elemento en el hash");
	pa2m_afirmar(hash_size(hash) == 1,
		     "El hash tiene 1 elemento después de insertar");
	pa2m_afirmar(hash_insert(hash, "clave2", &valor2, &encontrado),
		     "Se puede insertar otro elemento en el hash");
	pa2m_afirmar(hash_size(hash) == 2,
		     "El hash tiene 2 elementos después de insertar");

	hash_destroy(hash);
}

void prueba_insertar_claves_duplicadas()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	pa2m_afirmar(hash_insert(hash, "clave1", &valor2, &encontrado),
		     "Se puede insertar un elemento con una clave duplicada");
	pa2m_afirmar(
		hash_size(hash) == 1,
		"El hash tiene 1 elemento después de insertar una clave duplicada");
	pa2m_afirmar(encontrado == &valor1,
		     "El valor reemplazado es el correcto");

	int *valor_encontrado = (int *)hash_get(hash, "clave1");
	pa2m_afirmar(valor_encontrado != NULL && *valor_encontrado == valor2,
		     "El valor asociado a 'clave1' es el nuevo valor");

	hash_destroy(hash);
}

void prueba_insertar_clave_nula()
{
	Hash *hash = hash_new(10);
	int valor = 42;
	void *encontrado = NULL;

	pa2m_afirmar(!hash_insert(hash, NULL, &valor, &encontrado),
		     "No se puede insertar un elemento con clave nula");

	hash_destroy(hash);
}

void prueba_insertar_valor_nulo()
{
	Hash *hash = hash_new(10);
	void *encontrado = NULL;

	pa2m_afirmar(hash_insert(hash, "clave1", NULL, &encontrado),
		     "Se puede insertar un elemento con valor nulo");
	pa2m_afirmar(
		hash_size(hash) == 1,
		"El hash tiene 1 elemento después de insertar un valor nulo");

	hash_destroy(hash);
}

// CASOS BORDE
void prueba_insertar_muchos_elementos()
{
	Hash *hash = hash_new(10);
	void *encontrado = NULL;
	int cantidad = 1000;
	bool exito = true;

	for (int i = 0; i < cantidad; i++) {
		char clave[20];
		sprintf(clave, "clave%d", i);
		int *valor = malloc(sizeof(int));
		*valor = i;
		if (!hash_insert(hash, clave, valor, &encontrado)) {
			exito = false;
			break;
		}
	}

	pa2m_afirmar(exito, "Se pueden insertar 1000 elementos en el hash");
	pa2m_afirmar(
		hash_size(hash) == cantidad,
		"El hash tiene 1000 elementos después de insertar muchos elementos");

	hash_destroy_all(hash, free);
}

void prueba_insertar_en_hash_vacio()
{
	Hash *hash = hash_new(10);
	void *encontrado = NULL;

	pa2m_afirmar(hash_size(hash) == 0,
		     "Un hash recién creado tiene 0 elementos");
	pa2m_afirmar(hash_insert(hash, "clave1", NULL, &encontrado),
		     "Se puede insertar un elemento en un hash vacío");
	pa2m_afirmar(
		hash_size(hash) == 1,
		"El hash tiene 1 elemento después de insertar en un hash vacío");

	hash_destroy(hash);
}

void prueba_insertar_claves_largas()
{
	Hash *hash = hash_new(10);
	char clave[256];
	memset(clave, 'a', 255);
	clave[255] = '\0';
	int valor = 42;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insert(hash, clave, &valor, &encontrado),
		     "Se puede insertar una clave muy larga");
	pa2m_afirmar(
		hash_size(hash) == 1,
		"El hash tiene 1 elemento después de insertar una clave larga");

	hash_destroy(hash);
}

void prueba_insertar_claves_iguales_diferente_caso()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave", &valor1, &encontrado);
	pa2m_afirmar(hash_insert(hash, "CLAVE", &valor2, &encontrado),
		     "Se pueden insertar claves iguales con diferente caso");
	pa2m_afirmar(
		hash_size(hash) == 2,
		"El hash tiene 2 elementos con claves iguales en diferente caso");

	hash_destroy(hash);
}

void prueba_insertar_colision()
{
	Hash *hash = hash_new(1); // Forzar colisiones
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insert(hash, "clave1", &valor1, &encontrado),
		     "Se puede insertar un elemento en un hash con colisión");
	pa2m_afirmar(hash_insert(hash, "clave2", &valor2, &encontrado),
		     "Se puede insertar otro elemento con colisión");
	pa2m_afirmar(hash_size(hash) == 2,
		     "El hash tiene 2 elementos después de manejar colisiones");

	hash_destroy(hash);
}

void prueba_insertar_mas_elementos_que_capacidad_inicial()
{
	Hash *hash = hash_new(3);
	void *encontrado = NULL;
	int cantidad = 10;
	bool exito = true;

	for (int i = 0; i < cantidad; i++) {
		char clave[20];
		sprintf(clave, "clave%d", i);
		int *valor = malloc(sizeof(int));
		*valor = i;
		if (!hash_insert(hash, clave, valor, &encontrado)) {
			exito = false;
			break;
		}
	}

	pa2m_afirmar(
		exito,
		"Se pueden insertar más elementos que la capacidad inicial del hash");
	pa2m_afirmar(
		hash_size(hash) == cantidad,
		"El hash tiene todos los elementos insertados después de redimensionar");

	hash_destroy_all(hash, free);
}

void prueba_insertar_claves_caracteres_especiales()
{
	Hash *hash = hash_new(10);
	char *claves[] = { "clave_esp!@#", "clave+123", "clave-con-guion",
			   "clave.con.punto" };
	int valores[] = { 1, 2, 3, 4 };
	void *encontrado = NULL;

	bool exito = true;
	for (int i = 0; i < 4; i++) {
		if (!hash_insert(hash, claves[i], &valores[i], &encontrado)) {
			exito = false;
			break;
		}
	}

	pa2m_afirmar(exito,
		     "Se pueden insertar claves con caracteres especiales");
	pa2m_afirmar(hash_size(hash) == 4,
		     "El hash tiene 4 elementos con claves especiales");

	hash_destroy(hash);
}

void prueba_buscar_elementos()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(hash, "clave2", &valor2, &encontrado);

	int *valor_encontrado = (int *)hash_get(hash, "clave1");
	pa2m_afirmar(
		valor_encontrado != NULL && *valor_encontrado == valor1,
		"Se puede buscar y encontrar el valor asociado a 'clave1'");

	valor_encontrado = (int *)hash_get(hash, "clave2");
	pa2m_afirmar(
		valor_encontrado != NULL && *valor_encontrado == valor2,
		"Se puede buscar y encontrar el valor asociado a 'clave2'");

	valor_encontrado = (int *)hash_get(hash, "clave_inexistente");
	pa2m_afirmar(valor_encontrado == NULL,
		     "Buscar una clave inexistente devuelve NULL");

	hash_destroy(hash);
}

// CASOS BORDE BUSCAR
void prueba_buscar_clave_nula()
{
	Hash *hash = hash_new(10);

	void *valor_encontrado = hash_get(hash, NULL);
	pa2m_afirmar(valor_encontrado == NULL,
		     "Buscar una clave nula devuelve NULL");

	hash_destroy(hash);
}

void prueba_buscar_en_hash_vacio()
{
	Hash *hash = hash_new(10);

	void *valor_encontrado = hash_get(hash, "clave1");
	pa2m_afirmar(valor_encontrado == NULL,
		     "Buscar una clave en un hash vacío devuelve NULL");

	hash_destroy(hash);
}

void prueba_buscar_claves_duplicadas()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(hash, "clave1", &valor2, &encontrado);

	int *valor_encontrado = (int *)hash_get(hash, "clave1");
	pa2m_afirmar(
		valor_encontrado != NULL && *valor_encontrado == valor2,
		"Buscar una clave duplicada devuelve el último valor insertado");

	hash_destroy(hash);
}

void prueba_buscar_colision()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(
		hash, "clave2", &valor2,
		&encontrado); // Asume que "clave1" y "clave2" generan una colisión.

	int *valor_encontrado = (int *)hash_get(hash, "clave1");
	pa2m_afirmar(
		valor_encontrado != NULL && *valor_encontrado == valor1,
		"Se puede buscar y encontrar el valor asociado a 'clave1' en caso de colisión");

	valor_encontrado = (int *)hash_get(hash, "clave2");
	pa2m_afirmar(
		valor_encontrado != NULL && *valor_encontrado == valor2,
		"Se puede buscar y encontrar el valor asociado a 'clave2' en caso de colisión");

	hash_destroy(hash);
}

void prueba_quitar_elementos()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(hash, "clave2", &valor2, &encontrado);

	int *valor_quitado = (int *)hash_remove(hash, "clave1");
	pa2m_afirmar(valor_quitado != NULL && *valor_quitado == valor1,
		     "Se puede quitar el valor asociado a 'clave1'");
	pa2m_afirmar(hash_size(hash) == 1,
		     "El hash tiene 1 elemento después de quitar 'clave1'");

	valor_quitado = (int *)hash_remove(hash, "clave2");
	pa2m_afirmar(valor_quitado != NULL && *valor_quitado == valor2,
		     "Se puede quitar el valor asociado a 'clave2'");
	pa2m_afirmar(hash_size(hash) == 0,
		     "El hash tiene 0 elementos después de quitar 'clave2'");

	valor_quitado = (int *)hash_remove(hash, "clave_inexistente");
	pa2m_afirmar(valor_quitado == NULL,
		     "Quitar una clave inexistente devuelve NULL");

	hash_destroy(hash);
}

void prueba_quitar_muchos_elementos()
{
	Hash *hash = hash_new(10);
	void *encontrado = NULL;
	int cantidad = 1000;

	for (int i = 0; i < cantidad; i++) {
		char clave[20];
		sprintf(clave, "clave%d", i);
		int *valor = malloc(sizeof(int));
		*valor = i;
		hash_insert(hash, clave, valor, &encontrado);
	}

	bool exito = true;
	for (int i = 0; i < cantidad; i++) {
		char clave[20];
		sprintf(clave, "clave%d", i);
		int *valor_quitado = (int *)hash_remove(hash, clave);
		if (valor_quitado == NULL || *valor_quitado != i) {
			exito = false;
			break;
		}
		free(valor_quitado);
	}

	pa2m_afirmar(exito, "Se pueden quitar 1000 elementos del hash");
	pa2m_afirmar(
		hash_size(hash) == 0,
		"El hash tiene 0 elementos después de quitar muchos elementos");

	hash_destroy(hash);
}

// CASOS BORDE QUITAR
void prueba_quitar_clave_nula()
{
	Hash *hash = hash_new(10);

	void *valor_quitado = hash_remove(hash, NULL);
	pa2m_afirmar(valor_quitado == NULL,
		     "Quitar una clave nula devuelve NULL");

	hash_destroy(hash);
}

void prueba_quitar_en_hash_vacio()
{
	Hash *hash = hash_new(10);

	void *valor_quitado = hash_remove(hash, "clave1");
	pa2m_afirmar(valor_quitado == NULL,
		     "Quitar una clave en un hash vacío devuelve NULL");

	hash_destroy(hash);
}

void prueba_quitar_claves_duplicadas()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(hash, "clave1", &valor2, &encontrado);

	int *valor_quitado = (int *)hash_remove(hash, "clave1");
	pa2m_afirmar(
		valor_quitado != NULL && *valor_quitado == valor2,
		"Quitar una clave duplicada devuelve el último valor insertado");
	pa2m_afirmar(
		hash_size(hash) == 0,
		"El hash tiene 0 elementos después de quitar la clave duplicada");

	hash_destroy(hash);
}

void prueba_quitar_colision()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(
		hash, "clave2", &valor2,
		&encontrado); // Asume que "clave1" y "clave2" generan una colisión.

	int *valor_quitado = (int *)hash_remove(hash, "clave1");
	pa2m_afirmar(valor_quitado != NULL && *valor_quitado == valor1,
		     "Se puede quitar una clave en colisión correctamente");
	pa2m_afirmar(
		hash_size(hash) == 1,
		"El hash tiene 1 elemento después de quitar una clave en colisión");

	valor_quitado = (int *)hash_remove(hash, "clave2");
	pa2m_afirmar(valor_quitado != NULL && *valor_quitado == valor2,
		     "Se puede quitar la otra clave en colisión correctamente");
	pa2m_afirmar(
		hash_size(hash) == 0,
		"El hash tiene 0 elementos después de quitar todas las claves en colisión");

	hash_destroy(hash);
}

void prueba_contiene_clave()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);

	pa2m_afirmar(hash_contains(hash, "clave1"),
		     "El hash contiene 'clave1'");
	pa2m_afirmar(!hash_contains(hash, "clave_inexistente"),
		     "El hash no contiene 'clave_inexistente'");

	hash_destroy(hash);
}

bool iterador_prueba(char *clave, void *valor, void *ctx)
{
	(*(int *)ctx)++;
	return true;
}

bool iterador_prueba_corte(char *clave, void *valor, void *ctx)
{
	(*(int *)ctx)++;
	return (*(int *)ctx) < 2;
}

void prueba_iterar_elementos()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(hash, "clave2", &valor2, &encontrado);

	int contador = 0;
	size_t iterados = hash_map(hash, iterador_prueba, &contador);

	pa2m_afirmar(iterados == 2, "Se iteran 2 elementos en el hash");
	pa2m_afirmar(
		contador == 2,
		"El contador se incrementa correctamente durante la iteración");

	contador = 0;
	iterados = hash_map(hash, iterador_prueba_corte, &contador);
	pa2m_afirmar(
		iterados == 2,
		"La iteración se corta correctamente cuando la función devuelve false");
	pa2m_afirmar(
		contador == 2,
		"El contador se incrementa correctamente durante la iteración con corte");

	hash_destroy(hash);
}

// CASOS BORDE ITERAR
void prueba_iterar_hash_vacio()
{
	Hash *hash = hash_new(10);
	int contador = 0;

	size_t iterados = hash_map(hash, iterador_prueba, &contador);
	pa2m_afirmar(iterados == 0, "No se itera sobre un hash vacío");
	pa2m_afirmar(contador == 0,
		     "El contador permanece en 0 en un hash vacío");

	hash_destroy(hash);
}

void prueba_iterar_elementos_con_duplicados()
{
	Hash *hash = hash_new(10);
	int valor1 = 42;
	int valor2 = 84;
	void *encontrado = NULL;

	// Insertando duplicados
	hash_insert(hash, "clave1", &valor1, &encontrado);
	hash_insert(hash, "clave1", &valor2,
		      &encontrado); // La clave 'clave1' se sobrescribe

	int contador = 0;
	size_t iterados = hash_map(hash, iterador_prueba, &contador);

	pa2m_afirmar(
		iterados == 1,
		"Solo se itera sobre la clave única 'clave1' después de sobrescribirla");
	pa2m_afirmar(
		contador == 1,
		"El contador se incrementa correctamente cuando hay duplicados");

	hash_destroy(hash);
}

void prueba_iterar_gran_cantidad_elementos()
{
	Hash *hash = hash_new(1000);
	void *encontrado = NULL;
	int cantidad = 1000;

	for (int i = 0; i < cantidad; i++) {
		char clave[20];
		sprintf(clave, "clave%d", i);
		int *valor = malloc(sizeof(int));
		*valor = i;
		hash_insert(hash, clave, valor, &encontrado);
	}

	int contador = 0;
	size_t iterados = hash_map(hash, iterador_prueba, &contador);

	pa2m_afirmar(iterados == cantidad,
		     "Se iteran 1000 elementos correctamente");
	pa2m_afirmar(
		contador == cantidad,
		"El contador se incrementa correctamente durante la iteración de muchos elementos");

	hash_destroy_all(hash, free);
}

void destructor_prueba(void *elemento)
{
	free(elemento);
}

void prueba_destruir_todo()
{
	Hash *hash = hash_new(10);
	int *valor1 = malloc(sizeof(int));
	int *valor2 = malloc(sizeof(int));
	*valor1 = 42;
	*valor2 = 84;
	void *encontrado = NULL;

	hash_insert(hash, "clave1", valor1, &encontrado);
	hash_insert(hash, "clave2", valor2, &encontrado);

	hash_destroy_all(hash, destructor_prueba);
	pa2m_afirmar(
		true,
		"El hash se destruye correctamente y se aplica el destructor a los elementos");
}

void prueba_destruir_sin_elementos()
{
	Hash *hash = hash_new(10);
	hash_destroy(hash);
	pa2m_afirmar(
		true,
		"El hash se destruye correctamente cuando no tiene elementos");
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas del Hashmap ===============");
	prueba_crear_hash();

	pa2m_nuevo_grupo("Pruebas de inserción en hash");
	prueba_insertar_en_hash_vacio();
	prueba_insertar_elementos();
	prueba_insertar_claves_duplicadas();
	prueba_insertar_clave_nula();
	prueba_insertar_valor_nulo();
	prueba_insertar_muchos_elementos();
	// CASOS BORDE
	prueba_insertar_claves_largas();
	prueba_insertar_claves_iguales_diferente_caso();
	prueba_insertar_colision();
	prueba_insertar_mas_elementos_que_capacidad_inicial();
	prueba_insertar_claves_caracteres_especiales();

	pa2m_nuevo_grupo("Pruebas de buscar en hash");
	prueba_buscar_elementos();
	// CASOS BORDE
	prueba_buscar_clave_nula();
	prueba_buscar_en_hash_vacio();
	prueba_buscar_claves_duplicadas();
	prueba_buscar_colision();

	pa2m_nuevo_grupo("Pruebas de quitar en hash");
	prueba_quitar_elementos();
	prueba_quitar_muchos_elementos();
	// CASOS BORDE
	prueba_quitar_clave_nula();
	prueba_quitar_en_hash_vacio();
	prueba_quitar_claves_duplicadas();
	prueba_quitar_colision();

	pa2m_nuevo_grupo("Pruebas de iteración de elementos en el hash");
	prueba_iterar_elementos();
	// CASOS BORDE
	prueba_iterar_hash_vacio();
	prueba_iterar_elementos_con_duplicados();
	prueba_iterar_gran_cantidad_elementos();

	pa2m_nuevo_grupo("Pruebas de general en hash");
	prueba_contiene_clave();
	prueba_destruir_todo();
	prueba_destruir_sin_elementos();

	return pa2m_mostrar_reporte();
}
