#include<R.h>
#include<Rinternals.h>


SEXP sumc(SEXP x, SEXP y) {
    if (XLENGTH(x) == 0 || XLENGTH(y) == 0) {
        Rf_error("Both vectors need to have at least one value");
    }
    if (!Rf_isReal(x) || !Rf_isReal(y)) {
        Rf_error("Both vectors need to be of numerical type");
    }

    size_t xlen = XLENGTH(x);
    size_t ylen = XLENGTH(y);

    size_t outlen = xlen > ylen ? xlen : ylen;

    double* xp = REAL(x);
    double* yp = REAL(y);

    SEXP z = Rf_allocVector(REALSXP, outlen);
    PROTECT(z);

    double* zp = REAL(z);

    int xcnt = 0, ycnt = 0, zcnt = 0;

    while (zcnt != outlen) {
        zp[zcnt] = xp[xcnt] + yp[ycnt];

        if (++xcnt == xlen) xcnt = 0;
        if (++ycnt == ylen) ycnt = 0;

        zcnt++;
    }

    UNPROTECT(1);
    return z;

}