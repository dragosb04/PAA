#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

int m[N][N];

void dfs (int v[], int node, int temp[][N]) {
    v[node] = 1;
    for (int i = 0; i < N; i++) {
        if (temp[node][i] && !v[i]) {
            dfs(v, i, temp);
        }
    }
}

void most_dangerous_computers(int n) {
    int count = 0, max_count = -1;
    int nodes[n];
    memset(nodes, 0, sizeof(nodes));
    for (int i = 0; i < n; i++) {
        count = 0;
        for (int j = 0; j < n; j++) {
            if (m[i][j] == 1)
                count++;
        }
        nodes[i] = count;
        if (count > max_count) {
            max_count = count;
        }
    }
    // printf("Max count is %d\n", max_count);
    for (int i = 0; i < n; i++) {
        if (nodes[i] == max_count) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void critical_computers (int n) {
    int critical_nodes[n];
    memset(critical_nodes, 0, sizeof(critical_nodes));
    for (int i = 0; i < n; i++) {
        int temp[n][n];
        int nodes[n];
        memset(nodes, 0, sizeof(nodes));
        memcpy(temp, m, sizeof(m));
        for (int j = 0; j < n; j++) {
            temp[i][j] = temp[j][i] = 0;
        }
        for (int j = 0; j < n; j++) {
            if (j != i) {
                dfs(nodes, j, temp);
                break;
            }
        }
        for (int j = 0; j < n; j++) {
            if (j != i && nodes[j] == 0) {
                critical_nodes[i] = 1;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (critical_nodes[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
}

int main (int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file %s\n", argv[1]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(f, "%d", &m[i][j]);
        }
    }

    fclose(f);

    most_dangerous_computers(N);
    critical_computers(N);
    return 0;
}
