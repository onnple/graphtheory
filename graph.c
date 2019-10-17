//
// Created by Once on 2019/10/11.
//

#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "list.h"
#include "binaryheap.h"
#include "disjset.h"

Graph *graph_new(int n, int is_directed){
    if(n < 2){
        perror("n is too small");
        return NULL;
    }
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    if(!graph){
        perror("alloc memory for graph error");
        return NULL;
    }
    graph->n = n;
    graph->e = 0;
    graph->is_directed = is_directed;
    graph->list = (Vertex*)malloc(n * sizeof(Vertex));
    if(!graph->list){
        perror("alloc memory for vertex list error");
        free(graph);
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        graph->list[i].src = i;
        graph->list[i].visited = 0;
        graph->list[i].color = -1;
        graph->list[i].indegree = 0;
        graph->list[i].cyclic = 0;
        graph->list[i].dist = INT_MAX;
        graph->list[i].path = -1;
        graph->list[i].data = NULL;
        graph->list[i].adjlist = NULL;
    }
    return graph;
}

static void adjlist_add_edge(Graph *grpah, int u, int v, int w){
    Node *head = grpah->list[u].adjlist;
    Node *node = (Node*)malloc(sizeof(Node));
    node->r = 0;
    node->src = u;
    node->dest = v;
    node->weight = w;
    node->flow = w;
    node->next = head;
    grpah->list[u].adjlist = node;
}

void graph_add_edge(Graph *graph, gdata ud, gdata vd, int u, int v, int w){
    if(graph == NULL || u < 0 || v < 0)
        return;
    graph->list[u].data = ud;
    graph->list[v].data = vd;
    adjlist_add_edge(graph, u, v, w);
    if(!graph->is_directed)
        adjlist_add_edge(graph, v, u, w);
    else
        graph->list[v].indegree++;
    graph->e++;
}

static void dfs(Graph *graph, int u){
    graph->list[u].visited = 1;
    printf("[%d %s] ", u, (char*)graph->list[u].data); // test
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        if(!graph->list[node->dest].visited){
            graph->list[node->dest].visited = 1;
            dfs(graph, node->dest);
        }
        node = node->next;
    }
}

void graph_dfs(Graph *graph, int s){
    if(graph == NULL || s < 0)
        return;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    dfs(graph, s);
    printf("\n");
}

void graph_bfs(Graph *graph, int s){
    if(graph == NULL || s < 0)
        return;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    Queue *queue = queue_new();
    graph->list[s].visited = 1;
    queue_push(queue, &graph->list[s]);
    Vertex *v;
    Node *node;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        printf("[%d %s] ", v->src, v->data); // test
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited){
                graph->list[node->dest].visited = 1;
                queue_push(queue, &graph->list[node->dest]);
            }
            node = node->next;
        }
    }
    printf("\n");
    free(queue);
}

static int is_cyclic_directed(Graph *graph, int u){
    if(!graph->list[u].visited){
        graph->list[u].visited = 1;
        graph->list[u].cyclic = 1;
        Node *node = graph->list[u].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited && is_cyclic_directed(graph, node->dest))
                return 1;
            else if(graph->list[node->dest].cyclic)
                return 1;
            node = node->next;
        }
    }
    graph->list[u].cyclic = 0;
    return 0;
}

int graph_is_cyclic_directed(Graph *graph){
    if(graph == NULL || !graph->is_directed)
        return 0;
    for (int j = 0; j < graph->n; ++j) {
        graph->list[j].visited = 0;
        graph->list[j].cyclic = 0;
    }
    for (int i = 0; i < graph->n; ++i)
        if(is_cyclic_directed(graph, i))
            return 1;
    return 0;
}

static int is_cyclic_undirected(Graph *graph, int u, int parent){
    graph->list[u].visited = 1;
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        if(!graph->list[node->dest].visited){
            if(is_cyclic_undirected(graph, node->dest, u))
                return 1;
        }
        else if(node->dest != parent)
            return 1;
        node = node->next;
    }
    return 0;
}

int graph_is_cyclic_undirected(Graph *graph){
    if(graph == NULL || graph->is_directed)
        return 0;
    for (int i = 0; i < graph->n; ++i)
        graph->list[i].visited = 0;
    for (int j = 0; j < graph->n; ++j)
        if(!graph->list[j].visited && is_cyclic_undirected(graph, j, -1))
            return 1;
    return 0;
}

