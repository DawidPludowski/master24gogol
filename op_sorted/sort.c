#include<R.h>
#include<Rinternals.h>

double* insert_sort(double* xp, int len) {

    double min_val;
    int min_idx;
    double temp_val;

    for (size_t i = 0; i < len; i++) {
        min_val = xp[i];
        min_idx = i;
        for (size_t j = i + 1; j < len; j++) {
            if (xp[j] < min_val) {
                min_val = xp[j];
                min_idx = j;
            }
        }
        temp_val = xp[i];
        xp[i] = xp[min_idx];
        xp[min_idx] = temp_val;
    }


    return xp;

}

SEXP sortc(SEXP arr) {

    if (XLENGTH(arr) < 1) {
        Rf_error("Vector cannot be empty");
    } else if (!Rf_isReal(arr)) {
        Rf_error("Vector must be of type real");
    }

    SEXP x;
    size_t len = XLENGTH(arr);
    x = Rf_allocVector(REALSXP, len);

    PROTECT(x);

    double* xp = REAL(x);
    double* arrp = REAL(arr);

    for (size_t i = 0; i < len; i++) {
        xp[i] = arrp[i];
    }

    insert_sort(xp, len);
    UNPROTECT(1);
    return x;

}
