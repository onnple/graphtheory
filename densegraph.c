//
// Created by Once on 2019/10/7.
//

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "densegraph.h"

DenseGraph *dgraph_new(int v){
    if(v < 2){
        perror("count of vertex is too small");
        return NULL;
    }
    DenseGraph *graph = (DenseGraph*)malloc(sizeof(DenseGraph));
    if(!graph){
        perror("alloc for graph error");
        return NULL;
    }
    graph->v = v;
    graph->matrix = (int**)malloc(v * sizeof(int*));
    if(!graph->matrix){
        perror("alloc for matrix error");
        free(graph);
        return NULL;
    }
    for (int i = 0; i < v; ++i) {
        graph->matrix[i] = (int*)malloc(v * sizeof(int));
        for (int j = 0; j < v; ++j)
            graph->matrix[i][j] = 0;
    }
    return graph;
}

int dgraph_add_edge(DenseGraph *graph, int u, int v){
    if(graph == NULL || graph->v < 2 || graph->matrix == NULL)
        return 0;
    graph->matrix[u][v] = 1;
    graph->matrix[v][u] = 1;
    return 1;
}

static void bfs(DenseGraph *graph, int s){
    Queue *queue = queue_new();
    int visited[graph->v];
    for (int k = 0; k < graph->v; ++k)
        visited[k] = 0;
    visited[s] = 1;
    queue_push(queue, (qdata)s);
    int d;
    while(!queue_is_empty(queue)){
        d = (int)queue_pop(queue);
        printf("%d ", (int)d);
        for (int i = 0; i < graph->v; ++i)
            if(graph->matrix[d][i] && !visited[i]){
                visited[i] = 1;
                queue_push(queue, (qdata)i);
            }
    }
    queue_clear(queue);
    printf("\n");
}

void dgraph_bfs(DenseGraph *graph, int s){
    if(graph == NULL || graph->v < 2 || graph->matrix == NULL)
        return;
    bfs(graph, s);
}

static void dfs(DenseGraph *graph, int visited[], int u){
    visited[u] = 1;
    printf("%d ", u);
    for (int i = 0; i < graph->v; ++i) {
        if(graph->matrix[u][i] && !visited[i]){
            dfs(graph, visited, i);
        }
    }
}

void dgraph_dfs(DenseGraph *graph, int s){
    if(graph == NULL || graph->v < 2 || graph->matrix == NULL)
        return;
    int visited[graph->v];
    for (int i = 0; i < graph->v; ++i) {
        visited[i] = 0;
    }
    dfs(graph, visited, s);
    printf("\n");
}

int dgraph_clear(DenseGraph *graph){
    if(graph == NULL)
        return 0;
    for (int i = 0; i < graph->v; ++i)
        free(graph->matrix[i]);
    free(graph->matrix);
    free(graph);
    return 1;
}