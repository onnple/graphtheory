//
// Created by Once on 2019/10/9.
//

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

List *list_new(void){
    List *list = (List*)malloc(sizeof(List));
    if(!list){
        perror("alloc for list error");
        return NULL;
    }
    list->head = list->tail = list->temp_node = NULL;
    list->size = 0;
    return list;
}

int list_is_empty(List *list){
    if(list == NULL)
        return 1;
    return list->size == 0;
}

static LNode *node_new(ldata value){
    LNode *node = (LNode*)malloc(sizeof(LNode));
    if(!node){
        perror("alloc for node error");
        return NULL;
    }
    node->next = node->prev = NULL;
    node->value = value;
    return node;
}

int list_push_front(List *list, ldata value){
    if(list == NULL)
        return 0;
    LNode *node = node_new(value);
    if(!node)
        return 0;
    if(list->size == 0){
        node->prev = node->next = node;
        list->head = list->tail = node;
        list->size++;
        return 1;
    }
    LNode *head = list->head;
    node->next = head;
    node->prev = list->tail;
    head->prev = node;
    list->tail->next = node;
    list->head = node;
    list->size++;
    return 1;
}

int list_push_back(List *list, ldata value){
    if(list == NULL)
        return 0;
    LNode *node = node_new(value);
    if(!node)
        return 0;
    if(list->size == 0){
        node->prev = node->next = node;
        list->head = list->tail = node;
        list->size++;
        return 1;
    }
    LNode *tail = list->tail;
    node->next = list->head;
    node->prev = tail;
    tail->next = node;
    list->head->prev = node;
    list->tail = node;
    list->size++;
    return 1;
}

int list_delete(List *list, ldata value){
    if(list == NULL || list->size <= 0)
        return 0;
    LNode *node = list->head, *temp;
    do{
        if(node->value == value){
            temp = node->next;
            node->prev->next = temp;
            temp->prev = node->prev;
            free(node);
            list->size--;
            return 1;
        }
        node = node->next;
    }
    while(node != list->head && list->size > 0);
    return 0;
}

ldata list_front(List *list){
    if(list == NULL || list->size < 1)
        return NULL;
    return list->head->value;
}

ldata list_back(List *list){
    if(list == NULL || list->size < 1)
        return NULL;
    return list->tail->value;
}

void list_pop_front(List *list){
    if(list == NULL || list->size < 1)
        return;
    LNode *head = list->head;
    list->tail->next = head->next;
    head->next->prev = list->tail;
    list->head = head->next;
    free(head);
    list->size--;
}

void list_pop_back(List *list){
    if(list == NULL || list->size < 1)
        return;
    LNode *tail = list->tail;
    list->head->prev = tail->prev;
    tail->prev->next = list->head;
    list->tail = tail->prev;
    free(tail);
    list->size--;
}

LNode *list_begin(List *list){
    if(list == NULL || list->size < 1)
        return NULL;
    list->temp_node = list->head;
    return list->temp_node;
}

LNode *list_next(List *list){
    if(list == NULL || list->size < 1)
        return NULL;
    if(list->temp_node->next != list->head){
        list->temp_node = list->temp_node->next;
        return list->temp_node;
    }
    return NULL;
}

LNode *list_end(List *list){
    return NULL;
}

int list_clear(List *list){
    if(list == NULL)
        return 0;
    if(list->size > 0){
        LNode *node = list->head, *temp = NULL;
        if(list->tail != NULL)
            list->tail->next = NULL;
        while(node != NULL){
            temp = node->next;
            free(node);
            node = temp;
        }
    }
    free(list);
    return 1;
}