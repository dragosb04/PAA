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

int primMST () {
    int parent[N], key[N], inMST[N];
    parent[0] = -1;

    memset(inMST, 0, sizeof(inMST));
    key[0] = 0;
    for (int i = 1; i < N; i++) {
        key[i] = INT_MAX;
    }

    for (int i = 0; i < N - 1; i++) {
        int u = min (key, inMST);
        inMST[u] = 1;

        for (int v = 0; v < N; v++) {
            if (m[u][v] && !inMST[v] && m[v][u] < key[v]) {
                key[v] = m[v][u];
                parent[v] = u;
            }
        }
    }

    int result = 0;

    for (int i = 0; i < N; i++) {
        printf("%d ", parent[i]);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        result += key[i];
        printf("%d ", key[i]);
    }
    printf("\n");

    return result;
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

    printf("%d", primMST());

}