void graph_topsort_01(Graph *graph){
    if(graph == NULL || !graph->is_directed)
        return;
    List *list = list_new();
    Queue *queue = queue_new();
    for (int i = 0; i < graph->n; ++i) {
        if (graph->list[i].indegree == 0)
            queue_push(queue, &graph->list[i]);
    }
    Vertex *v;
    Node *node;
    int count = 0;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        count++;
        list_push_back(list, v);
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(--graph->list[node->dest].indegree == 0)
                queue_push(queue, &graph->list[node->dest]);
            node = node->next;
        }
    }
    if(count != graph->n){
        printf("cycle found.\n");
        perror("cycle found in topological sorting");
        queue_clear(queue);
        list_clear(list);
        return;
    }
    LNode *n = list_begin(list);
    while(n != NULL){
        printf("[%d] ", ((Vertex*)(n->value))->src);
        n = list_next(list);
    }
    printf("\n");
    free(queue);
    list_clear(list);
}

static int topsort_02(Graph *graph, List *stack, int u){
    graph->list[u].visited = 1;
    graph->list[u].cyclic = 1;
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        if(!graph->list[node->dest].visited)
            return topsort_02(graph, stack, node->dest);
        else if(graph->list[node->dest].cyclic){
            printf("cycle found.\n");
            return 0;
        }
        node = node->next;
    }
    list_push_front(stack, &graph->list[u]);
    graph->list[u].cyclic = 0;
    return 1;
}

void graph_topsort_02(Graph *graph){
    if(graph == NULL || !graph->is_directed)
        return;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
        graph->list[i].cyclic = 0;
    }
    List *stack = list_new();
    for (int j = 0; j < graph->n; ++j) {
        if(!graph->list[j].visited)
            if(!topsort_02(graph, stack, j))
                break;
    }
    if(stack->size != graph->n){
        list_clear(stack);
        return;
    }
    LNode *n = list_begin(stack);
    while(n != NULL){
        printf("[%d] ", ((Vertex*)(n->value))->src);
        n = list_next(stack);
    }
    printf("\n");
    list_clear(stack);
}

static void all_topsort(Graph *graph, List *list){
    int flag = 0;
    Node *node;
    for (int i = 0; i < graph->n; ++i) {
        if(graph->list[i].indegree == 0 && !graph->list[i].visited){
            node = graph->list[i].adjlist;
            while(node != NULL){
                graph->list[node->dest].indegree--;
                node = node->next;
            }
            list_push_back(list, &graph->list[i]);
            graph->list[i].visited = 1;
            all_topsort(graph, list);

            node = graph->list[i].adjlist;
            while(node != NULL){
                graph->list[node->dest].indegree++;
                node = node->next;
            }
            list_pop_back(list);
            graph->list[i].visited = 0;
            flag = 1;
        }
    }
    if(!flag){
        LNode *n = list_begin(list);
        while(n != NULL){
            printf("[%d] ", ((Vertex*)n->value)->src);
            n = list_next(list);
        }
        printf("\n");
    }
}

void graph_all_topsort(Graph *graph){
    if(graph == NULL || !graph->is_directed)
        return;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
    }
    List *list = list_new();
    all_topsort(graph, list);
    list_clear(list);
}

static void reset_indegree(Graph *graph, int u){
    graph->list[u].visited = 1;
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        graph->list[node->dest].indegree++;
        if(!graph->list[node->dest].visited)
            reset_indegree(graph, node->dest);
        node = node->next;
    }
}

void graph_reset_indegree(Graph *graph){
    if(graph == NULL)
        return;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
        graph->list[i].indegree = 0;
    }
    for (int j = 0; j < graph->n; ++j) {
        if(!graph->list[j].visited)
            reset_indegree(graph, j);
    }
}

static void print_path(Graph *graph, int u){
    graph->list[u].visited = 1;
    if(graph->list[u].path != -1 && !graph->list[graph->list[u].path].visited)
        print_path(graph, graph->list[u].path);
    printf(" -> [%d, %s]", u, graph->list[u].data);
}

void graph_print_path(Graph *graph, int u, int v){
    if(graph == NULL || u < 0 || v < 0 || graph->list[u].dist != 0)
        return;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
    }
    print_path(graph, v);
    printf("\n");
}

void graph_shortest_path_unweighted(Graph *graph, int s){
    if(graph == NULL || s < 0)
        return;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].path = -1;
        graph->list[i].dist = INT_MAX;
    }
    Queue *queue = queue_new();
    graph->list[s].dist = 0;
    queue_push(queue, &graph->list[s]);
    Node *node;
    Vertex *v;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(graph->list[node->dest].dist == INT_MAX){
                graph->list[node->dest].dist = v->dist + 1;
                graph->list[node->dest].path = v->src;
                queue_push(queue, &graph->list[node->dest]);
            }
            node = node->next;
        }
    }
    free(queue);
}

