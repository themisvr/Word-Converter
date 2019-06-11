#ifndef WORD_CONVERTER_H
#define WORD_CONVERTER_H

#include "priority_queue.h"

list_node *optimized_converter(char *, char *);
char **read_dictionary(size_t, size_t);
int str_compare(const void *, const void *);
list_node *Similar(char *, char **);
uint32_t steps_number(list_node *);
uint32_t heuristic(char *, char *);
int checked(list_node *, char *);


#endif //WORD_CONVERTER_H
