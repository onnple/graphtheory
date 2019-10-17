//
// Created by Once on 2019/10/10.
//

#ifndef GRAPHTHEORY_DISJSET_H
#define GRAPHTHEORY_DISJSET_H

typedef struct disjset{
    int n;
    int *parent;
    int *rank;
} Disjset;

extern Disjset *disjset_new(int n);
extern int disjset_make_set(Disjset *disjset);
extern int disjset_find(Disjset *disjset, int x);
extern int disjset_union(Disjset *disjset, int x, int y);
extern int disjset_clear(Disjset *disjset);

#endif //GRAPHTHEORY_DISJSET_H
