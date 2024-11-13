#include<R.h>
#include<Rinternals.h>
#include<stdio.h>

#define SORTED 1
#define NOT_SORTED 0

int* insert_sort_idx(double* xp, int* yp, int len) {
    double min_val;
    int min_idx;
    int temp;

    for (int i = 0; i < len; i++){
        yp[i] = i;
    }

    for (size_t i = 0; i < len; i++) {
        min_val = xp[yp[i]];
        min_idx = i;
        for (size_t j = i + 1; j < len; j++) {
            if (xp[yp[j]] < min_val) {
                min_val = xp[yp[j]];
                min_idx = j;
            }
        }
        temp = yp[min_idx];
        yp[min_idx] = yp[i];
        yp[i] = temp;
    }


    return yp;
}

static int binsearch(double* arrp, double el, int len) {

    int lb = 0, rb = len - 1, mid_idx;

    while (lb != rb) {
        mid_idx = (rb + lb) / 2;
        if (arrp[mid_idx] == el) {
            return mid_idx;
        } else if (arrp[mid_idx] < el) {
            lb = mid_idx;
        } else {
            rb = mid_idx;
        }
    } 

    return -2;


}

static int binsearch_idx(double* arrp, double el, int len, int* sortidx) {

    int lb = 0, rb = len - 1, mid_idx;

    while (lb != rb) {
        mid_idx = (rb + lb) / 2;
        if (arrp[sortidx[mid_idx]] == el) {
            return sortidx[mid_idx];
        } else if (arrp[sortidx[mid_idx]] < el) {
            lb = mid_idx == lb ? mid_idx + 1 : mid_idx;
        } else {
            rb = mid_idx == rb ? mid_idx - 1: mid_idx;
        }
    } 

    return -2;


}

SEXP binsearchc(SEXP arr, SEXP el) {

    if (XLENGTH(arr) < 1) {
        Rf_error("Vector cannot be empty");
    } else if (!Rf_isReal(arr)) {
        Rf_error("Vector must be of type numeric");
    } else if (!Rf_isReal(el) || XLENGTH(el) != 1) {
        Rf_error("el can be only a scalar");
    }

    double* arrp = REAL(arr);
    int len = XLENGTH(arr);
    int sorted = 1;
    for (int i = 0; i < len - 1; i++) {
        if (arrp[i] > arrp[i+1]) {
            sorted = 0;
            break;
        }
    }

    double elreal = REAL(el)[0];
    int out;

    if (sorted == NOT_SORTED) {
        int sortidx[len];
        insert_sort_idx(arrp, sortidx, len);
        out = binsearch_idx(arrp, elreal, len, sortidx);
    } else {
        out = binsearch(arrp, elreal, len);
    }

    return Rf_ScalarInteger(out + 1);

}