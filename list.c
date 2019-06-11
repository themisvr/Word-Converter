#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

list_node *Create() {

    list_node *dummy;
    dummy = (list_node *)malloc(sizeof(list_node));
    if(dummy == NULL) {
    	fprintf(stderr, "Error:Cannot allocate memory\n");
    	return NULL;
    }
    dummy->next = NULL;

    return dummy;
}

void print_list(list_node *head) {

    if(head == NULL) {
        printf("The word list is empty\n");
        return;
    }

    list_node *start;
    for(start = head->next; start != NULL; start = start->next) {
        printf("[%s]->", start->string);
    }
    printf("FINISHED\n");
}

void insert_last(list_node *head, char *code) {

    if(head == NULL) return;

    /* creating a node with the given code */
    list_node *new_node = (list_node *)malloc(sizeof(list_node));
    if(new_node == NULL) {
        printf("Error:Cannot allocate memory\n");
        return;
    }
    new_node->next = NULL;
    strncpy(new_node->string, code, strlen(code)+1);

    if(!head->next) {
        head->next = new_node;
    }
    else {
        list_node *curr_node = head;
        while(curr_node->next) {
            curr_node = curr_node->next;
        }
        curr_node->next = new_node;
    }
}

void insert_first(list_node *head, char *code) {

    if(head == NULL) return;

    /* creating a node with the given code */
    list_node *new_node = (list_node *)malloc(sizeof(list_node));
    if(new_node == NULL) {
        printf("Error:Cannot allocate memory\n");
        return;
    }
    new_node->next = NULL;
    strncpy(new_node->string, code, strlen(code)+1);

    if(!head->next) {
        head->next = new_node;
    }
    else {
        new_node->next = head->next;
        head->next = new_node;
    }
}

void free_list(list_node *head) {

    if(head == NULL) {
        printf("List is already empty\n");
        return;
    }
    list_node *tmp_node = head;
    while (tmp_node->next != NULL) {
        list_node *to_delete = tmp_node->next;
        tmp_node->next = tmp_node->next->next;
        free(to_delete);
    }
    free(tmp_node);
}
