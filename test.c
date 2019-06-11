#include <stdio.h>
#include <stdlib.h>
#include "optimized_converter.h"


int main(void) {


    printf("Converting [dog] to [cat]...\n");
    list_node *path = optimized_converter("dog", "cat");
    if(!path) exit(1);
    print_list(path);
    free_list(path);
    printf("Converting [cans] to [coin]...\n");
    path = optimized_converter("cans", "coin");
    if(!path) exit(1);
    print_list(path);
    free_list(path);
    printf("Converting [dart] to [dogs]...\n");
    path = optimized_converter("dart", "dogs");
    if(!path) exit(1);
    print_list(path);
    free_list(path);
    printf("Converting [cans] to [claw]...\n");
    path = optimized_converter("cans", "claw");
    if(!path) exit(1);
    print_list(path);
    free_list(path);
    printf("Converting [cans] to [able]...\n");
    path = optimized_converter("cans", "abel");
    if(!path) exit(1);
    print_list(path);
    free_list(path);
    printf("Converting [table] to [bread]...\n");
    path = optimized_converter("table", "bread");
    if(!path) exit(1);
    print_list(path);
    free_list(path);
    printf("Converting [table] to [acton]...\n");
    path = optimized_converter("table", "acton");
    if(!path) exit(1);
    print_list(path);
    free_list(path);

    return 0;
}
