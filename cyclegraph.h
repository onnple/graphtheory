//
// Created by Once on 2019/10/10.
//

#ifndef GRAPHTHEORY_CYCLEGRAPH_H
#define GRAPHTHEORY_CYCLEGRAPH_H

typedef char string[128];

typedef struct cnode{ // 边edge
    int dest; // 结束顶点
    int weight; // 权值
    struct cnode *next; // 下一个邻接的顶点
} CNode;

typedef struct cvertex{ // 顶点vertex
    int color;
    int visited; // 访问标记
    int cycle; // 一次dfs标记
    int src; // 开始顶点
    string name; // 顶点的名称
    CNode *adjlist; // 该顶点的邻接表
} CVertex;

typedef struct cyclegraph{ // 图graph
    int n; // 顶点数量
    int is_directed; // 是否为有向图
    CVertex *list; // 邻接表数组（顶点数组）
} CycleGraph;

extern CycleGraph *cgraph_new(int n, int is_directed);
extern void cgraph_add_edge(CycleGraph *graph, const char uname[], const char vname[], int u, int v, int w);
extern void cgraph_dfs(CycleGraph *graph, int s);
extern void cgraph_bfs(CycleGraph *graph, int s);
// 使用一般DFS方式检测有向图是否有圈
extern int cgraph_is_cyclic_directed_normal(CycleGraph *graph);
// 使用着色的方式检测有向图是否有圈
extern int cgraph_is_cyclic_directed_color(CycleGraph *graph);
// 一般方式检测无向图是否有圈
extern int cgraph_is_cyclic_undirected_normal(CycleGraph *graph);
// 使用不相交集检测无向图是否有圈
extern int cgraph_is_cyclic_undirected_disjset(CycleGraph *graph);
extern int cgraph_clear(CycleGraph *graph);

#endif //GRAPHTHEORY_CYCLEGRAPH_H
