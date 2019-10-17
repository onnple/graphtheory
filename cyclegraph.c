//
// Created by Once on 2019/10/10.
//

#include "cyclegraph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "disjset.h"

CycleGraph *cgraph_new(int n, int is_directed){
    if(n < 2){
        perror("n is too small");
        return NULL;
    }
    CycleGraph *graph = (CycleGraph*)malloc(sizeof(CycleGraph));
    if(!graph){
        perror("alloc for graph error");
        return NULL;
    }
    graph->n = n;
    graph->is_directed = is_directed;
    graph->list = (CVertex*)malloc(sizeof(CVertex) * n);
    if(!graph->list){
        perror("alloc for vertices error");
        free(graph);
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        graph->list[i].src = i;
        graph->list[i].visited = 0;
        graph->list[i].cycle = 0;
        graph->list[i].adjlist = NULL;
    }
    return graph;
}

static void adjlist_add_edge(CycleGraph *graph, int u, int v, int w){
    CNode *node = graph->list[u].adjlist;
    CNode *head = (CNode*)malloc(sizeof(CNode));
    head->dest = v;
    head->weight = w;
    head->next = node;
    graph->list[u].adjlist = head;
}

void cgraph_add_edge(CycleGraph *graph, const char uname[], const char vname[], int u, int v, int w){
    if(graph == NULL || uname == NULL || u < 0 || v < 0)
        return;
    strcpy(graph->list[u].name, uname);
    strcpy(graph->list[v].name, vname);
    adjlist_add_edge(graph, u, v, w);
    if(!graph->is_directed)
        adjlist_add_edge(graph, v, u, w);
}

static void dfs(CycleGraph *graph, int u){
    printf("[%d %s] ", u, graph->list[u].name);
    graph->list[u].visited = 1;
    CNode *edge = graph->list[u].adjlist;
    while(edge != NULL){
        if(!graph->list[edge->dest].visited)
            dfs(graph, edge->dest);
        edge = edge->next;
    }
}

void cgraph_dfs(CycleGraph *graph, int s){
    if(graph == NULL)
        return;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    dfs(graph, s);
    printf("\n");
}

void cgraph_bfs(CycleGraph *graph, int s){
    if(graph == NULL)
        return;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    Queue *queue = queue_new();
    queue_push(queue, &graph->list[s]);
    graph->list[s].visited = 1;
    CVertex *vertex;
    CNode *node;
    while(!queue_is_empty(queue)){
        vertex = queue_pop(queue);
        printf("[%d %s] ", vertex->src, vertex->name);
        node = vertex->adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited){
                graph->list[node->dest].visited = 1;
                queue_push(queue, &graph->list[node->dest]);
            }
            node = node->next;
        }
    }
    printf("\n");
}

static int is_cyclic_directed_normal(CycleGraph *graph, int u){
    if(!graph->list[u].visited){
        graph->list[u].visited = 1;
        graph->list[u].cycle = 1;
        CNode *node = graph->list[u].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited && is_cyclic_directed_normal(graph, node->dest))
                return 1;
            else if(graph->list[node->dest].cycle)
                return 1;
            node = node->next;
        }
    }
    graph->list[u].cycle = 0;
    return 0;
}

int cgraph_is_cyclic_directed_normal(CycleGraph *graph){
    if(graph == NULL || !graph->is_directed)
        return 0;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    for (int j = 0; j < graph->n; ++j)
        if(is_cyclic_directed_normal(graph, j))
            return 1;
    return 0;
}

static int is_cyclic_directed_color(CycleGraph *graph, int u){
    graph->list[u].color = 2;
    CNode *node = graph->list[u].adjlist;
    while(node != NULL){
        if(graph->list[node->dest].color == 2)
            return 1;
        else if(graph->list[node->dest].color == 1 && is_cyclic_directed_color(graph, node->dest))
            return 1;
        node = node->next;
    }
    graph->list[u].color = 3;
    return 0;
}

int cgraph_is_cyclic_directed_color(CycleGraph *graph){
    if(graph == NULL || !graph->is_directed)
        return 0;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].color = 1;
    for (int j = 0; j < graph->n; ++j)
        if(graph->list[j].color == 1)
            if(is_cyclic_directed_color(graph, j))
                return 1;
    return 0;
}

static int is_cyclic_undirected_normal(CycleGraph *graph, int u, int parent){
    graph->list[u].visited = 1;
    CNode *node = graph->list[u].adjlist;
    while(node != NULL){
        if(!graph->list[node->dest].visited){
            if(is_cyclic_undirected_normal(graph, node->dest, u))
                return 1;
        }
        else if(node->dest != parent)
            return 1;
        node = node->next;
    }
    return 0;
}

int cgraph_is_cyclic_undirected_normal(CycleGraph *graph){
    if(graph == NULL || graph->is_directed)
        return 0;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    for (int j = 0; j < graph->n; ++j)
        if(!graph->list[j].visited && is_cyclic_undirected_normal(graph, j, -1))
            return 1;
    return 0;
}

int cgraph_is_cyclic_undirected_disjset(CycleGraph *graph){
    if(graph == NULL || graph->is_directed)
        return 0;
    CNode *node;
    Disjset *disjset = disjset_new(graph->n);
    for (int j = 0; j < graph->n; ++j)
        graph->list[j].visited = 0;
    for (int i = 0; i < graph->n; ++i) {
        node = graph->list[i].adjlist;
        graph->list[i].visited = 1;
        while(node != NULL){
            if(!graph->list[node->dest].visited && disjset_union(disjset, i, node->dest))
                return 1;
            node = node->next;
        }
    }
    disjset_clear(disjset);
    return 0;
}

int cgraph_clear(CycleGraph *graph){
    if(graph == NULL)
        return 0;
    CNode *node, *temp;
    for (int i = 0; i < graph->n; ++i) {
        node = graph->list[i].adjlist;
        while(node != NULL){
            temp = node->next;
            free(node);
            node = temp;
        }
    }
    free(graph->list);
    free(graph);
    return 1;
}