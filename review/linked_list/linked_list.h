#ifndef LINKED_LIST_H
    #define LINKED_LIST_H
    typedef struct Node {
        void* val;
        struct Node* next;
    } Node;

    typedef struct LinkedList{
        Node* head;
    } LinkedList;

    LinkedList* ll_create();
    int ll_insert_front(LinkedList* list, void* val);
    int ll_insert_int(LinkedList* list, int val);
    int ll_insert_back(LinkedList* list, void* val);
    int ll_remove_nth(LinkedList* list, int n);
    void ll_free_list(LinkedList* list);
    void ll_print_list(LinkedList* list, void (*print_func)(void*));

#endif  