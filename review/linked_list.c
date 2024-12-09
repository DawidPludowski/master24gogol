#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct _list_node
{
    struct _list_node* next;
    int data;
} list_node;

void push(list_node** n, int data) 
{
    list_node* new = malloc(sizeof(list_node));
    new->data = data;
    new->next = *n;
    *n = new;
}

int pop(list_node** n) // pn is more approciate
    {
        // assert((void*)**n != NULL); // #include<asset.h>
        int data = (*n)->data;
        list_node* old = *n;
        *n = (*n)->next; // (8)->data === (*(*n)).data
        free(old);
        return data;
    }

void main() {

    list_node* head = NULL;

    push(&head, 7);

    push(&(head->next), 8); // but it makes sense only when one el exists?

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);

    while (head != NULL) {
        int data = pop(&head);
        printf("%d\n", data);
    }


}