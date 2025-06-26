#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    int score;
    struct node *right;
    struct node *left;
} Node_t;

Node_t *createNode(int index, int score) {
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));
    node->index = index;
    node->left = NULL;
    node->right = NULL;
    node->score = score;
    return node;
}

void print_tree(Node_t *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->index);
    print_tree(node->left);
    print_tree(node->right);
}

Node_t* generate_tree(Node_t* nodes[], int n, int parents[], int scores[]) {
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(i, scores[i]);
    }

    for (int i = 0; i < n; i++) {
        if (parents[i] == -1) continue;

        if (nodes[parents[i]]->left == NULL)
            nodes[parents[i]]->left = nodes[i];
        else
            nodes[parents[i]]->right = nodes[i];
    }

    return nodes[0];
}

void biggest_score (Node_t* node, int path[], int result_path[], int level, int* score, int actual_score, int* depth) {

    if (node == NULL)
        return;

    path[level] = node->index;
    actual_score = actual_score + node->score;

    if (node->left == NULL && node->right == NULL) {
        if (*score < actual_score) {
            *depth = level + 1;
            for (int i = 0; i <= level; i++) {
                result_path[i] = path[i];
            }
            *score = actual_score;
        }
        return;
    }

    biggest_score(node->left, path, result_path, level + 1, score, actual_score, depth);
    biggest_score(node->right, path, result_path, level + 1, score, actual_score, depth);
}

int main (int argc, char* argv[]) {

    if (argc != 2) {
        printf("Please enter the file name\n");
        exit(EXIT_FAILURE);
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    fscanf(f, "%d", &n);

    int parents[n], scores[n];
    Node_t* nodes[n];

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &parents[i]);
    }

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &scores[i]);
    }

    Node_t *root = generate_tree(nodes, n, parents, scores);

    //print_tree(root);

    int path[n], result_path[n], depth = 0, score = 0;
    biggest_score(root, path, result_path, 0, &score, 0, &depth);

    for (int i = 0; i < depth; i++) {
        printf("%d ", result_path[i]);
    }
    printf("\n");
    printf("%d", score);
    return 0;
}
