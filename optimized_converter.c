#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "optimized_converter.h"


char alphabet[] = {  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
size_t words = 60076;
size_t letters = 20;

list_node *optimized_converter(char *starting_word, char *final_word) {

    if(strlen(starting_word) != strlen(final_word)) {
        fprintf(stderr,"Error: these words dont have the same length\n");
        exit(-1);
    }
    list_node *first_word = Create();
    assert(first_word != NULL);
    insert_first(first_word, starting_word);
    /* evaluation is actually the priority number of the conversion */
    uint32_t evaluation = steps_number(first_word) + heuristic(first_word->next->string, final_word);
    /* creating the first node of the priority queue with the list we just created and the priority steps_number */
    /* we just computed by the given algorithm */
    p_queue *priority_q = create_pqnode(first_word, evaluation);

    /* initialize the dictionary */
    char **words_array = read_dictionary(words, letters);

    int flag = 0;
    size_t loops_count = 0;
    list_node *checked_words = Create();
    if(checked_words == NULL) {
        exit(-1);
        fprintf(stderr, "Error occured\n");
    }
    while(strncmp(priority_q->list->next->string, final_word, strlen(final_word)+1) != 0) {
        p_queue *pq_temp = priority_q;
        /* take the first word of the queue and check all the words that are similar to this word */
        if(checked(checked_words, priority_q->list->next->string) == 0) {
            list_node *conversion = Similar(priority_q->list->next->string, words_array);
            /* take all possible lists that are going to be created for each word */
            list_node *head;
            list_node *lptr;
            for(lptr = conversion->next; lptr != NULL; lptr = lptr->next) {
                list_node *a_list = Create();
                /* copy the old list to the new one and add the new element */
                for(head = priority_q->list->next; head != NULL; head = head->next) {
                    insert_last(a_list, head->string);
                }
                /* insert first so when we take the first element we check, whether the word is what we searching for, or not */
                insert_first(a_list, lptr->string);
                evaluation = steps_number(a_list) + heuristic(a_list->next->string, final_word);
                push_pqnode(&priority_q, a_list, evaluation);
            }
            free_list(conversion);
        }
        /* mark the word as checked, no need to check it every single time it appears */
        insert_last(checked_words, priority_q->list->next->string);
        priority_q = pop_pqnode(priority_q);
        delete_pqnode(&priority_q, pq_temp);

        ++loops_count;
        if(!strncmp(priority_q->list->next->string, final_word, strlen(final_word)+1)) {
            flag = 1;
            break;
        }
    }

    for(size_t i = 0U; i < words; i++) {
        free(words_array[i]);
    }
    free(words_array);
    free_list(checked_words);

    if(flag == 1) {
        printf("Number of loops until we find the path: [%ld]\n", loops_count);
        /* copy the path to a new list */
        list_node *path = Create();
        list_node *traverse = NULL;
        for(traverse = priority_q->list->next; traverse != NULL; traverse = traverse->next) {
            /* reverse it again to take the right form of the path */
            insert_first(path, traverse->string);
        }
        free_pqueue(&priority_q);
        return path;
    }
    printf("Could not find a path for the given word!\n");
    return NULL;
}


uint32_t heuristic(char *word1, char *word2) {

    uint32_t diff_letters = 0;

    /* we check until we reach the end of the word1 */
    /* these two words have the same length so we dont need to check for both */
    for(size_t i = 0; i < strlen(word1); i++) {
        if(word1[i] != word2[i]) {
            diff_letters++;
        }
    }

    return diff_letters;
}


uint32_t steps_number(list_node *head) {

    assert(head != NULL);
    uint32_t steps = 0;
    /* NOTE::dont forget that the implementation for my list ADT has a dummy node */
    /* so we start from the head->next as the actuall node */
    list_node *temp = head->next;
    while(temp != NULL) {
        steps++;
        temp = temp->next;
    }

    return steps;
}

list_node *Similar(char *word, char **words_array) {


    /* sorting the array using the qsort function from the standart library */
    qsort(words_array, words, sizeof(char *), str_compare);

    /* create the list with the results */
    list_node *results = Create();
    if(!results) {
        fprintf(stderr, "Error occured\n");
        return NULL;
    }

    /* copy the word to a string */
    char *check_string = malloc(strlen(word)+1);

    for(size_t i = 0U; i < strlen(word); i++) {
        strncpy(check_string, word, strlen(word)+1);
        /* for each letter in the alphabet */
        for(size_t j = 0U; j < 26; j++) {
            /* change the letters one-by-one */
            check_string[i] = alphabet[j];
            /* binary search in the words_array to find the given string */
            char **key = (char **)bsearch(&check_string, words_array, words, sizeof(char *), str_compare);
            if(key != NULL) {
                if(strcmp(*key, word) != 0) {
                    /* if we find it, we put it in the list that we want to return */
                    insert_last(results, *key);
                }
            }
        }
    }
    free(check_string);

    return results;
}


char **read_dictionary(size_t words, size_t words_length) {

    /* open the given dictionary */
    FILE *fp;
    fp = fopen("words.txt", "r");
    if(!fp) {
        fprintf(stderr, "Error occured:File [words.txt] failed to open, the program will be terminated\n");
        exit(1);
    }
    /* there are #rows words inside the "words.txt" dictionary */
    char **words_array;
    words_array = (char **)calloc(words + 1, sizeof(char *));
    if(!words_array) {
        fprintf(stderr, "Error:Cannot allocate memory\n");
        exit(1);
    }
    /* for each word we allocate memory for the string itself */
    /* we put 15 characters each max + '\0'*/
    for(size_t i = 0U; i < words; i++) {
        words_array[i] = (char *)malloc( (words_length + 1) * sizeof(char));
        if(!words_array[i]) {
            fprintf(stderr, "Error:Cannot allocate memory\n");
            exit(1);
        }
    }
    /* a count for the words */
    int index = 0;
    /* for each word in the dictionary we put it in the array */
    while(fgets(words_array[index], words_length, fp) != NULL) {
        index++;
    }

    /* we removes the '\n' from the string */
    for(size_t i = 0U; i < words; i++) {
        words_array[i] = strtok(words_array[i], "\n");
    }

    fclose(fp);

    return words_array;
}


int checked(list_node *list, char *word) {

    if(list == NULL) {
        printf("Error:List is empty,no words to search\n");
        /* if error occures */
        return -1;
    }

    list_node *start;
    /* traverse the list till the end */
    for(start = list->next; start != NULL; start = start->next) {
        if(!strcmp(start->string, word)) {
            /* the word is found */
            return 1;
        }
    }
    return 0;
}


int str_compare(const void *string1, const void *string2) {

    return strcmp(*(char **)string1, *(char **)string2);
}
