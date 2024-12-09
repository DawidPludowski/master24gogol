#include <stdlib.h>

int _insert_idx(double* x, int l, int r, double el) {

    int mid = (l + r) / 2;

    if (el == x[r]) {
        return r;
    }

    while (l != r) {
        if (x[mid] == el) {
            break;
        } else if (el < x[mid]) {
            r = mid;
        } else {
            l = mid;
        }
    }

    int stable_idx = mid;

    while (x[stable_idx] == x[stable_idx + 1]) {
        stable_idx++;
    }
    stable_idx++;

    return stable_idx;

}

void insertionsort_binsearch(double* x, size_t n) {

    int insert_idx;
    int l, r, mid;
    double temp_val;

    for (int i = 1; i < n; i++) {
        l = 0;
        r = i;

        insert_idx = _insert_idx(x, l, r, x[i]);
        temp_val = x[i];

        for (int j = i; j >= insert_idx; i--) {
            x[j] = x[j-1];
        }

        x[insert_idx] = temp_val;
    }

}

static void _merge_list(double* x, size_t l1, size_t r1, size_t l2, size_t r2) {
    int lc = l1;
    int rc = l2;

    int out_size = (r1 - l1) + (r2 - l2);

    double* out = malloc(sizeof(double)*out_size);

    int c = 0;

    while (lc < r1 || rc < r2) {
        
        if (lc == r1) {
            out[c] = x[rc];
            rc++;         
        } else if (rc == r2) {
            out[c] = x[lc];
            lc++;            
        } else if (x[lc] < x[rc]) {
            out[c] = x[lc];
            lc++;
        } else {
            out[c] = x[rc];
            rc++;
        }
    }

    for (int i = 0; i < (r1 - l1); i++) {
        x[l1 + i] = out[i];
    }
    for (int i = 0; i < (r2 - l2); i++) {
        x[l2 + i] = out[(r1 - l1) + i];
    }
}

static void _mergesort(double*x, size_t l, size_t r) {
    if (r - l <= 1) return;

    int mid = (r + l) / 2;

    _mergesort(x, l, mid);
    _mergesort(x, mid, r);

    _merge_list(x, l, mid, mid, r);
}

void mergesort(double* x, size_t n) {
    _mergesort(x, 0, n);
}

static int _pivotsort(double* x, size_t l, size_t r) {

    size_t pivot = (l + r) / 2;
    size_t swap_cnt = 0;
    size_t idx = l;

    double temp;

    while (idx != pivot) {
        if (x[idx] > x[pivot]) {
            temp = x[idx];
            x[idx] = x[pivot - 1];
            x[pivot - 1] = x[pivot];
            x[pivot] = temp;
            pivot--;
            swap_cnt++;
        }
        idx++;
    }

    idx = pivot + swap_cnt;
    while (idx != r) {
        if (x[idx] < x[pivot]) {
            temp = x[idx];
            x[idx] = x[pivot + 1];
            x[pivot + 1] = x[pivot];
            x[pivot] = temp;
            pivot++;
        }
        idx++;
    }

    return pivot;

}

static void _quicksort(double* x, size_t l, size_t r) {
    int pivot_idx = _pivotsort(x, l, r);

    if (r - l > 2) {
        _quicksort(x, l, pivot_idx);
        _quicksort(x, pivot_idx + 1, r);
    }
}


void quicksort(double* x, size_t n) {
    _quicksort(x, 0, n);
}

static int* quantitysort(int* x, size_t n, int max_val) {
    int* out = malloc(sizeof(int)*max_val);

    for (int i = 0; i < max_val; i++) {
        out[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        out[x[i]] += 1;
    }

    return out;
}

int* argsort_quantitysort(int* x, size_t n, int max_val) {

    int* sort_table = quantitysort(x, n, max_val);
    int* out = malloc(sizeof(int)*n);
    int* count_table = malloc(sizeof(int)*max_val);

    for (int i = 0; i < max_val; i++) {
        count_table = 0;
    }

    int val;
    int idx;

    for (int i = 0; i < n; i++) {
        idx = 0;
        val = x[i]; 
        for (int j = 0; j < x[i]; j++) {
            idx += sort_table[j];
        }
        idx += count_table[x[i]];
        out[i] = idx;
        count_table[x[i]]++;
    }

    return out;

}

static void _argsort_merge_list(double* x, size_t l, size_t mid, size_t r, int* out, int* helptable) {
    int lc = l;
    int rc = mid;

    int c = 0;

    while (lc < mid || rc < r) {
        
        if (lc == mid) {
            helptable[c] = out[rc];
            rc++;         
        } else if (rc == r) {
            helptable[c] = out[lc];
            lc++;            
        } else if (x[out[lc]] < x[out[rc]]) {
            helptable[c] = out[lc];
            lc++;
        } else {
            helptable[c] = out[rc];
            rc++;
        }
    }

    for (int i = l; i < r; i++) {
        out[i] = helptable[i];
    }
}

static void _argsort_mergesort(double* x, size_t l, size_t r, int* out, int* helptable) {
    if (r - l <= 1) return;

    int mid = (r + l) / 2;

    _argsort_mergesort(x, l, mid, out, helptable);
    _argsort_mergesort(x, mid, r, out, helptable);

    _argsort_merge_list(x, l, mid, r, out, helptable);
}

int* argsort_mergesort(double* x, size_t n, int* out) {
    int* helptable = malloc(sizeof(int)*n);
    _argsort_mergesort(x, 0, n, out, helptable);
}

// int* argsort_countsort(int* x, sizE_t n) {

// }

void heapify(double* x, int root, size_t n) {
    int idx = root;
    int l, r;
    double temp;

    while (idx < n) {
        l = idx * 2 + 1;
        r = idx * 2 + 2;
        if (x[idx] > x[l] && x[idx] > x[r]) return;
        else if (x[l] > x[r]) {
            temp = x[idx];
            x[idx] = x[l];
            x[l] = temp;
            idx = idx * 2 + 1;
        } else {
            temp = x[idx];
            x[idx] = x[r];
            x[r] = temp;
            idx = idx * 2 + 2;            
        }
    }
}

void build_heap(double* x, size_t n) {
    for (int i = n / 2; i >= 0; i--) {
        heapify(x, i, n);
    }
}

void heapsort(double* x, size_t n) {
    build_heap(x, n);
    
    double temp;
    for (int i = 0; i < n; i++) {
        temp = x[0];
        x[0] = x[n-i];
        x[n-i];
        heapify(x, 0, n-i);
    }
}