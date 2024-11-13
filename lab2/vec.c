#include<R.h>
#include<Rinternals.h>

static SEXP cumsum_double(const double* vec, const size_t len, const int na_rm) {
    
    SEXP x = Rf_allocVector(REALSXP, len); 
    PROTECT(x);

    double* xp = REAL(x);
    double sum = 0.0;

    for (int i = 0; i < len; i++) {
        if (ISNA(vec[i])) {
            if (na_rm != 0) {
                xp[i] = sum;
            } else {
                xp[i] = NA_REAL;
            }
        } else {
            sum += vec[i];
            xp[i] = sum;
        }
    }
    UNPROTECT(1);

    return x;
}

static SEXP cumsum_int(const int* vec, const size_t len, const int na_rm) {

    SEXP x = Rf_allocVector(REALSXP, len); 
    PROTECT(x);

    double* xp = REAL(x);
    int sum = 0;

    for (int i = 0; i < len; i++) {
        if (vec[i] == NA_INTEGER) {
            if (na_rm != 0) {
                xp[i] = sum;
            } else {
                xp[i] = NA_REAL;
            }
        } else {
            sum += vec[i];
            xp[i] = sum;
        }
    }
    UNPROTECT(1);

    return x;
}

static SEXP cumsum_logical(const int* vec, const size_t len, const int na_rm) {

    SEXP x = Rf_allocVector(REALSXP, len); 
    PROTECT(x);

    double* xp = REAL(x);
    int sum = 0;

    for (int i = 0; i < len; i++) {
        if (vec[i] == NA_LOGICAL) {
            if (na_rm != 0) {
                xp[i] = sum;
            } else {
                xp[i] = NA_REAL;
            }
        } else {
            sum += vec[i] != 0 ? 1 : 0;
            xp[i] = sum;
        }
    }
    UNPROTECT(1);

    return x;
}

SEXP c_cumsum(SEXP vec, SEXP na_rm) {

    if (!Rf_isReal(vec) & !Rf_isInteger(vec) & !Rf_isLogical(vec)) {
        Rf_error("Vector should be of type (real | integer | logical)");
    }

    if (XLENGTH(vec) == 0) {
        if (Rf_isReal(vec)) {
            return Rf_ScalarReal(NA_REAL);
        } else if (Rf_isInteger(vec)) {
            return Rf_ScalarInteger(NA_INTEGER);
        } else {
            return Rf_ScalarLogical(NA_LOGICAL);
        }
    }

    if (!Rf_isLogical(na_rm)) {
        Rf_error("na_rm parameter should be of logical type");
    }
    if (XLENGTH(na_rm) != 1) {
        Rf_error("na_rm should be a vector of size equal to 1");
    }

    const size_t vec_len = XLENGTH(vec);
    const int _na_rm = LOGICAL(na_rm)[0];

    if (_na_rm == NA_LOGICAL) {
        Rf_error("na_rm cannot be a NA");
    }

    SEXP out;
    if (Rf_isReal(vec)) {
        out = cumsum_double(REAL(vec), vec_len, _na_rm);
        return out;    
    } else if (Rf_isInteger(vec)) {
        out = cumsum_int(INTEGER(vec), vec_len, _na_rm);
        return out;    
    } else {
        out = cumsum_logical(LOGICAL(vec), vec_len, _na_rm);
        return out;
    }

}