#include <stdio.h>
#include <string.h>

int m[20][20];

void dfs(int v[], int node, int* count) {
    v[node] = 1;
    for (int i = 0; i < 20; i++) {
        if (v[i] == 0 && m[node][i] == 1) {
            *count = *count + 1;
            dfs(v, i, count);
        }
    }
}

void get_most_influent_permissions(int n) {

    int count = 0;

    int max_count = -1, index_max = -1;
    for (int i = 1; i < n; i++) {
        int visited_nodes[n];
        memset(visited_nodes, 0, sizeof(visited_nodes));
        count = 0;
        dfs(visited_nodes, i, &count);
        if (count > max_count) {
            max_count = count;
            index_max = i;
        }
    }

    printf("%d\n", index_max + 1);
}

void get_dangerous_permissions(int n, int permissions_until_dangerous) {
    int count = 0;
    int nodes[n];
    memset(nodes, 0, sizeof(nodes));
    for (int i = 0; i < n; i++) {
        int visited_nodes[n];
        count = 0;
        memset(visited_nodes, 0, sizeof(visited_nodes));
        dfs(visited_nodes, i, &count);
        if (count > permissions_until_dangerous) {
            nodes[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (nodes[i] == 1)
            printf("%d ", i + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    int perms_until_risk;
    fscanf(f, "%d", &perms_until_risk);

    int n;
    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(f, "%d", &m[i][j]);
        }
    }

    fclose(f);

    get_most_influent_permissions(n);
    get_dangerous_permissions(n, perms_until_risk);
    return 0;
}
