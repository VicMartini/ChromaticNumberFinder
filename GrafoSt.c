#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "GrafoSt.h"
typedef uint32_t u32;

u32 print_graph(Grafo g, u32 lines)
{
    u32 M = g->num_vertices;
    vertice *vert, *vecino = NULL;
    u32 longitud_lista = 0;
    if (lines > M)
        return 1;
    for (u32 i = 0; i < lines; i++)
    {
        vert = g->vertices[i];
        if (vert != NULL)
        {
            printf("%u: vertice: %u -> \n", i, vert->nombre);
            printf("  vecinos:\n");
            printf("( \n");
            longitud_lista = vert->grado;
            printf("grado: %u \n", longitud_lista);
            for (u32 i = 0; i < longitud_lista; i++)
            {
                vecino = index_ith(i, vert->vecinos);
                if (vecino != NULL)
                {
                    printf("(v: %u, peso: %u )", vecino->nombre, vert->pesos[i]);
                }
            }
            printf("\n ) \n");
            printf("\n");
        }
    }
    return 0;
}
Grafo ConstruccionDelGrafo(void)
{
    Grafo new_graph = malloc(sizeof(struct GrafoSt));
    Lado_st *infoEdge = NULL;
    Lado_st **array = NULL;
    u32 N = 0;
    u32 M = 0;
    u32 v_degree = 0;
    u32 max_degree = 0;
    u32 min_degree = 0xFFFFFFFF;

    infoEdge = parse_p_edge_n_m();
    N = infoEdge->v;
    M = infoEdge->w;
    array = parse_edge(infoEdge);
    new_graph->num_vertices = N;

    hash_table scaffold = new_ht(N); //La hashtable va a servir como un 'andamio' para la
                                     //construcción del grafo.

    for (int i = 0; i < M; i++)
    {
        insert_edge(array[i]->v, array[i]->w, scaffold);
    }
    //Ya no necesitamos la hashtable. Vamos a destruirla y quedarnos solo con el iterator
    new_graph->vertices = ht_extract_iterator(scaffold);
    for (int j = 0; j < N; ++j)
    {
        v_degree = length(new_graph->vertices[j]->vecinos);
        new_graph->vertices[j]->pesos = calloc(v_degree, sizeof(u32));
        new_graph->vertices[j]->grado = v_degree;
        min_degree = (v_degree < min_degree) ? v_degree : min_degree;
        max_degree = (v_degree > max_degree) ? v_degree : max_degree;
    }
    new_graph->Delta = max_degree;
    new_graph->delta = min_degree;
    return new_graph;
}

u32 Delta(Grafo g)
{
    return g->Delta;
}

u32 delta(Grafo g)
{
    return g->Delta;
}

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G)
{
    ;
    u32 n = G->num_vertices;
    if (i < n && j < G->vertices[i]->grado)
    {
        G->vertices[i]->pesos[j] = p;
        return 0;
    }
    else
    {
        return 1;
    }
};
u32 PesoLadoConVecino(u32 j, u32 i, Grafo G)
{
    u32 n = G->num_vertices;
    if (i < n && j < G->vertices[i]->grado)
        return G->vertices[i]->pesos[j];
    else
        return 0;
};
