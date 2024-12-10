#include <stdlib.h>

#define ROOT 1
#define NOTROOT 0

typedef struct _node {
    double* data;
    struct _node** pointers;
    int t;
    int n_el;
    int is_root;
} node;

node* create_node(int t, int is_root) {
    int m = 2 * t + 1;
    node* n = malloc(sizeof(node));
    n->data = malloc(sizeof(double)*m);
    n->pointers = malloc(sizeof(node)*(m+1));
    n->t = t;
    n->n_el = 0;
    n->is_root = is_root;

    for (int i = 0; i < m+1; i++) {
        (n->pointers)[i] = NULL;
    }

    return n;
}

static void _push_to_not_full(node** n, double el) {
    (*n)->data[(*n)->n_el + 1] = el;
    (*n)->n_el++;   
}

int traverse(node** n, double el) { // return pointer to go, -1 otherwise
    double* data = (*n)->data;
    int n_el = (*n)->n_el;
    for (int i = 0; i < n_el; i++) {
        if (el < data[i]) {
            if (*((*n)->pointers + i) != NULL) return i;
            else return -1;
        } else if (el == data[i]) {
            return -1;
        }
    }
}

void push(node** n, double el) {
    int m = (*n)->t * 2 + 1;
    int idx;

    node* cn;
    
    if ((*n)->is_root && (*(*n)->pointers) == NULL && (*n)->n_el < m) { // not filled root without childs
        _push_to_not_full(n, el);
    } else if (((*n)->is_root) && (*(*n)->pointers != NULL)) { // root with childs
        while (idx = traverse(n, el) >= 0) {
            cn = (*((*n)->pointers + idx));
        }
        if (cn->n_el < m) {
            _push_to_not_full(&cn, el);
        }
    }
}

void main() {

    node* root = create_node(2, ROOT);


}

