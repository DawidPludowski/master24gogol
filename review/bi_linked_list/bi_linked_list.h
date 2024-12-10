#ifndef BI_LINKED_LIST_H
    #define BI_LINKED_LIST_H
    typedef struct Node {
        void* val;
        struct Node* next;
        struct Node* prev;
    } Node;

    typedef struct BiLinkedList{
        Node* head;
        Node* tail;
    } BiLinkedList;

    BiLinkedList* bll_create();
    int bll_insert_front(BiLinkedList* list, void* val);
    int bll_insert_int(BiLinkedList* list, int val);
    int bll_insert_back(BiLinkedList* list, void* val);
    int bll_remove_nth(BiLinkedList* list, int n);
    void bll_free_list(BiLinkedList* list);
    void bll_print_list(BiLinkedList* list, void (*print_func)(void*));

#endif  