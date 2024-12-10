#include "linked_list.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>


LinkedList* ll_create(){
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    if (list == NULL){
        errno = ENOMEM;
        return NULL;
    }
    list->head = NULL;
    return list;
};

int ll_insert_front(LinkedList* list, void* val){
    if (list == NULL){
        errno = EINVAL;
        return -1;
    }
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL){
        errno = ENOMEM;
        return -1;
    }
    node->val = val;
    node->next = list->head;
    list->head = node;
    return 0;
};

int ll_insert_back(LinkedList* list, void* val){
    if (list == NULL){
        errno = EINVAL;
        return -1;
    }
    Node* head = list->head;

    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL){
        errno = ENOMEM;
        return -1;
    }

    node->val = val;
    node->next = NULL;

    if (head == NULL){
        list->head = node;
        return 0;
    }

    while (head->next != NULL)
        head = head->next;


    head->next = node;
    return 0;
};

int ll_remove_nth(LinkedList* list, int n){
    if (list == NULL || list->head == NULL){
        errno = EINVAL;
        return -1;
    }

    Node* head = list->head;
    size_t size = 1;
    while (head->next != NULL){
        head = head->next;
        size++;
    }

    if (n > size || n < 1){
        errno = EINVAL;
        return -1;
    }

    head = list->head;
    if (head->next == NULL && n == 1){
        free(list->head);
        list->head = NULL;
        return 0;
    }

    for (size_t i=0;i<size-n-1;i++){
        head = head->next;
    }
    head->next = head->next->next;
    return 0;
};

void ll_free_list(LinkedList* list){
    Node* current = list->head;
    Node* next;
    while (current != NULL){
        next = current->next;
        free(current->val);
        free(current);
        current = next;
    }
    free(list);
};

void ll_print_list(LinkedList* list, void (*print_func)(void*)){
    Node* current = list->head;
    while(current != NULL){
        print_func(current->val);
        current = current->next;
    }
    printf("\n");
};

int ll_insert_int(LinkedList* list, int val){
    void* val_ptr = malloc(sizeof(int));
    *((int*)val_ptr) = val;
    return ll_insert_front(list, val_ptr);
};


void print_int(void* val){
    printf("%d ", *(int*)val);
}

int main(void){
    LinkedList* ll = ll_create();
    if (ll_insert_int(ll, 1) != 0)
        goto error;
    if (ll_insert_int(ll, 2) != 0)
        goto error;
    if (ll_insert_int(ll, 3) != 0)
        goto error;
    ll_print_list(ll, print_int);
    
    if (ll_remove_nth(ll, 1) != 0)
        goto error;
    ll_print_list(ll, print_int);
    
    if (ll_remove_nth(ll, 1) != 0)
        goto error;
    ll_print_list(ll, print_int);
    
    if (ll_remove_nth(ll, 1) != 0)
        goto error;
    ll_print_list(ll, print_int);
    
    ll_free_list(ll);
    return 0;
    error:
        perror("delete_to_empty");
        return -1;
}