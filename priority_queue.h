#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdint.h>
#include "list.h"

typedef struct p_queue{
    list_node *list;
    uint32_t priority_num; // lower value means higher priority */
    struct p_queue *next;
} p_queue;


p_queue *create_pqnode(list_node *, uint32_t);
void push_pqnode(p_queue **, list_node *, uint32_t);
p_queue *pop_pqnode(p_queue *);
void delete_pqnode(p_queue **, p_queue *);
void free_pqueue(p_queue **);



#endif //PRIORITY_QUEUE_H
