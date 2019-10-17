#include <stdio.h>
#include "densegraph.h"
#include "queue.h"
#include "sparsegraph.h"
#include "cyclegraph.h"
#include "graph.h"


static void densegraph(void){
    DenseGraph *graph = dgraph_new(6);
    dgraph_add_edge(graph, 0, 1);
    dgraph_add_edge(graph, 0, 2);
    dgraph_add_edge(graph, 1, 3);
    dgraph_add_edge(graph, 1, 4);
    dgraph_add_edge(graph, 2, 4);
    dgraph_add_edge(graph, 3, 4);
    dgraph_add_edge(graph, 3, 5);
    dgraph_add_edge(graph, 4, 5);
    dgraph_bfs(graph, 5);
    dgraph_dfs(graph, 0);
    dgraph_clear(graph);
}

static void sparsegraph(void){
    SparseGraph *graph = sgraph_new(6);
    sgraph_add_edge(graph, 0, 1);
    sgraph_add_edge(graph, 0, 2);
    sgraph_add_edge(graph, 1, 3);
    sgraph_add_edge(graph, 1, 4);
    sgraph_add_edge(graph, 2, 4);
    sgraph_add_edge(graph, 3, 4);
    sgraph_add_edge(graph, 3, 5);
    sgraph_add_edge(graph, 4, 5);
    sgraph_bfs(graph, 5);
    sgraph_dfs(graph, 0);
    sgraph_clear(graph);
}

static void cyclegraph(void){
    // directed graph
    CycleGraph *digraph = cgraph_new(5, 1);
    cgraph_add_edge(digraph, "Bird","Apple", 1, 0, 15);
    cgraph_add_edge(digraph, "Apple","Dog", 0, 3, 26);
    cgraph_add_edge(digraph, "Cat","Bird", 2, 1, 3);
//    cgraph_add_edge(digraph, "Apple","Cat", 0, 2, 5);
//    cgraph_add_edge(digraph, "Egg","Apple", 4, 0, 10);

    cgraph_add_edge(digraph, "Cat","Apple", 2, 0, 5);
    cgraph_add_edge(digraph, "Apple","Egg", 0, 4, 10);

    cgraph_add_edge(digraph, "Dog","Egg", 3, 4, 7);
    cgraph_dfs(digraph, 0);
    cgraph_bfs(digraph, 3);
    if(cgraph_is_cyclic_directed_normal(digraph))
        printf("digraph has cycle\n");
    else
        printf("digraph doesn't have cycle\n");
    if(cgraph_is_cyclic_directed_color(digraph))
        printf("digraph has cycle\n");
    else
        printf("digraph doesn't have cycle\n");
    cgraph_clear(digraph);

    // undirected graph
    CycleGraph *graph = cgraph_new(4, 0);
    cgraph_add_edge(graph, "Green Town", "Lonely Village", 0, 1, 15);
    cgraph_add_edge(graph, "Green Town", "Moon City", 0, 2, 18);
    cgraph_add_edge(graph, "Lonely Village", "Moon City", 1, 2, 26);
    cgraph_add_edge(graph, "Dead Forest", "Moon City", 3, 2, 10);
    cgraph_dfs(graph, 0);
    cgraph_bfs(graph, 3);
    if(cgraph_is_cyclic_undirected_disjset(graph))
        printf("graph has cycle\n");
    else
        printf("graph doesn't have cycle\n");
    if(cgraph_is_cyclic_undirected_normal(graph))
        printf("graph has cycle\n");
    else
        printf("graph doesn't have cycle\n");
    cgraph_clear(graph);
}

