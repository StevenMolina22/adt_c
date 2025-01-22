#include "graph.h"

struct graph {
	Hash* adjacency;
};

struct edge {
	void* to;
	void* weight;
};

/*
 */
Graph* g_new() {
	Graph* g = malloc(sizeof(Graph));
	g->adjacency = hash_new(0);
	return g;
}

void g_destroy(Graph* g, void (*fn)(void*)) {
	hash_destroy_all(g->adjacency, fn);
	free(g);
}

/*
 */
void g_add_vertex(Graph* g, void* vertex) {
	// TODO! change hash adt to be generic
	if (hash_get(g->adjacency, vertex) == NULL) {
		hash_insert(g->adjacency, vertex, NULL, NULL);
	}
}

/*
 */
void g_add_edge(Graph* g, void* from, void* to, Edge* edge);

/*
 */
void g_remove_vertex(Graph* g, void* vertex);

/*
 */
void g_remove_edge(Graph* g, void* from, void* to);

/*
 */
Edge** g_get_neighbors(Graph* g, void* V);

/*
 */
void g_dft(Graph* g, void* vertex, Fn f);

/*
 *
 */
void g_bft(Graph* g, void* vertex, Fn f);

/*
 */
void g_print(Graph* g);
