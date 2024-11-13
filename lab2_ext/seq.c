#include<R.h>
#include<Rinternals.h>
#include<stdio.h>

SEXP seq_by(const int from, const int to, const double by) {
    size_t len = (size_t) ((double) to - (double) from) / by;

    SEXP y = Rf_allocVector(REALSXP, len);
    PROTECT(y);

    double* yp = REAL(y);

    double cumsum = 0;

    for (int i = 0; i < len; i++) {
        yp[i] = from + cumsum + by;
        cumsum += by;
    }

    UNPROTECT(1);
    return y;
}

SEXP seq_lengthout(const int from, const int to, const int lengthout) {
    double by = ((double) to - (double) from) / (double) lengthout;

    SEXP y = Rf_allocVector(REALSXP, lengthout);
    PROTECT(y);

    double* yp = REAL(y);

    double cumsum = 0;

    for (int i = 0; i < lengthout; i++) {
        yp[i] = from + cumsum + by;
        cumsum += by;
    }

    UNPROTECT(1);
    return y;
}

SEXP seq(SEXP from, SEXP to, SEXP by, SEXP lengthout) {

    if (!Rf_isInteger(from) || XLENGTH(from) != 1) {
        Rf_error("from is bad defined");
    }
    if (!Rf_isInteger(to) || XLENGTH(to) != 1) {
        Rf_error("to is bad defined");
    }
    if (!Rf_isReal(by) || XLENGTH(by) != 1) {
        Rf_error("by is bad defined");
    }
    if (!Rf_isInteger(lengthout) || XLENGTH(lengthout) != 1) {
        Rf_error("length.out is bad defined");
    }

    int from_int = INTEGER(from)[0];
    int to_int = INTEGER(to)[0];
    double by_double = REAL(by)[0];
    int lengthout_int = INTEGER(lengthout)[0];

    if (from_int >= to_int) {
        Rf_error("to needs to be greater than from");
    }

    if (!ISNA(by_double)) {
        return seq_by(from_int, to_int, by_double);
    } else if (lengthout_int != NA_INTEGER) {
        return seq_lengthout(from_int, to_int, lengthout_int);
    } else {
        Rf_error("Both by and length.out are NA");
    }

}