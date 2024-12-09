#include <stdlib.h>

int count_groups(double* x, size_t n) {
    if (n == 0) {
        return 0;
    }
    int cnt = 1;
    double prev = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] != prev) {
            cnt++;
            prev = x[i];
        }
    }

    return cnt;
}

int binsearch(double* x, double el, size_t n) {
    int l = 0;
    int r = n-1;
    int mid = (r + l) / 2;

    if (x[l] == el) {
        return l;
    } else if (x[r] == el) {
        return r;
    }

    while (l != r) {
        if (x[mid] == el) {
            return mid;
        } else if (el < x[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return -1;
}

static void _unique(double* x, double* out, size_t n) {

    double prev = x[1];
    out[0] = prev;

    int cnt = 1;

    for (int i = 1; i < n; i++) {
        if (prev != x[i]) {
            cnt++;
            prev = x[i];
            out[cnt] = x[i];
        }
    }

}

double* unique(double* x, size_t n) {
    int n_groups = count_groups(x, n);
    if (n_groups == 0) {
        return NULL;
    }

    double* out = malloc(sizeof(double) * n_groups);

    _unique(x, out, n);

    return out;
}

int duplicated(double* x, size_t n) {

    if (n <= 1) {
        return 0;
    }

    int prev = x[0];

    for (int i = 1; i < n; i++) {
        if (prev == x[i]) {
            return 1;
        } else {
            prev = x[i];
        }
    }

    return 0;

}

double ecd(double* x, double el, size_t n) {
    if (el < x[0]) {
        return 0.0;
    }

    for (int i = 0; i < n; i++) {
        if (el > x[i]) {
            return (double) i / (double) n;
        }
    }

    return 1.0;
}

static void _join(int* idx, int* ref_idx, double* vals, double* out, size_t n, size_t m) {

    int prev = 0;
    int is_found;
    for (int i = 0; i < n; i++) {
        is_found = 0;
        for (int j = prev; j < m; j++) {
            if (ref_idx[j] == idx[i]) {
                prev = j;
                out[i] = vals[j];
                is_found = 1;
                break;
            }
        }
        if (!is_found) {
            out[i] = -1;
        }
    }

}

double* join(int* idx, int* ref_idx, double* vals, size_t n, size_t m) {

    double* out = malloc(sizeof(double) * n);
    _join(idx, ref_idx, vals, out, n, m);

    return out;
}

static void _groupby_sum(double* x, double* groups, size_t n, double* out) {

    int prev_group = groups[0];
    int cnt = 0;

    out[0] = x[0];
    for (int i = 1; i < n; i++) {
        if (prev_group != groups[i]) {
            prev_group = groups[i];
            cnt++;
        }
        out[cnt] += x[i];
    }

}

double* groupby_sum(double* x, double* groups, size_t n) {

    int n_groups = count_groups(groups, n);
    double* out = malloc(sizeof(double) * n_groups);

    for (int i = 0; i < n_groups; i++) {
        out[i] = 0;
    }
    
    _groupby_sum(x, groups, n, out);
    return out;
}