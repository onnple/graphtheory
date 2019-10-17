//
// Created by Once on 2019/10/12.
//

#ifndef GRAPHTHEORY_BINARYHEAP_H
#define GRAPHTHEORY_BINARYHEAP_H

typedef void* hdata;

typedef struct bnode{
    int key;
    hdata data;
} BNode;

// minimum heap
typedef struct binaryheap{
    int n;
    int size;
    BNode *list;
} BinaryHeap;

extern BinaryHeap *bheap_new(int n);
extern int bheap_is_empty(BinaryHeap *heap);
extern int bheap_push(BinaryHeap *heap, int key, hdata data);
extern hdata bheap_top(BinaryHeap *heap);
extern hdata bheap_pop(BinaryHeap *heap);
extern int bheap_decrease(BinaryHeap *heap, hdata data, int value);
extern int bheap_clear(BinaryHeap *heap);

#endif //GRAPHTHEORY_BINARYHEAP_H
