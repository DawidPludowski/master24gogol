#include<R.h>
#include<Rinternals.h>
#include<stdio.h>

static SEXP rep_times(SEXP x, const int times) {
    size_t len = XLENGTH(x);
    size_t outlen = len * times;

    SEXP y = Rf_allocVector(REALSXP, outlen);
    PROTECT(y);

    double* yp = REAL(y);
    double* xp = REAL(x);

    for (int i = 0; i < times; i++) {
        for (int j = 0; j < len; j++) {
            yp[i*len + j] = xp[j];
        }
    }

    UNPROTECT(1);
    return y;
}

static SEXP rep_lengthout(SEXP x, const int lengthout) {
    size_t len = XLENGTH(x);

    SEXP y = Rf_allocVector(REALSXP, lengthout);
    PROTECT(y);

    int cnt = 0;

    double* yp = REAL(y);
    double* xp = REAL(x);

    do {
        for (int i = 0; i < len; i++) {
            yp[cnt] = xp[i];
            cnt++;
            if (cnt == lengthout) break;
        }
    } while (cnt != lengthout);

    UNPROTECT(1);
    return y;
}

SEXP rep(SEXP x, SEXP times, SEXP lengthout) {

    if (!Rf_isReal(x)) {
        Rf_error("x needs to be of real type");
    }

    // if (!Rf_isInteger(times) || XLENGTH(times) != 1) {
    //     Rf_error("times needs to be of int type");
    // }

    // if (!Rf_isInteger(lengthout) || XLENGTH(lengthout) != 1) {
    //     Rf_error("length.out needs to be of int type");
    // }

    SEXP out;
    if (INTEGER(times)[0] != NA_INTEGER) {
        int times_int = INTEGER(times)[0];
        out = rep_times(x, times_int);
        return out;
    } else if (INTEGER(lengthout)[0] != NA_INTEGER) {
        int lengthout_int = INTEGER(lengthout)[0];
        return rep_lengthout(x, lengthout_int);
        return out;
    } else {
        Rf_error("Both times and length.out are bad defined");
    }

}