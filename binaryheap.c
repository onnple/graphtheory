//
// Created by Once on 2019/10/12.
//

#include "binaryheap.h"
#include <stdlib.h>
#include <stdio.h>

BinaryHeap *bheap_new(int n){
    if(n < 1){
        perror("n is too small");
        return NULL;
    }
    BinaryHeap *heap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    if(!heap){
        perror("alloc for heap error");
        return NULL;
    }
    heap->n = n;
    heap->size = 0;
    heap->list = (BNode*)malloc(sizeof(BNode) * n);
    if(!heap->list){
        perror("alloc for list of heap error");
        free(heap);
        return NULL;
    }
    return heap;
}

int bheap_is_empty(BinaryHeap *heap){
    if(heap == NULL)
        return 1;
    return heap->size == 0;
}

static int parent(int i) { return (i-1)/2; }

static int left(int i) { return (2*i + 1); }

static int right(int i) { return (2*i + 2); }

static void swap(BNode *x, BNode *y){
    BNode temp = *x;
    x->key = y->key;
    x->data = y->data;
    y->key = temp.key;
    y->data = temp.data;
}

static void heapify(BinaryHeap *heap, int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap->size && heap->list[l].key < heap->list[i].key)
        smallest = l;
    if (r < heap->size && heap->list[r].key < heap->list[smallest].key)
        smallest = r;
    if (smallest != i)
    {
        swap(&heap->list[i], &heap->list[smallest]);
        heapify(heap, smallest);
    }
}

int bheap_push(BinaryHeap *heap, int key, hdata data){
    if(heap == NULL)
        return 0;
    if(heap->size == heap->n){
        perror("pushing overflow");
        return 0;
    }
    heap->size++;
    int i = heap->size - 1;
    heap->list[i].key = key;
    heap->list[i].data = data;
    while(i != 0 && heap->list[parent(i)].key > heap->list[i].key){
        swap(&heap->list[i], &heap->list[parent(i)]);
        i = parent(i);
    }
    return 1;
}

hdata bheap_top(BinaryHeap *heap){
    if(heap == NULL || heap->size == 0)
        return NULL;
    return heap->list[0].data;
}

hdata bheap_pop(BinaryHeap *heap){
    if(heap == NULL || heap->size == 0)
        return NULL;
    if (heap->size == 1){
        heap->size--;
        return heap->list[0].data;
    }
    hdata root = heap->list[0].data;
    heap->list[0] = heap->list[heap->size-1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

int bheap_decrease(BinaryHeap *heap, hdata data, int value){
    if(heap == NULL || heap->size == 0)
        return 0;
    int i = -1;
    for (int j = 0; j < heap->size; ++j) {
        if(heap->list[j].data == data){
            i = j;
            break;
        }
    }
    if(i == -1)
        return 0;
    heap->list[i].data = data;
    heap->list[i].key = value;
    while (i != 0 && heap->list[parent(i)].key > heap->list[i].key)
    {
        swap(&heap->list[i], &heap->list[parent(i)]);
        i = parent(i);
    }
    return 1;
}

int bheap_clear(BinaryHeap *heap){
    if(heap == NULL)
        return 0;
    free(heap->list);
    free(heap);
    return 1;
}
