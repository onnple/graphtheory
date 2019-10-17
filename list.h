//
// Created by Once on 2019/10/9.
//

#ifndef GRAPHTHEORY_LIST_H
#define GRAPHTHEORY_LIST_H

typedef void* ldata;

typedef struct lnode{
    ldata value;
    struct lnode *next;
    struct lnode *prev;
} LNode;

typedef struct list{
    LNode *head;
    LNode *tail;
    int size;
    LNode *temp_node;
} List;

extern List *list_new(void);
extern int list_is_empty(List *list);
extern int list_push_front(List *list, ldata value);
extern int list_push_back(List *list, ldata value);
extern int list_delete(List *list, ldata value);
extern ldata list_front(List *list);
extern ldata list_back(List *list);
extern void list_pop_front(List *list);
extern void list_pop_back(List *list);
extern LNode *list_next(List *list);
extern LNode *list_begin(List *list);
extern LNode *list_end(List *list);
extern int list_clear(List *list);

#endif //GRAPHTHEORY_LIST_H
