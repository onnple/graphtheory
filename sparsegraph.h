//
// Created by Once on 2019/10/9.
//

#ifndef GRAPHTHEORY_SPARSEGRAPH_H
#define GRAPHTHEORY_SPARSEGRAPH_H

#include "list.h"

typedef struct sparsegraph{
    int n;
    List **lists;
} SparseGraph;

extern SparseGraph *sgraph_new(int n);
extern void sgraph_add_edge(SparseGraph *graph, int u, int v);
extern void sgraph_dfs(SparseGraph *graph, int s);
extern void sgraph_bfs(SparseGraph *graph, int s);
extern int sgraph_clear(SparseGraph *graph);

#endif //GRAPHTHEORY_SPARSEGRAPH_H
