//
// Created by Once on 2019/10/7.
//

#ifndef GRAPHTHEORY_DENSEGRAPH_H
#define GRAPHTHEORY_DENSEGRAPH_H

// 稠密图ADT，顶点为：0 <= x <= v-1
typedef struct densegraph{
    int v; // 顶点数
    int **matrix; //  邻接矩阵
} DenseGraph;


// 稠密图操作声明
extern DenseGraph *dgraph_new(int v);
extern int dgraph_add_edge(DenseGraph *graph, int u, int v);
extern void dgraph_bfs(DenseGraph *graph, int s);
extern void dgraph_dfs(DenseGraph *graph, int s);
extern int dgraph_clear(DenseGraph *graph);

#endif //GRAPHTHEORY_DENSEGRAPH_H
