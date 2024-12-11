#include <stdlib.h>

typedef struct _sv {
    int* loc;
    double* val;
    int n;
} SV;

typedef struct _oh {
    int* loc;
    int* is_used;
    int* was_used;
    double* val;
    int n;
    int size;
} OH;

int max(int a, int b) {return a > b ? a : b;}

OH* get_oh(int n, int size) {
    OH* oh = malloc(sizeof(OH));
    oh->n = n;
    oh->size = size;
    oh->loc = malloc(sizeof(int)*n);
    oh->is_used = malloc(sizeof(int)*n);
    oh->was_used = malloc(sizeof(int)*n);
    oh->val = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++) {
        oh->is_used[i] = 0;
        oh->was_used[i] = 0;
    }
    return oh;
}

int hash(int loc, int m) {return (loc * loc) % m;}

int search_loc(OH* oh, int idx) {
    int hidx = hash(idx, oh->n);
    int sp = hidx;
    do {
        if (!oh->was_used[hidx]) return -1;
        else if (!oh->loc[hidx] == idx) return hidx;
        hidx = (hidx + 1) % oh->n;
    } while (hidx != sp);
    return -1;
}

void insert_val(OH* oh, int idx, double val) {
    int hidx = hash(idx, oh->n);
    int sp = hidx;
    while (hidx != sp) {
        if (!oh->is_used[hidx] || oh->loc[hidx] == idx) {
            oh->val[hidx] = val;
            oh->loc[hidx] = idx;
            oh->is_used[hidx] = 1;
            oh->was_used[hidx] = 1;
        }
        hidx = (hidx + 1) % oh->n;
    }
}

void add_val(OH* oh, int idx, double val) {
    int hidx = hash(idx, oh->n);
    int sp = hidx;
    while (hidx != sp) {
        if (!oh->is_used[hidx] || oh->loc[hidx] == idx) {
            oh->val[hidx] += val;
            oh->loc[hidx] = idx;
            oh->is_used[hidx] = 1;
            oh->was_used[hidx] = 1;
        }
        hidx = (hidx + 1) % oh->n;
    }  
}

void delete_idx(OH* oh, int idx) {
    int hidx = search_loc(oh, idx);
    if (hidx < 0) return;
    oh->is_used[hidx] = 0;
}

OH* add_oh(OH* oh1, OH* oh2) {
    int size = max(oh1->size, oh1->size);
    int n = oh1->n + oh2->n;

    OH* out = get_oh(n, size);
    for (int i = 0; i < oh1->n; i++) {
        add_val(out, oh1->loc[i], oh1->val[i]);
    }
    for (int i = 0; i < oh2->n; i++) {
        add_val(out, oh2->loc[i], oh2->val[i]);
    }
    return out;
}