void graph_shortest_path_weighted_dijkstra(Graph *graph, int s){
    if(graph == NULL || s < 0)
        return;
    BinaryHeap *heap = bheap_new(graph->n);
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
        graph->list[i].path = -1;
        graph->list[i].dist = INT_MAX;
        bheap_push(heap, graph->list[i].dist, &graph->list[i]);
    }
    graph->list[s].dist = 0;
    bheap_decrease(heap, &graph->list[s], graph->list[s].dist);
    Vertex *v = NULL;
    Node *node;
    while(1){
        v = bheap_pop(heap);
        if(v == NULL)
            break;
        v->visited = 1;
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited){
                if(v->dist + node->weight < graph->list[node->dest].dist){
                    graph->list[node->dest].dist = v->dist + node->weight;
                    bheap_decrease(heap, &graph->list[node->dest], v->dist + node->weight);
                    graph->list[node->dest].path = v->src;
                }
            }
            node = node->next;
        }
    }
    bheap_clear(heap);
}

void graph_shortest_path_weighted_negative(Graph *graph, int s){
    if(graph == NULL || s < 0)
        return;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].dist = INT_MAX;
        graph->list[i].path = -1;
    }
    int times[graph->n];
    for (int j = 0; j < graph->n; ++j)
        times[j] = 0;
    Queue *queue = queue_new();
    graph->list[s].dist = 0;
    queue_push(queue, &graph->list[s]);
    Node *node;
    Vertex *v;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(v->dist + node->weight < graph->list[node->dest].dist){
                graph->list[node->dest].dist = v->dist + node->weight;
                graph->list[node->dest].path = v->src;
                if(!queue_has(queue, &graph->list[node->dest])){
                    if(++times[node->dest] == graph->n + 1)
                        break;
                    queue_push(queue, &graph->list[node->dest]);
                }
            }
            node = node->next;
        }
    }
    free(queue);
}

static int min(int a, int b){
    if(a > b)
        return b;
    else
        return a;
}

static int edge_weight(Graph *graph, int u, int v){
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        if(node->dest == v)
            return node->weight;
        node = node->next;
    }
    return INT_MAX;
}

static void update_flow_positive(Graph *graph, int u, int v, int flow){
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        if(node->dest == v){
            node->flow -= flow;
            return; // 无平行边
        }
        node = node->next;
    }
}

static void update_flow_negative(Graph *graph, int u, int v, int flow){
    Node *node = graph->list[u].adjlist, *temp = NULL;
    while(node != NULL){
        if(node->dest == v){
            temp = node;
            break; // 无平行边
        }
        node = node->next;
    }
    if(temp == NULL){
        graph->list[u].data = NULL;
        graph->list[v].data = NULL;
        Node *head = graph->list[u].adjlist;
        node = (Node*)malloc(sizeof(Node));
        node->r = 1;
        node->dest = v;
        node->weight = INT_MIN;
        node->flow = flow; // residual flow
        node->next = head;
        graph->list[u].adjlist = node;
    }
    else{
        temp->flow += flow;
    }
}

static void release_negative_edge(Graph *graph){
    Node *node, *temp;
    for (int i = 0; i < graph->n; ++i) {
        node = graph->list[i].adjlist;
        while(node != NULL){
            temp = node->next;
            if(node->r == 1){
                free(node);
                if(node == graph->list[i].adjlist)
                    graph->list[i].adjlist = temp;
            }
            node = temp;
        }
    }
}

static int find_path_ff(Graph *graph, int s, int t){
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].path = -1;
        graph->list[i].visited = 0;
    }
    Queue *queue = queue_new();
    graph->list[s].visited = 1;
    queue_push(queue, &graph->list[s]);
    Vertex *v;
    Node *node;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited && node->flow > 0){
                graph->list[node->dest].visited = 1;
                graph->list[node->dest].path = v->src;
                queue_push(queue, &graph->list[node->dest]);
            }
            node = node->next;
        }
    }
    free(queue);
    return graph->list[t].visited;
}

int graph_max_flow_fordfulkerson(Graph *graph, int s, int t){
    if(graph == NULL || !graph->is_directed || s < 0 || t < 0 || s == t)
        return INT_MIN;
    Node *node;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].path = -1;
        graph->list[i].visited = 0;
        node = graph->list[i].adjlist;
        while(node != NULL){
            node->flow = node->weight;
            node = node->next;
        }
    }
    int max_flow = 0, flow = 0, v;
    while(find_path_ff(graph, s, t)){
        flow = INT_MAX;
        v = t;
        while(v != s){
            flow = min(flow, edge_weight(graph, graph->list[v].path, v));
            v = graph->list[v].path;
        }
        v = t;
        while(v != s){
            update_flow_positive(graph, graph->list[v].path, v, flow);
            update_flow_negative(graph, v, graph->list[v].path, flow);
            v = graph->list[v].path;
        }
        max_flow += flow;
    }
    release_negative_edge(graph);
    return max_flow;
}

