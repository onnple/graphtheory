//
// Created by Once on 2019/10/9.
//

#include "sparsegraph.h"
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

SparseGraph *sgraph_new(int n){
    if(n < 1){
        perror("n is too small");
        return NULL;
    }
    SparseGraph *graph = (SparseGraph*)malloc(sizeof(SparseGraph));
    if(!graph){
        perror("alloc for graph error");
        return NULL;
    }
    graph->n = n;
    graph->lists = (List**)malloc(n * sizeof(List*));
    if(!graph->lists){
        perror("alloc for lists error");
        free(graph);
        return NULL;
    }
    for (int i = 0; i < n; ++i)
        graph->lists[i] = list_new();
    return graph;
}

void sgraph_add_edge(SparseGraph *graph, int u, int v){
    if(graph == NULL)
        return;
    list_push_back(graph->lists[u], (ldata)v);
    list_push_back(graph->lists[v], (ldata)u);
}

void sgraph_dfs(SparseGraph *graph, int s){
    if(graph == NULL || graph->n < 1 || graph->lists == NULL)
        return;
    int visited[graph->n];
    for (int i = 0; i < graph->n; ++i)
        visited[i] = 0;
    visited[s] = 1;
    List *stack = list_new();
    list_push_front(stack, (ldata)s);
    int d;
    LNode *node;
    while(!list_is_empty(stack)){
        d = (int)list_front(stack);
        printf("%d ", d);
        list_pop_front(stack);
        node = list_begin(graph->lists[d]);
        while(node != NULL){
            if(!visited[(int)node->value]){
                visited[(int)node->value] = 1;
                list_push_front(stack, node->value);
            }
            node = list_next(graph->lists[d]);
        }
    }
    free(stack);
    printf("\n");
}

void sgraph_bfs(SparseGraph *graph, int s){
    if(graph == NULL || graph->n < 1 || graph->lists == NULL)
        return;
    int visited[graph->n];
    for (int i = 0; i < graph->n; ++i)
        visited[i] = 0;
    visited[s] = 1;
    Queue *queue = queue_new();
    queue_push(queue, (qdata)s);
    int d;
    LNode *node;
    while(!queue_is_empty(queue)){
        d = (int)queue_pop(queue);
        printf("%d ", d);
        node = list_begin(graph->lists[d]);
        while(node != NULL){
            if(!visited[(int)node->value]){
                visited[(int)node->value] = 1;
                queue_push(queue, node->value);
            }
            node = list_next(graph->lists[d]);
        }
    }
    queue_clear(queue);
    printf("\n");
}

int sgraph_clear(SparseGraph *graph){
    if(graph == NULL)
        return 0;
    for (int i = 0; i < graph->n; ++i) {
        list_clear(graph->lists[i]);
    }
    free(graph->lists);
    free(graph);
    return 1;
}
