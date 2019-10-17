//
// Created by Once on 2019/10/10.
//

#include "disjset.h"
#include <stdlib.h>
#include <stdio.h>

Disjset *disjset_new(int n){
    if(n < 1){
        perror("n is too small");
        return NULL;
    }
    Disjset *disjset = (Disjset*)malloc(sizeof(Disjset));
    disjset->n = n;
    disjset->parent = (int*)malloc(sizeof(int) * n);
    if(!disjset->parent){
        perror("alloc for parent error");
        free(disjset);
        return NULL;
    }
    disjset_make_set(disjset);
    disjset->rank = (int*)malloc(sizeof(int) * n);
    if(!disjset->rank){
        perror("alloc for rank error");
        free(disjset);
        free(disjset->parent);
        return NULL;
    }
    for (int i = 0; i < n; ++i)
        disjset->rank[i] = 0;
    return disjset;
}

int disjset_make_set(Disjset *disjset){
    if(disjset == NULL || disjset->parent == NULL)
        return 0;
    for (int i = 0; i < disjset->n; ++i)
        disjset->parent[i] = i;
    return 1;
}

int disjset_find(Disjset *disjset, int x){
    if(disjset == NULL)
        return -1;
    while(x != disjset->parent[x]){
        disjset->parent[x] = disjset->parent[disjset->parent[x]];
        x = disjset->parent[x];
    }
    return x;
}

int disjset_union(Disjset *disjset, int x, int y){
    if(disjset == NULL)
        return 0;
    int x_root = disjset_find(disjset, x);
    int y_root = disjset_find(disjset, y);
    if(x_root == y_root)
        return 1;
    if(disjset->rank[x_root] > disjset->rank[y_root])
        disjset->parent[y_root] = x_root;
    else if(disjset->rank[x_root] < disjset->rank[y_root])
        disjset->parent[x_root] = y_root;
    else{
        disjset->parent[x_root] = y_root;
        disjset->rank[y_root]++;
    }
    return 0;
}

int disjset_clear(Disjset *disjset){
    if(disjset == NULL)
        return 0;
    free(disjset->parent);
    free(disjset->rank);
    free(disjset);
    return 1;
}