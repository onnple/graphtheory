//
// Created by Once on 2019/10/8.
//

#ifndef GRAPHTHEORY_QUEUE_H
#define GRAPHTHEORY_QUEUE_H

typedef void* qdata;

typedef struct qnode{
    qdata *value;
    struct qnode *next;
    struct qnode *prev;
} QNode;

typedef struct queue{
    QNode *head;
    QNode *tail;
    int size;
} Queue;

extern Queue *queue_new(void);
extern int queue_is_empty(Queue *queue);
extern int queue_push(Queue *queue, qdata value);
extern qdata queue_pop(Queue *queue);
extern int queue_has(Queue *queue, qdata value);
extern int queue_clear(Queue *queue);

#endif //GRAPHTHEORY_QUEUE_H
