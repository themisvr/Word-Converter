#ifndef LIST_H
#define LIST_H

typedef struct list_node {
    char string[20];
    struct list_node *next;
} list_node;

list_node *Create();
void insert_last(list_node *, char *);
void insert_first(list_node *, char *);
void print_list(list_node *);
void free_list(list_node *);

#endif //LIST_H