static int find_path_dinic(Graph *graph, int s, int t){
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].level = -1;
    }
    Queue *queue = queue_new();
    graph->list[s].level = 0;
    queue_push(queue, &graph->list[s]);
    Vertex *v;
    Node *node;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(graph->list[node->dest].level == -1 && node->flow > 0){
                graph->list[node->dest].level = v->level + 1;
                queue_push(queue, &graph->list[node->dest]);
            }
            node = node->next;
        }
    }
    free(queue);
    return graph->list[t].level == -1 ? 0 : 1;
}

// DFS
static int send_max_flow(Graph *graph, int flow, int u, int t){
    if(u == t)
        return flow;
    Node *node = graph->list[u].adjlist;
    int min_flow, temp_flow;
    while(node != NULL){
        if(node->flow > 0 && graph->list[node->dest].level == graph->list[u].level + 1){
            min_flow = min(flow, node->flow);
            temp_flow = send_max_flow(graph, min_flow, graph->list[node->dest].src, t);
            if(temp_flow > 0){
                node->flow -= temp_flow;
                update_flow_negative(graph, node->dest, u, temp_flow);
                return temp_flow;
            }
        }
        node = node->next;
    }
    return 0;
}

int graph_max_flow_dinic(Graph *graph, int s, int t){
    if(graph == NULL || !graph->is_directed || s < 0 || t < 0 || s == t)
        return INT_MIN;
    Node *node;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].path = -1;
        graph->list[i].visited = 0;
        node = graph->list[i].adjlist;
        while(node != NULL){
            node->flow = node->weight;
            node = node->next;
        }
    }
    int max_flow = 0, flow = 0;
    while(find_path_dinic(graph, s, t)){
        while((flow = send_max_flow(graph, INT_MAX, s, t)) != 0)
            max_flow += flow;
    }
    release_negative_edge(graph);
    return max_flow;
}

int graph_undirected_is_connected(Graph *graph){
    if(graph == NULL || graph->is_directed)
        return 0;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
    }
    Queue *queue = queue_new();
    graph->list[0].visited = 1;
    queue_push(queue, &graph->list[0]);
    Vertex *v;
    Node *node;
    while(!queue_is_empty(queue)){
        v = queue_pop(queue);
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited){
                graph->list[node->dest].visited = 1;
                queue_push(queue, &graph->list[node->dest]);
            }
            node = node->next;
        }
    }
    free(queue);
    for (int j = 0; j < graph->n; ++j) {
        if(!graph->list[j].visited)
            return 0;
    }
    return 1;
}

void graph_print_mst_prim(Graph *graph){
    if(graph == NULL)
        return;
    for (int i = 0; i < graph->n; ++i) {
        printf("[%d %d] ", graph->list[i].src, graph->list[i].path);
    }
    printf("\n");
}

void graph_mst_prim(Graph *graph){
    if(graph == NULL || graph->is_directed || !graph_undirected_is_connected(graph))
        return;
    BinaryHeap *heap = bheap_new(graph->n);
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
        graph->list[i].path = -1;
        graph->list[i].d = INT_MAX;
        bheap_push(heap, graph->list[i].d, &graph->list[i]);
    }
    graph->list[0].visited = 1;
    graph->list[0].path = 0;
    graph->list[0].d = 0;
    bheap_decrease(heap, &graph->list[0], graph->list[0].d);
    Vertex *v = NULL;
    Node *node;
    while(1){
        v = bheap_pop(heap);
        if(v == NULL)
            break;
        v->visited = 1;
        node = graph->list[v->src].adjlist;
        while(node != NULL){
            if(!graph->list[node->dest].visited){
                if(node->weight < graph->list[node->dest].d){
                    graph->list[node->dest].d = node->weight;
                    bheap_decrease(heap, &graph->list[node->dest], node->weight);
                    graph->list[node->dest].path = v->src;
                }
            }
            node = node->next;
        }
    }
    bheap_clear(heap);
}

