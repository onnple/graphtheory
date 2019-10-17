//
// Created by Once on 2019/10/8.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *queue_new(void){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if(!queue){
        perror("alloc for queue error");
        return NULL;
    }
    queue->head = queue->tail = NULL;
    queue->size = 0;
    return queue;
}

int queue_is_empty(Queue *queue){
    if(queue == NULL)
        return 1;
    return queue->size == 0;
}

int queue_push(Queue *queue, qdata value){
    if(queue == NULL)
        return 0;
    QNode *node = (QNode*)malloc(sizeof(QNode));
    if(!node){
        perror("push fail");
        return 0;
    }
    node->prev = node->next = NULL;
    node->value = value;
    if(queue->size == 0){
        queue->head = queue->tail = node;
        node->prev = node->next = node;
        queue->size++;
        return 1;
    }
    QNode *tail = queue->tail;
    tail->next = node;
    node->prev = tail;
    node->next = queue->head;
    queue->head->prev = node;
    queue->tail = node;
    queue->size++;
    return 1;
}

qdata queue_pop(Queue *queue){
    if(queue == NULL || queue->size < 1)
        return NULL;
    QNode *head = queue->head;
    qdata value = head->value;
    queue->tail->next = head->next;
    head->next->prev = queue->tail;
    queue->head = head->next;
    free(head);
    queue->size--;
    return value;
}

int queue_has(Queue *queue, qdata value){
    if(queue == NULL || queue->size == 0)
        return 0;
    QNode *node = queue->head;
    do{
        if(node->value == value)
            return 1;
        node = node->next;
    }
    while(node != queue->head && queue->size > 0);
    return 0;
}

int queue_clear(Queue *queue){
    if(queue == NULL)
        return 0;
    QNode *node = queue->head, *temp = NULL;
    if(queue->tail != NULL)
        queue->tail->next = NULL;
    while(node != NULL){
        temp = node->next;
        free(node);
        node = temp;
    }
    free(queue);
    return 1;
}