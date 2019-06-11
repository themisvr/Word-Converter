#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "priority_queue.h"


p_queue *create_pqnode(list_node *list, uint32_t pnum) {
    /* creating a node with the given data and return the node itself */

    /* error checking for NULL pointers */
    assert(list != NULL);
    p_queue *pqueue = (p_queue *)malloc(sizeof(p_queue));
    assert(pqueue != NULL);
    pqueue->list = list;
    pqueue->priority_num = pnum;
    pqueue->next = NULL;

    return pqueue;
}

void push_pqnode(p_queue **pqueue, list_node *list, uint32_t pnum) {

    /* error checking for NULL pointers */
    assert(pqueue != NULL);
    assert(list != NULL);

    p_queue *start = (*pqueue);
    /* create new node */
    p_queue *new_pqnode = create_pqnode(list, pnum);

    /* the head has lesser priority than the new node we created */
    /* so we insert new node before head and change head node */
    /* NOTE:: greater priority number lesser priority */
    if((*pqueue)->priority_num > pnum) {
        new_pqnode->next = (*pqueue);
        (*pqueue) = new_pqnode;
    }
    else {
        /* traverse the priority queue and find the right position to insert the node */
        while((start->next != NULL) && (start->next->priority_num < pnum)) {
            start = start->next;
        }
        new_pqnode->next = start->next;
        start->next = new_pqnode;
    }
}

p_queue *pop_pqnode(p_queue *pqueue) {

    assert(pqueue != NULL);

    p_queue *temp = pqueue;
    pqueue = pqueue->next;
    return temp;
}

void delete_pqnode(p_queue **head, p_queue *delete) {

    assert(head != NULL);
    assert(delete != NULL);

    p_queue *temp_pqnode = *head;
    if((*head) == delete) {
        (*head) = (*head)->next;
        free_list(delete->list);
        free(delete);
    }
    else {
        while(temp_pqnode->next != delete) {
            temp_pqnode = temp_pqnode->next;
        }
        temp_pqnode->next = temp_pqnode->next->next;
        free_list(delete->list);
        free(delete);
    }
}

void free_pqueue(p_queue **pqueue) {

	p_queue *tmp_pqnode = (*pqueue);
    while (tmp_pqnode->next != NULL) {
    	p_queue *to_delete = tmp_pqnode->next;
    	tmp_pqnode->next = tmp_pqnode->next->next;
    	free_list(to_delete->list);
    	free(to_delete);
    	to_delete = NULL;
    }
    free_list(tmp_pqnode->list);
    free(tmp_pqnode);
}