void graph_mst_kruskal(Graph *graph, Node *edges[]){
    if(graph == NULL || graph->is_directed || !graph_undirected_is_connected(graph))
        return;
    BinaryHeap *heap = bheap_new(2 * graph->e);
    Node *node;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].path = -1;
        node = graph->list[i].adjlist;
        while(node != NULL){
            bheap_push(heap, node->weight, node);
            node = node->next;
        }
    }
    Disjset *disjset = disjset_new(graph->n);
    int count = 0;
    while(count < graph->n - 1){
        node = bheap_pop(heap);
        if(!disjset_union(disjset, node->src, node->dest)){
            edges[count] = node;
            count++;
        }
    }
    bheap_clear(heap);
    disjset_clear(disjset);
}

void graph_print_mst_kruskal(Graph *graph, Node *edges[]){
    if(graph == NULL || edges == NULL)
        return;
    for (int i = 0; i < graph->n - 1; ++i) {
        printf("[%d %d] ", edges[i]->src, edges[i]->dest);
    }
    printf("\n");
}

static void find_articulation_p(Graph *graph, List *list, int u, int *counter, int *root, int *r){
    graph->list[u].visited = 1;
    Node *node = graph->list[u].adjlist;
    graph->list[u].low = graph->list[u].num = (*counter)++;  // 1 初始化编号
    while(node != NULL){
        if(!graph->list[node->dest].visited){ // 向前的边
            graph->list[node->dest].path = node->src;
            find_articulation_p(graph, list, node->dest, counter, root, r); // DFS
            if(node->src == *r)
                (*root)++;
            if(graph->list[node->dest].low >= graph->list[u].num){
                if(node->src == *r){
                    if(*root >= 2)
                        list_push_back(list, &graph->list[u]);
                }
                else
                    list_push_back(list, &graph->list[u]);
            }
            graph->list[u].low = min(graph->list[u].low, graph->list[node->dest].low); // 3
        }
        else if(graph->list[u].path != node->dest) // 背向边
            graph->list[u].low = min(graph->list[u].low, graph->list[node->dest].num); // 2
        node = node->next;
    }
}

List *graph_find_articulation_p(Graph *graph){
    if(graph == NULL || graph->is_directed)
        return NULL;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].visited = 0;
        graph->list[i].path = -1;
    }
    int counter = 0, r = 0, root = 0;
    List *list = list_new();
    find_articulation_p(graph, list, r, &counter, &root, &r);
    return list;
}

void graph_print_articulation(Graph *graph, List *list){
    if(graph == NULL || list == NULL || graph->is_directed)
        return;
    LNode *node = list_begin(list);
    while(node != list_end(list)){
        printf("[%d %s] ", ((Vertex*)node->value)->src, ((Vertex*)node->value)->data);
        node = list_next(list);
    }
    printf("\n");
}

void graph_print_color(Graph *graph){
    if(graph == NULL)
        return;
    for (int i = 0; i < graph->n; ++i) {
        printf("{%s %d} ", graph->list[i].data, graph->list[i].color);
    }
    printf("\n");
}

void graph_coloring_greedy(Graph *graph){
    if(graph == NULL)
        return;
    int available[graph->n];
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].color = -1;
        available[i] = 0;
    }
    graph->list[0].color = 0;
    Node *node;
    int c;
    for (int j = 1; j < graph->n; ++j) {
        node = graph->list[j].adjlist;
        while(node != NULL){
            if(graph->list[node->dest].color != -1)
                available[graph->list[node->dest].color] = 1;
            node = node->next;
        }
        for (c = 0; c < graph->n; ++c) {
            if(!available[c])
                break;
        }
        graph->list[j].color = c;
        node = graph->list[j].adjlist;
        while(node != NULL){
            if(graph->list[node->dest].color != -1)
                available[graph->list[node->dest].color] = 0;
            node = node->next;
        }
    }
}

static int is_safe(Graph *graph, int u, int c){
    Node *node = graph->list[u].adjlist;
    while(node != NULL){
        if(graph->list[node->dest].color == c)
            return 0;
        node = node->next;
    }
    return 1;
}

static int m_coloring(Graph *graph, int m, int u){
    if(graph->n == u)
        return 1;
    for (int c = 0; c < m; ++c) {
        if(is_safe(graph, u, c)){
            graph->list[u].color = c;
            if(m_coloring(graph, m, u + 1))
                return 1;
            graph->list[u].color = 0;
        }
    }
    return 0;
}

int graph_m_coloring(Graph *graph, int m){
    if(graph == NULL || m < 0)
        return 0;
    for (int i = 0; i < graph->n; ++i) {
        graph->list[i].color = 0;
    }
    if(!m_coloring(graph, m, 0)){
        printf("solution does not exist");
        return 0;
    }
    graph_print_color(graph);
    return 1;
}

int graph_clear(Graph *graph){
    if(graph == NULL)
        return 0;
    Node *node, *temp;
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