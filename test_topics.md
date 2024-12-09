# Test

* algorithms on sorted arrays
    * binsearch
    * unique (appending to the array)
    * duplicated (flagging)
    * empirical cumulative distribution
    * mode
    * merge/match (SQL join) for int-based indicies
    * group by sum/mean/count etc
* sorting algorithms with weird modifications / hybrid forms
    * insertion sort (e.g., binsearch used in insertion)
    * merge sort
    * quick sort
    * heapsort
    * stable argsort that uses quantity sort
    * mergesort that returns argsort
* counting sort return argsort
* Circural buffer
* Linked list and other directed root trees
* trees (only part of algorithms, not full)
    * left-right rotate in AVL trees
    * red-black trees (XD)
    * B-trees
    * basically rotations, not the whole algorithms
* graphs
    * DFS (depth-first search)/BFS (breadth-first search) (listing all vertices connected to the given index)
* hash tables
* skills to implement whatever is in the code below

```{c}
typedef struct _list_node
{
    struct _list_node* next;
    int data;
}

list_node* head = NULL;

void push(list_node** n, int data) 
{
    list_node* new = malloc(sizeof(list_node));
    new->data = data;
    new->next = *n;
    *n = new;
}

push(&head, 7);

push(&(head->next), 8); // but it makes sense only when one el exists?
```

```{c}
int pop(list_node** n) // pn is more approciate
{
    assert(**n != NULL); // #include<asset.h>
    int data = (*n)->data;
    list_node* old = *n;
    *n = (*n)->next; // (8)->data === (*(*n)).data
    free(old);
    return data;
}
```