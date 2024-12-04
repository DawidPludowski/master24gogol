# Lecture 7 (I guess)

## Arrays of arrays

* used in bucket sort (literally counting sort with perserving order etc)

## Graphs

* G = (V, E)
* V = {0, ..., n-1}
* E \subset V^2
* adjency lists (array with, let's say linked list this adjenct vertices), a[i] <- neighbours of i
  1. in this case, can be directed!
  2. **on the test** -> DFS (depth-first search)/BFS (breadth-first search) (listing all vertices connected to the given index)

## Hash tables

k should be bigger than n, n/k < 66.67%

On the test (11 chapter in the funny book)

x_1, ..., x_{n-1} \in X

h: X -> {0,...,k-1} <- ideally, bijection; in practise, some comflicts exists in most algorithms

### open addresses

if h(x_i) = h(x_j) = 3, we simply store them in the next bucket

[][][x_i][x_j][][][][]

place is occupied? Store in the next free slot

O(1) amortized access

### idk sth

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

maybe on the test (as everything dummy)

### Dense matrices

$A \in R^{n x m}$

$A_{i,j}$

R[0], ..., R[n-1] in R^m // rows (arrays of arrays), lack of locality, no one uses ...

C[0], ..., C[m-1] in R^n // (except data frames)

c-style arrays (row-major) -> flat array, x[i*m+j], used by numpy

fortran-style (column-major) // same as previous, x[i+j*n], used by R (numpy also can use it)

#### Example

A = [[1,2,3,4],
     [5,6,7,8]]

c-style = [1,2,3,4,5,6,7,8]

fortran-style = [1,5,2,6,3,7,4,8]

trailing dimension: with empty cells on trailing dimension

A = [[1,2,3,NULL],
     [5,6,7,NULL]]

good if total # of rows/cols is 2^k, or better, 8^k

### Non-contigous matrices

contigous matrices has stride/setpsize/increment of 1 (always) to get next element

why non-contigous? E.g., for operations like A[:,::2] that creates only a view, not a new object

Or better example: A[:,2]
