# Notes

## Circural buffer

FIFO

* store index of start/end of the actual data in a simple array
* may be on the test

## Array of arrays

* `double** x;` - pointer to the pointer
* arrays may vary in size (additional table with sizes is required)

This is not optimal (but used for dataframes - data_frame from R: `x` - list, `x[i]` - atomic vector, `i` - column index). B-trees are implemented like that. Subarrays can be strucs with meta-info:

```{c}
x = malloc(sizeof(double*)*n);
//for i ...
x[i] = malloc(sizeof(double)*d);

x[i][j] == (x[i])[j]
```

Long vector with pointers to split points is used in real life.

Homework:

* `n x m` size arrays
* get first 5 rows (x[:5])
* get rows with positive value on the 1 col x[x[1] > 0,]
* get rows with positive value on the 1 col except 1 col x[x[1] > 0, -1]

## Linked list and other directed root trees

```{c}
typedef struct _list_node 
{
   struct _list_node* next;
   ab data; 
} list_node;

list_node* head = NULL;
head = malloc(sizeof(list_node));

head->data = 1;
head->next = ...;

list_node* ne = malloc(sizeof(list_node));

ne->data = 0;
ne->next = head;

head = ne;

// remove first element
head = head->next; // but this is a memory LEAK

// correct way
list_node* oe -= head;
head = head->next;
free(oe);
```

* we lost caching (lack of locality)
* unlimited space
* costly access to the middle
* additional memory for addresses

Augumenttions:

* storing whole pages in a node (locality)
* add/pop from the end (reference to the end)
    1. here, list should be bidirectional to efficient pop back

Can be on the test (lol)

### Rooted trees

* decision trees (not really on the test)

On the test (maybe):

* left-right rotate in AVL trees
* red-black trees (XD)
* B-trees
* basically rotations, not the whole algorithms

```{c}
typedef struct _bintree_node
{
    struct _bintree_node* left;
    struct _bintree_node* right;
    union {
        struct {
            int which_var;
            double c;
        }, // anon strucs
        struct {
            int num0;
            int num1;
        } // some final values
    }
}
```

## Hash tables

## Sparse vectors

## Matrices

## Sparse matrices

## Ideas

* mergesort that returns argsort
* counting sort return argsort

on the test (to implement), no R/Py API:

```{c}
int sort(int* x, size_t n) {}
```

## In the future

* disjoint set  (sth)
* clustering methods
* minimum spanning trees
* nearest neighbour search (with fast implementation)
