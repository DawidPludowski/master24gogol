#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>
#include <stdio.h>

static void insertsort(int arr[], int size) {

    double min;
    int min_idx;
    double temp;

    for (int i = 0; i < size; i++) {
        min = arr[i];
        min_idx = i;
        for (int j = i+1; j < size; j++) {
            if (arr[j] < min) {
                min = arr[j];
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

SEXP insertsort_wrapper(SEXP arr) {
    if (!Rf_isInteger(arr)) {
        Rf_error("Array needs to be of int type.");
    }

    int size = (int) XLENGTH(arr);
    int* c_arr = INTEGER(arr);

    insertsort(c_arr, size);  

    return R_NilValue;

}