#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int index;
    struct Node* prim_fiu;
    struct Node* frate_dreapta;
} Node_t;

Node_t* create_node(int index) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->index = index;
    node->prim_fiu = NULL;
    node->frate_dreapta = NULL;
    return node;
}

Node_t* generate_tree(Node_t* nodes[], int n, FILE* f) {
    int frate_dreapta, prim_fiu;

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d %d", &prim_fiu, &frate_dreapta);
        if (frate_dreapta != -1)
            nodes[i]->frate_dreapta = nodes[frate_dreapta];
        if (prim_fiu != -1)
            nodes[i]->prim_fiu = nodes[prim_fiu];
    }

    return nodes[0];
}

int max_depth(Node_t* node) {
    if (node == NULL) return 0;
    int left = max_depth(node->prim_fiu);
    int right = max_depth(node->frate_dreapta);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

void generate_longest_path (Node_t* node, int path[], int* max_len, int level, int result[]) {
    if (node == NULL) return;

    path[level] = node->index;

    if (node->prim_fiu == NULL && node->frate_dreapta == NULL) {
        if (level + 1 > *max_len) {
            *max_len = level + 1;
            for (int i = 0; i < *max_len; i++)
                result[i] = path[i];
        }
    }

    generate_longest_path(node->prim_fiu, path, max_len, level + 1, result);
    generate_longest_path(node->frate_dreapta, path, max_len, level + 1, result);
}

int main (int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: ./filename <file>\n");
        exit(EXIT_FAILURE);
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    fscanf(f, "%d", &n);

    Node_t* nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = create_node(i);
    }

    Node_t* root = generate_tree(nodes, n, f);

    printf("%d", max_depth(root));
    printf("\n");
    int result[n], path[n], max_len = 0;
    generate_longest_path(root, path, &max_len, 0, result);

    for (int i = 0; i < max_len; i++) {
        printf("%d ", result[i]);
    }
    for (int i = 0; i < n; i++) {
        free(nodes[i]);
    }
    return 0;
}
