//
// Created by Once on 2019/10/11.
//

#ifndef GRAPHTHEORY_GRAPH_H
#define GRAPHTHEORY_GRAPH_H

#include "list.h"

typedef void* gdata;

typedef struct node{
    int src;
    int dest;
    int weight;
    int r;
    int flow; // residual flow
    struct node *next;
} Node;

typedef struct vertex{
    int src;
    int visited;
    int color;
    int indegree;
    int level;
    int dist;
    int d;
    int low;
    int num;
    int path;
    int cyclic;
    gdata data;
    Node *adjlist;
} Vertex;

typedef struct graph{
    int n;
    int e;
    int is_directed;
    Vertex *list;
} Graph;

extern Graph *graph_new(int n, int is_directed);
extern void graph_add_edge(Graph *graph, gdata ud, gdata vd, int u, int v, int w);
extern void graph_dfs(Graph *graph, int s);
extern void graph_bfs(Graph *graph, int s);
extern int graph_is_cyclic_directed(Graph *graph);
extern int graph_is_cyclic_undirected(Graph *graph);
extern void graph_topsort_01(Graph *graph);
extern void graph_topsort_02(Graph *graph);
extern void graph_all_topsort(Graph *graph);
extern void graph_reset_indegree(Graph *graph);
extern void graph_print_path(Graph *graph, int u, int v);
extern void graph_shortest_path_unweighted(Graph *graph, int s);
extern void graph_shortest_path_weighted_dijkstra(Graph *graph, int s);
extern void graph_shortest_path_weighted_negative(Graph *graph, int s);
extern int graph_max_flow_fordfulkerson(Graph *graph, int s, int t);
extern int graph_max_flow_dinic(Graph *graph, int s, int t);
extern int graph_undirected_is_connected(Graph *graph);
extern void graph_print_mst_prim(Graph *graph);
extern void graph_mst_prim(Graph *graph);
extern void graph_mst_kruskal(Graph *graph, Node *edges[]);
extern void graph_print_mst_kruskal(Graph *graph, Node *edges[]);
extern List *graph_find_articulation_p(Graph *graph);
extern void graph_print_articulation(Graph *graph, List *list);
extern void graph_print_color(Graph *graph);
extern void graph_coloring_greedy(Graph *graph);
extern int graph_m_coloring(Graph *graph, int m);
extern int graph_clear(Graph *graph);

#endif //GRAPHTHEORY_GRAPH_H