static void graph(void){
    // directed graph
    Graph *digraph = graph_new(5, 1);
    graph_add_edge(digraph, "Bird","Apple", 1, 0, 15);
    graph_add_edge(digraph, "Apple","Dog", 0, 3, 26);
    graph_add_edge(digraph, "Cat","Bird", 2, 1, 3);
    graph_add_edge(digraph, "Apple","Cat", 0, 2, 5);
    graph_add_edge(digraph, "Egg","Apple", 4, 0, 10);

//    graph_add_edge(digraph, "Cat","Apple", 2, 0, 5);
//    graph_add_edge(digraph, "Apple","Egg", 0, 4, 10);

    graph_add_edge(digraph, "Dog","Egg", 3, 4, 7);
    graph_dfs(digraph, 0);
    graph_bfs(digraph, 3);
    if(graph_is_cyclic_directed(digraph))
        printf("digraph has cycle\n");
    else
        printf("digraph doesn't have cycle\n");
    graph_clear(digraph);

    printf("\n");

    // undirected graph
    Graph *ungraph = graph_new(4, 0);
    graph_add_edge(ungraph, "Green Town", "Lonely Village", 0, 1, 15);
    graph_add_edge(ungraph, "Green Town", "Moon City", 0, 2, 18);
//    graph_add_edge(ungraph, "Lonely Village", "Moon City", 1, 2, 26);
    graph_add_edge(ungraph, "Dead Forest", "Moon City", 3, 2, 10);
    graph_dfs(ungraph, 0);
    graph_bfs(ungraph, 3);
    if(graph_is_cyclic_undirected(ungraph))
        printf("ungraph has cycle\n");
    else
        printf("ungraph doesn't have cycle\n");
    graph_clear(ungraph);

    printf("\n");

    // topological sorting
    Graph *tgraph = graph_new(8, 1);
    graph_add_edge(tgraph, "1", "0", 1, 0, 0);
    graph_add_edge(tgraph, "2", "1", 2, 1, 0);
    graph_add_edge(tgraph, "3", "1", 3, 1, 0);
    graph_add_edge(tgraph, "5", "2", 5, 2, 0);
    graph_add_edge(tgraph, "6", "3", 6, 3, 0);
    graph_add_edge(tgraph, "5", "4", 5, 4, 0);
    graph_add_edge(tgraph, "7", "5", 7, 5, 0);
    graph_add_edge(tgraph, "6", "4", 6, 4, 0);
    graph_add_edge(tgraph, "7", "6", 7, 6, 0);

//    graph_add_edge(tgraph, "4", "6", 4, 6, 0);
//    graph_add_edge(tgraph, "6", "7", 6, 7, 0);
    graph_topsort_01(tgraph);
    graph_topsort_02(tgraph);
    graph_reset_indegree(tgraph);
    graph_all_topsort(tgraph);
    graph_clear(tgraph);

    printf("\n");

    Graph *s1 = graph_new(6, 1);
    graph_add_edge(s1, "A", "B", 0, 1, 4);
    graph_add_edge(s1, "A", "C", 0, 2, 2);
    graph_add_edge(s1, "B", "C", 1, 2, 5);
    graph_add_edge(s1, "B", "D", 1, 3, 10);
    graph_add_edge(s1, "C", "E", 2, 4, 3);
    graph_add_edge(s1, "E", "D", 4, 3, 4);
    graph_add_edge(s1, "D", "F", 3, 5, 11);
    graph_shortest_path_unweighted(s1, 0);
    graph_print_path(s1, 0, 5);
    graph_shortest_path_weighted_dijkstra(s1, 0);
    graph_print_path(s1, 0, 5);
    graph_clear(s1);

    printf("\n");

    printf("shortest path\n");
    Graph *s2 = graph_new(5, 1);
    graph_add_edge(s2, "0", "1", 0, 1, -3);
    graph_add_edge(s2, "0", "2", 0, 2, 5);
    graph_add_edge(s2, "1", "3", 1, 3, 1);
    graph_add_edge(s2, "2", "3", 2, 3, -8);

//    graph_add_edge(s2, "2", "4", 2, 4, -2);
    graph_add_edge(s2, "4", "2", 4, 2, -2); // cycle

    graph_add_edge(s2, "3", "4", 3, 4, 3);
    graph_shortest_path_unweighted(s2, 0);
    graph_print_path(s2, 0, 4);
    graph_shortest_path_weighted_negative(s2, 0);
    graph_print_path(s2, 0, 4);
    graph_clear(s2);

    printf("\n");

    Graph *s3 = graph_new(6, 1);
    graph_add_edge(s3, "0", "1", 0, 1, 3);
    graph_add_edge(s3, "0", "2", 0, 2, 4);
    graph_add_edge(s3, "1", "2", 1, 2, 4);
    graph_add_edge(s3, "1", "3", 1, 3, 2);
    graph_add_edge(s3, "1", "4", 1, 4, 3);
    graph_add_edge(s3, "2", "4", 2, 4, 4);
    graph_add_edge(s3, "3", "5", 3, 5, 4);
    graph_add_edge(s3, "4", "5", 4, 5, 5);
    printf("max flow: %d\n", graph_max_flow_fordfulkerson(s3, 0, 5));
    printf("max flow: %d\n", graph_max_flow_dinic(s3, 0, 5));
    graph_clear(s3);

    printf("\n");

    Graph *s4 = graph_new(7, 0);
    graph_add_edge(s4, "0", "1", 0, 1, 2);
    graph_add_edge(s4, "0", "2", 0, 2, 4);
    graph_add_edge(s4, "0", "3", 0, 3, 1);
    graph_add_edge(s4, "1", "3", 1, 3, 3);
    graph_add_edge(s4, "1", "4", 1, 4, 10);
    graph_add_edge(s4, "2", "3", 2, 3, 2);
    graph_add_edge(s4, "3", "4", 3, 4, 7);
    graph_add_edge(s4, "2", "5", 2, 5, 5);
    graph_add_edge(s4, "3", "5", 3, 5, 8);
    graph_add_edge(s4, "3", "6", 3, 6, 4);
    graph_add_edge(s4, "4", "6", 4, 6, 6);
    graph_add_edge(s4, "5", "6", 5, 6, 1);
    graph_mst_prim(s4);
    graph_print_mst_prim(s4);
    Node *edges[s4->n - 1];
    graph_mst_kruskal(s4, edges);
    graph_print_mst_kruskal(s4, edges);
    graph_clear(s4);

    printf("\n");

    Graph *s5 = graph_new(7, 0);
    graph_add_edge(s5, "A", "B", 0, 1, 0);
    graph_add_edge(s5, "A", "D", 0, 3, 0);
    graph_add_edge(s5, "B", "C", 1, 2, 0);
    graph_add_edge(s5, "C", "D", 2, 3, 0);
    graph_add_edge(s5, "C", "G", 2, 6, 0);
    graph_add_edge(s5, "D", "E", 3, 4, 0);
    graph_add_edge(s5, "D", "F", 3, 5, 0);
    graph_add_edge(s5, "E", "F", 4, 5, 0);
    List *list = graph_find_articulation_p(s5);
    graph_print_articulation(s5, list);
    list_clear(list);
    graph_coloring_greedy(s5);
    graph_print_color(s5);
    graph_m_coloring(s5, 3);
    graph_clear(s5);
}

int main() {
    graph();
    return 0;
}