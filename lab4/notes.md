# Lecture notes

Today's algorithms:

* insertion sort
* merge sort
* quick sort
* heapsort
* ???

^ this (with hybrid forms) can be on the test!

Cormen - introduction to the algrithms 2, 6-9

## Algorithms

### Insertion sort

* locality ofreferen**ce - better CPU cache
* super fast for n < 20
* **to implement** - do binsearch for the insertion instead of linear search (test linear vs binsearch)
* **to implement** - find k smallest values in the array (additional array to insertsort) -> O(kn)

### Merge sort

* ! mergesort in np.argsort(kind='mergesort') is not a mergesort!!!!!
* append element from the first sequence first to remain stability
* **to implelent** in O(n) time of merge, O(n) memeory and stable
* pass additional array to mergesort to store ada in merge
* **to implement** mergesort without recursion
* **to implement** use temp arr and org arr as temp arr one after another (change ref by switching pointers
* can be parallized
* (a+b)/2 can produce overflow so a/2 + b/2 is better (not work for like most cases lol)

### timsort

* assumes data is presorted (approx)
* instead od 2,4,8,... to sort, check for the longest sorted subsequences
* building like trees of subsequences to be merged (not really equal depth for all leafs)
* `sort()` in python use powersort, np `uses.sort()` timesort (peeksort)

### Quicksort

* not stable
* O(n) memory; O(nlogn) (average), O(n^2) pesimistic time
* c = partition(x, a, b) -> x[a],...,x[c] <= x[c+1], ..., x[b]
