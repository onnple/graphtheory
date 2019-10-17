# 图论算法（Graph Theory Glgorithms）

## 图的主要操作函数

### 1、创建一个图
extern Graph *graph_new(int n, int is_directed);

### 2、添加边
extern void graph_add_edge(Graph *graph, gdata ud, gdata vd, int u, int v, int w);

### 3、DFS遍历
extern void graph_dfs(Graph *graph, int s);

### 4、BFS遍历
extern void graph_bfs(Graph *graph, int s);

### 5、检查一个有向图是否有环
extern int graph_is_cyclic_directed(Graph *graph);

### 6、检查一个无向图是否有环
extern int graph_is_cyclic_undirected(Graph *graph);

### 7、拓扑排序
extern void graph_topsort_01(Graph *graph);

### 8、拓扑排序
extern void graph_topsort_02(Graph *graph);

### 9、求所有的拓扑排序
extern void graph_all_topsort(Graph *graph);

### 10、重置所有顶点的入度数
extern void graph_reset_indegree(Graph *graph);

### 11、按路径打印顶点
extern void graph_print_path(Graph *graph, int u, int v);

### 12、无权图的最短路径
extern void graph_shortest_path_unweighted(Graph *graph, int s);

### 13、有权图的最短路径
extern void graph_shortest_path_weighted_dijkstra(Graph *graph, int s);

### 14、具有负值边的最短路径
extern void graph_shortest_path_weighted_negative(Graph *graph, int s);

### 15、最大流算法
extern int graph_max_flow_fordfulkerson(Graph *graph, int s, int t);

### 16、最大流算法
extern int graph_max_flow_dinic(Graph *graph, int s, int t);

### 17、检查一个无向图是否是连通的
extern int graph_undirected_is_connected(Graph *graph);

### 18、打印prim最少生成树
extern void graph_print_mst_prim(Graph *graph);

### 19、prim最少生成树算法
extern void graph_mst_prim(Graph *graph);

### 20、kruskal最小生成树算法
extern void graph_mst_kruskal(Graph *graph, Node *edges[]);

### 21、kruskal最小生成树
extern void graph_print_mst_kruskal(Graph *graph, Node *edges[]);

### 22、查找割点
extern List *graph_find_articulation_p(Graph *graph);

### 23、打印割点
extern void graph_print_articulation(Graph *graph, List *list);

### 24、打印顶点的颜色
extern void graph_print_color(Graph *graph);

### 25、图着色
extern void graph_coloring_greedy(Graph *graph);

### 26、m着色问题
extern int graph_m_coloring(Graph *graph, int m);

### 27、清理图
extern int graph_clear(Graph *graph);

