#ifndef __GRAPH__
#define __GRAPH__

#include <stdlib.h>
#include "../hash/hash.h"
#include "../list/cola.h"

typedef struct graph Graph;
typedef struct edge Edge;

typedef void Fn(void*); 

/*
 */
Graph* g_new();

/*
 */
void g_add_vertex(Graph* g, void* vertex);

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
 */
void g_bft(Graph* g, void* vertex, Fn f);

/*
 */
void g_print(Graph* g);

#endif
