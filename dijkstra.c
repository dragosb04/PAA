#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 5
int m[N][N];

int min (int key[], int inMST[]) {
    int minIndex = -1, min = INT_MAX;

    for (int i = 0; i < N; i++) {
        if (!inMST[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra () {
    int keys[N], visited[N];
    memset(keys, 0, N * sizeof(int));
    memset(visited, 0, N * sizeof(int));

    for (int i = 0; i < N; i++) {
        keys[i] = INT_MAX;
    }

    keys[0] = 0;

    for (int i = 1; i < N; i++) {
        int u = min(keys, visited);
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < N; v++) {
            if (!visited[v] && m[u][v] && keys[v] > keys[u] + m[u][v]) {
                keys[v] = keys[u] + m[u][v];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", keys[i]);
    }
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please enter the file name\n");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(f, "%d", &m[i][j]);
        }
    }

    fclose(f);

    dijkstra();

}
