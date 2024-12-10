#define RED 0;
#define BLACK 1;

typedef struct _node {
    struct _node* left;
    struct _node* right;
    double val;
    int color;
} node;

void recolor(node* root, node* parent, node* child) {
    child->color = RED;
    root->color = RED;
    root->left->color = BLACK;
    root->right->color = BLACK;
}