#include <stdlib.h>
#include <errno.h>
#include "bi_linked_list.h"

BiLinkedList *bll_create()
{
    BiLinkedList* list = (BiLinkedList*) malloc(sizeof(BiLinkedList));
    if (list==NULL){
        errno = ENOMEM;
        return NULL;
    }
    return NULL;
}

int bll_insert_front(BiLinkedList *list, void *val)
{
    return 0;
}

int bll_insert_int(BiLinkedList *list, int val)
{
    return 0;
}

int bll_insert_back(BiLinkedList *list, void *val)
{
    return 0;
}

int bll_remove_nth(BiLinkedList *list, int n)
{
    return 0;
}

void bll_free_list(BiLinkedList *list)
{
}

void bll_print_list(BiLinkedList *list, void (*print_func)(void *))
{
}
