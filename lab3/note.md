# Lecture Notes

beofre the task:

* seq(),
* rep(),
* a*b of different lens,
* propag NA val, etc

stable:

```{sh}
forall a <= b, x[i[a]] == x[i[b]] => i[a] <= i[b]
```

in-place => O(1) (some ppl consider also O(logn))

to implement (assuming sorted) -> on test on Novemeber/December:

* binsearch
* unique (appending to the array)
* duplicated (flagging)
* empirical cumulative distribution
* mode
* merge/match (SQL join) for int-based indicies
* group by sum/mean/count etc

to check:

* check index.ismonotonic.increasing -- it is not used
* polaris, dplyr, data.table source code

```{c}
#<stdlib.h>
void qsort(void *x, size_t n, size_t s /* size of elements */, int (*cmp)(const void *a, const void *b))
\\ ((*a) <= (*b)>) -> 1, 0 otherwise

int x[10];
int ge(const void *a, const void *b) {int aa = *((int*)a); int bb = *((int*)b); return aa >= bb ? 1 : 0;} \\ maybe (int)
qsort(x, 10, sizeof(int), ge);
\\ now x is sorted
```
