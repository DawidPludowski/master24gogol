# Sorting

Quicksort, but with less recursion:

```{c}
while (b - a > 1) {

    c = partition(x, a, b);
    if (c - a < b - (c + 1)) {
        quicksort(x, a, c);
        a = c + 1;
    } else {
        quicksort(x, c+1, b);
        b = c
    }
}
```

To recap:

* heapsort (for e.g., Kruscal algorithm) - available in `numpy`
* quantity sort (?)
    1. simply count elements in separate array
    2. and then write them to a new arr
    3. no comparison so nice and fast
* how to make `argsort` from quantity sort (stable)?
    1. may be on the test (lol probably not)
    2. I guess make table for quantity sort and then make permutation in the second iteraiton
* radix sort
    1. based on bits
    2. get first bit, move 0 to left, 1 to right
    3. recursive with the splits and the bits
    4. depth depends on the size of the ints (so probably 32) so it's like constsnt in some way
    5. `O(b*n)`, `b` - bits, `n` - arr size
* this will be partially covered on the course site so worth checking

## Arrays

* addresses in C are virtual (like, it's obvious lol)
* memory is made from pages (~40kB) - smallest portion of data for CPU
* memory management unit (MMU) (translation ,,, buffer) TLB
* virtual addresses do not affect perofrmance
* swapping good etc etc
* `mmap` - taskes file from disk and map to virtual address space (probably as fast as swapping)
* `maloc` is implemented based on `mmap`

## Arrays different length

If we cannot tell what is the deisired length:

* first check, then init
* init as many as might be required
* fill it
* copy it to the final-length array

Or growable arrays:

* like in Python with `.append()`

```{c}
k = 1024
double x = malloc(k * sizeof(double))

while ...
    if (i < k)
        x[i++]
    else
        k = k * 2 /* or sth different, depends */
        x = realloc(k * sizeof(double))
        x[i++]
```

sometimes cheap (if free slots exists), sometimes whole new array need to be reinit (long)
