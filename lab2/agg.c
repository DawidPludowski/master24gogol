#include<R.h>
#include<Rinternals.h>
// #include<Rmath.h>

static double product_double(const double* vec, const size_t len, const int na_rm) {
    double out = 1.0;

    for (int i = 0; i < len; i++) {
        if (ISNA(vec[i])) {
            if (na_rm != 0) {
                continue;
            } else {
                return NA_REAL;
            }
        }
        out *= vec[i];
    }

    return out;
}

static int product_int(const int* vec, const size_t len, const int na_rm) {
    int out = 1;

    for (int i = 0; i < len; i++) {
        if (vec[i] == NA_INTEGER) {
            if (na_rm != 0) {
                continue;
            } else {
                return NA_INTEGER;
            }
        }
        out *= vec[i];
    }

    return out;
}

static int product_logical(const int* vec, const size_t len, const int na_rm) {
    int out = 1;

    for (int i = 0; i < len; i++) {
        if (vec[i] == NA_LOGICAL) {
            if (na_rm != 0) {
                continue;
            } else {
                return NA_LOGICAL;
            }
        }
        if (vec[i] == 0) {
            out = 0;
            break;
        }
    }

    return out;
}

SEXP c_prod(SEXP vec, SEXP na_rm) {
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

    if (Rf_isReal(vec)) {
        double out_double = product_double(REAL(vec), vec_len, _na_rm);
        return Rf_ScalarReal(out_double);
    } else if (Rf_isInteger(vec)) {
        int out_int = product_int(INTEGER(vec), vec_len, _na_rm);
        return Rf_ScalarInteger(out_int);
    } else {
        int out_logical = product_logical(LOGICAL(vec), vec_len, _na_rm);
        return Rf_ScalarLogical(out_logical);
    }

} 