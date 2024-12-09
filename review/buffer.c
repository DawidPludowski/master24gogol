#include <stdlib.h>
#include <stdio.h>

typedef struct _buffer {
    size_t n;
    size_t start;
    size_t end;
    size_t n_el;
    double* data;
} buffer;

void put_last(buffer* b, double el) {
    if (b->n_el == b->n) return;

    if (b->end == b->n) b->end = 0;
    else b->end++;

    *(b->data + b->end - 1) = el;

    b->n_el++;

}

void put_first(buffer* b, double el) {
    if (b->n_el == b->n) return;


    if (b->start == 0) b->start = b->n-1;
    else b->start--;

    *(b->data + b->start) = el; 
    b->n_el++;
}

double pop_first(buffer* b) {

    if (b->n_el == 0) return -1;

    double el = *(b->data + b->start);

    if (b->start == b->n-1) b->start = 0; 
    else b->start++;

    b->n_el--;

    return el;
}

double pop_last(buffer* b) {
    double el;

    if (b->n_el == 0) return -1;

    if (b->end != 0) el = *(b->data + b->end - 1);
    else el = *(b->data + b->n - 1);

    if (b->end == 0) b->end = b->n-1; 
    else b->end--;

    b->n_el--;

    return el;
}

void main() {

    double el;

    buffer* b = malloc(sizeof(buffer));
    b->data = malloc(sizeof(double)*5);
    b->n = 5;
    b->start = 0;
    b->end = 0;
    b->n_el = 0;

    put_last(b, 1.0);
    put_first(b, 2.0);
    put_last(b, 3.0);
    put_last(b, 4.0);

    size_t n_el = b->n_el;


    for (int i = 0; i < n_el; i++) {
        printf("%d, ", (int) b->start);
        el = pop_first(b);
        printf("%d\n", (int) el);
    }

    printf("\n");

    free(b->data);

    b->data = malloc(sizeof(double)*5);
    b->n = 5;
    b->start = 0;
    b->end = 0;
    b->n_el = 0;

    put_last(b, 1.0);
    put_first(b, 2.0);
    put_last(b, 3.0);
    put_last(b, 4.0);

    n_el = b->n_el;


    for (int i = 0; i < n_el; i++) {
        el = pop_last(b);
        printf("%d, ", (int) b->end);
        printf("%d\n", (int) el);
    }
}