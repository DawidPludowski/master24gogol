# Notes

## sparse vectors

* v - value vector, l - location in vector vector
* $x_{l_{i}} = v_i$, $i\in[l]$, 0 otherwise
* hashtables
    1. h[i] = v if found, 0 otherwise
* to implement
    1. sum of el in sparse vector (easy for sparse, hard for hastables)
    2. x[i] from sparse vector (h[i] in hastable O(1), or iterate for l vector (should be sorted) O(n) if not sorted)
    3. slice x[i:j] (hard for hastable)
    4. s\*x (scalar\*vector)
    5. x^Ty
    6. given x convert to sparse representations

## Sparse matrices

* A in R(n x m)
* as in scipy.sparse
* Matrix package in R
* DOK dictionary of keys
    1. h[(i, j)] = A[ij] if exists, 0 otherwise
    2. LIL list of lists (lists of sparse lists)
    3. COO coordinate/IJV list (like sparse lists but for I, J, V) A[I[i], J[j]], can be sorted leksykalnie
    4. CSR - compressed sparse row format
        * data (length s)
        * indexes (length s)
        * index pointer (indptr) (length n+1)
        In the i-th row A[i, indexes[indptr[i]:indptr[i+1]]] = data[indexes[indptr[i]:indptr[i+1]]]. Fast row slicing  (slow column slicing)
        * to implement A[i,:], A[:,j], A[i:j,:], A[:,i:j], sA, AB, A^ (basically for all of these structures)

## Clustering algorithms

$X = {x_1,...,x_n}$

$x_i \in R^d$

$\|x_i - x_j\|_2$

$\sqrt{\sum^d_l (x_{il} - x_{jl})^2}$

k-fixed, k>=2 - number of clusters

find k-partition of X $P={C_1, ..., C_k}$

label vectors (c_1,...,c_n) # each obs has value of its set idx.

### WCSS (within-cluster sum of squares)

$min_{c_1, ..., c_k} \frac 1n \sum^k_i \frac{1}{|c_i} \sum_{X, X' in C_i} \| X - X' \|^2$

$min_{c_1, ..., c_k} \frac 1n sum^n_i \frac{1}{|C_{ci}|} \sum_{x_j \in C_i} \| x_i - x_j \|^2$

This is NP-hard problem!!!


