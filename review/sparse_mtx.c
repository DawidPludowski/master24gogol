#include <stdio.h>
#include <stdlib.h>

typedef struct _csr {
    double* data;
    int* idx;
    int* pointr;
    int s;
    int n;
} CSR;

typedef struct _mtx {
    double* data;
    int n;
    int m;
} MTX;

CSR* get_csr(int s, int n) {
    CSR* csr = malloc(sizeof(CSR));
    csr->data = malloc(sizeof(double)*s);
    csr->idx = malloc(sizeof(int)*s);
    csr->pointr = malloc(sizeof(int) * (n+1));
    csr->n = n;
    csr->s = s;
}

MTX* get_mtx(double* data, int n, int m) {
    MTX* mtx = malloc(sizeof(MTX));
    mtx->data = data;
    mtx->n = n;
    mtx->m = m;
    return mtx;
}

void print_csr(CSR* csr) {
    printf("\ndata: ");
    for (int i = 0; i < csr->s; i++) printf("%d, ", (int) csr->data[i]);
    printf("\nidx: ");
    for (int i = 0; i < csr->s; i++) printf("%d, ", (int) csr->idx[i]);
    printf("\npointr: ");
    for (int i = 0; i < (csr->n+1); i++) printf("%d, ", (int) csr->pointr[i]);
    printf("\n");
}

void print_mtx(MTX* mtx) {
    for (int i = 0; i < mtx->n * mtx->m; i++) {
        if (i % mtx->m == 0) printf("\n");
        printf("%d, ", (int)mtx->data[i]);
    }
    printf("\n");
}

CSR* mtx2csr(MTX* mtx) {
    int nonzero_cnt = 0;
    for (int i = 0; i < mtx->n * mtx->m; i++) {
        if (mtx->data[i] != 0) nonzero_cnt++;
    }

    CSR* csr = get_csr(nonzero_cnt, mtx->n);

    int pointr_cnt = 0;
    int data_cnt;

    for (int i = 0; i < mtx->n * mtx->m; i++) {
        if (i % mtx->m == 0) {
            csr->pointr[pointr_cnt] = data_cnt;
            pointr_cnt++;
        } if (mtx->data[i] != 0) {
            csr->data[data_cnt] = mtx->data[i];
            csr->idx[data_cnt] = i % mtx->m;
            data_cnt++;
        }
    }

    csr->pointr[mtx->n] = nonzero_cnt;

    return csr;
}

void main() {
    int n = 4;
    int m = 4;
    double* data = malloc(sizeof(double)*n*m);
    for (int i = 0; i < n*m; i++) data[i] = i % 2 == 0 ? i : 0;

    MTX* mtx = get_mtx(data, n, m);
    print_mtx(mtx);

    CSR* csr = mtx2csr(mtx);
    print_csr(csr);
}