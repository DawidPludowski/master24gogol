#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    struct _node** ns;
    int nn;
    int id;
} node;

static void _dfs(node* n, int* out, int* out_el, int* checklist) {
    if (checklist[n->id] == 1) return;

    checklist[n->id] = 1;
    int nn = n->nn;
    for (int i = 0; i < nn; i++) {
        _dfs(*(n->ns + i), out, out_el, checklist);
    }
    out[*out_el] = n->id;
    out_el[0]++;

}

int* dfs(node* starting_node, int max_nodes) {
    node* n = starting_node;
    int* out = malloc(sizeof(int)*max_nodes);
    int* checklist = malloc(sizeof(int)*max_nodes);
    int* out_el = malloc(sizeof(int)*1);

    out_el[0] = 0;
    for (int i = 0; i < max_nodes; i++) checklist[i] = 0;
    for (int i = 0; i < max_nodes; i++) out[i] = -1;
    
    _dfs(starting_node, out, out_el, checklist);

    return out;
}

int* bfs(node* starting_node, int max_nodes) {
    node* n = starting_node;
    int* out = malloc(sizeof(int)*max_nodes);
    int* checklist = malloc(sizeof(int)*max_nodes);
    node** queue = malloc(sizeof(node)*max_nodes);
    int q_start = 0;
    int q_end = 0;
    int out_el = 0;

    for (int i = 0; i < max_nodes; i++) checklist[i] = 0;
    for (int i = 0; i < max_nodes; i++) queue[i] = NULL;
    for (int i = 0; i < max_nodes; i++) out[i] = -1;
    
    // algo
    queue[0] = starting_node;
    checklist[n->id] = 1;

    do {
        n = queue[q_start++];
        out[out_el++] = n->id;
        
        for (int i = 0; i < n->nn; i++) {
            if (checklist[n->ns[i]->id] != 1) {
                checklist[n->ns[i]->id] = 1;
                queue[++q_end] = n->ns[i];
            }
        }

    } while (q_start != q_end + 1);

    return out;
}

node* make_node(int id, int nn) {
    node* n = malloc(sizeof(node));
    n->id = id;
    n->nn = nn;
    n->ns = malloc(sizeof(node)*nn);
    return n;
}

void main() {
    /*
      ->2 -> 5
    1 ->3 -> 6
      ->4 -> 7
    */
    node* n1 = make_node(1, 3);
    node* n2 = make_node(2, 2);
    node* n3 = make_node(3, 2);
    node* n4 = make_node(4, 2);
    node* n5 = make_node(5, 1);
    node* n6 = make_node(6, 1);
    node* n7 = make_node(7, 1);

    n1->ns[0] = n2;
    n1->ns[1] = n3;
    n1->ns[2] = n4;

    n2->ns[0] = n1;
    n2->ns[1] = n5;

    n3->ns[0] = n1;
    n3->ns[1] = n6;

    n4->ns[0] = n1;
    n4->ns[1] = n7;

    n5->ns[0] = n2;
    n6->ns[0] = n3;
    n7->ns[0] = n4;

    int* res1 = dfs(n1, 7);
    for (int i = 0; i < 7; i++) printf("%d\n", res1[i]);

    printf("-----------\n");

    int* res2 = bfs(n1, 7);
    for (int i = 0; i < 7; i++) printf("%d\n", res2[i]);
}
