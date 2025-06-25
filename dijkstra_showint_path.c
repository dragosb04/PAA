#include <limits.h>
#include <stdio.h>
#include <string.h>
#define N 20

void print_path (int parents[], int node) {
    if (parents[node] == -1) {
        printf("%d ", node);
        return;
    }

    print_path(parents, parents[node]);
    printf("%d ", node);
}

int min (int keys[], int m[][N], int visited[]) {
    int min = INT_MAX, min_index = -1;

    for (int i = 0; i < N; i++) {
        if (!visited[i] && keys[i] < min) {
            min = keys[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra (int m[][N], int node) {
    int keys[N], visited[N], parent[N];

    for (int i = 0; i < N; i++) {
        keys[i] = INT_MAX;
        visited[i] = 0;
    }

    keys[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < N; i++) {
        int u = min (keys, m, visited);
        if (u == -1) break;
        visited[u] = 1;

        for (int j = 0; j < N; j++) {
            if (m[u][j] && !visited[j] && keys[j] > keys[u] + m[u][j]) {
                keys[j] = keys[u] + m[u][j];
                parent[j] = u;
            }
        }
    }

    print_path(parent, node);
}

int main (int argc, char *argv[]) {

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int m[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(f, "%d", &m[i][j]);
        }
    }

    fclose(f);

    dijkstra(m, 12);

    return 0;
}
