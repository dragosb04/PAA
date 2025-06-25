#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int index;
    struct Node* right;
    struct Node* left;
} Node_t;

typedef Node_t* NodePtr;

Node_t* create_node(int index) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->index = index;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void generate_tree(NodePtr* root, FILE* f, int n) {
    int parent;
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &parent);
        if (parent == 0) continue;

        if (root[parent - 1]->left == NULL) {
            root[parent - 1]->left = root[i];
        }
        else root[parent - 1]->right = root[i];
    }
}

void printTree(Node_t* node, int level) {
    if (node == NULL) return;

    printf("%d ", node->index + 1);
    printTree(node->left, level + 1);
    printTree(node->right, level + 1);
}

int maxdepth (Node_t* node) {
    if (node == NULL) return 0;
    int left = maxdepth(node->left);
    int right = maxdepth(node->right);
    if (left < right) return right + 1;
    else return left + 1;
}

void simulate_session(Node_t* root, FILE* f) {
    int response;

    Node_t* curr = root;
    while (fscanf(f, "%d", &response) == 1) {
        if (response == 0) {
            curr = curr->left;
        }
        else curr = curr->right;

        if (curr == NULL) {
            printf("0\n");
            return;
        }
    }

    printf("%d", maxdepth(curr));

}

int main(int argc, char* argv[]) {

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int n;
    fscanf(f, "%d", &n);

    Node_t** root = malloc(sizeof(Node_t*) * n);

    for (int i = 0; i < n; i++) {
        root[i] = create_node(i);
    }

    generate_tree(root, f, n);

    fclose(f);

    Node_t* root_node = root[0];

    FILE* fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    simulate_session(root_node, fp);
   // printTree(root_node, 0);

    return 0;
}
