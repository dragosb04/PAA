#include <stdio.h>

int m[30][30];

void calculate_profit (int n) {
    int in_sum = 0, out_sum = 0;
    for (int i = 0; i < n; i++) {
        in_sum = 0;
        out_sum = 0;
        for (int j = 0; j < n; j++) {
            out_sum += m[i][j];
            in_sum += m[j][i];
        }

        printf("Agent %d: in_sum = %d, out_sum = %d, dif = %d \n", i, in_sum, out_sum, out_sum - in_sum);
    }

}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please enter the file name\n");
        return -1;
    }
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    int n = 0;
    fscanf(f, "%d", &n);

    int x, y, c;
    while (fscanf(f, "%d %d %d", &x, &y, &c) == 3) {
        m[x][y] = c;
    }

    fclose(f);

    calculate_profit(n);

    return 0;
}
