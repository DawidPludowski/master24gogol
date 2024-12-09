// nice resource: https://www.geeksforgeeks.org/insertion-in-an-avl-tree/

#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    struct _node* left;
    struct _node* right;
    double val;
    int height;
} node;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(node* n) {
    if (n == NULL) return 0;
    return n->height;
}

void right_right(node** n) {
    node* l = (*n)->left;
    node* r = (*n)->right;
    node* ll = l->left;
    node* lr = l->right;

    node* root = (*n);
    root->left = lr;

    l->right = root;
    *n = l;
    (*n)->height = max(height((*n)->left), height((*n)->right)) + 1;
    root->height = max(height(root->left), height(root->right)) + 1;
}

void left_right(node** n) {

    node* l = (*n)->left;
    node* lr = l->right;
    node* T2 = lr->left;

    (*n)->left = lr;
    lr->left = l;
    l->right = T2;

    right_right(n);

}

void main() {

    node* root = malloc(sizeof(node));

    node* X = root;
    X->left = NULL;
    X->right = NULL;
    X->val = 1;
    X->height = 3;

    node* Y = malloc(sizeof(node));
    Y->left = NULL;
    Y->right = NULL;
    Y->val = 2;
    Y->height = 2;

    node* Z = malloc(sizeof(node));
    Z->left = NULL;
    Z->right = NULL;
    Z->val = 3;
    Z->height = 1;

    node* T3 = malloc(sizeof(node));
    T3->left = NULL;
    T3->right = NULL;
    T3->val = 4;
    T3->height = 1;



    X->left = Y;
    Y->left = Z;
    Y->right = T3;

    right_right(&root);

    printf("%d\n", (int) root->val);
    printf("%d\n", (int) root->left->val);
    printf("%d\n", (int) root->right->val);
    printf("%d\n", (int) root->right->left->val);

    printf("\n");

    root = X; 

    free(root->left);
    free(root->right);

    root->left = Y;
    Y->right = Z;
    Z->left = T3;

    left_right(&root);

    printf("%d\n", (int) root->val);
    printf("%d\n", (int) root->left->val);
    printf("%d\n", (int) root->right->val);
    printf("%d\n", (int) root->left->right->val);

}