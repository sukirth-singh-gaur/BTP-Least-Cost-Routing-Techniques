#include <stdio.h>
#include <stdlib.h>

// This function gives us the cost estimate of 2 destination nodes and 1 source node
float dest2(float p[2]) {
    float x;
    x = (1 + (p[0]) * (1 - p[1]) * (1 / p[1]) + (1 - p[0]) * (p[1]) * (1 / p[0]))
        / (1 - (1 - p[0]) * (1 - p[1]));
    return x;
}

// This function gives us the cost estimate of 3 destination nodes and 1 source node
float dest3(float p[3]) {
    float arr01[2] = {p[0], p[1]};
    float arr12[2] = {p[1], p[2]};
    float arr20[2] = {p[0], p[2]};
    float x = (1 + (1 - p[0]) * (1 - p[1]) * (p[2]) * (dest2(arr01))   
                + (1 - p[0]) * (1 - p[2]) * (p[1]) * (dest2(arr20)) 
                + (1 - p[1]) * (1 - p[2]) * (p[0]) * (dest2(arr12))
                + (1 - p[0]) * (p[1]) * (p[2]) * (1 / p[0])
                + (1 - p[1]) * (p[0]) * (p[2]) * (1 / p[1])
                + (1 - p[2]) * (p[0]) * (p[1]) * (1 / p[2]))
                / (1 - (1 - p[0]) * (1 - p[1]) * (1 - p[2]));
    return x;
}

// This function gives us the cost estimate of 4 destination nodes and 1 source node
float dest4(float p[4]) {
    float arr01[2] = {p[0], p[1]};
    float arr12[2] = {p[1], p[2]};
    float arr02[2] = {p[0], p[2]};
    float arr23[2] = {p[2], p[3]};
    float arr03[2] = {p[0], p[3]};
    float arr13[2] = {p[1], p[3]};
    float arr012[3] = {p[0], p[1], p[2]};
    float arr123[3] = {p[1], p[2], p[3]};
    float arr013[3] = {p[0], p[1], p[3]};
    float arr023[3] = {p[0], p[2], p[3]};
    
    float x = (1 + (1 - p[0]) * (1 - p[1]) * (p[2]) * p[3] * (dest2(arr01)) 
                + (1 - p[0]) * (p[1]) * (1 - p[2]) * p[3] * (dest2(arr02))
                + (1 - p[0]) * (p[1]) * (p[2]) * (1 - p[3]) * (dest2(arr03))
                + (p[0]) * (1 - p[1]) * (1 - p[2]) * p[3] * (dest2(arr12))
                + (p[0]) * (p[1]) * (1 - p[2]) * (1 - p[3]) * (dest2(arr23))
                + (1 - p[0]) * (p[1]) * (p[2]) * (1 - p[3]) * (dest2(arr13))
                + (1 - p[0]) * (1 - p[1]) * (1 - p[2]) * (p[3]) * (dest3(arr012))
                + (p[0]) * (1 - p[1]) * (1 - p[2]) * (1 - p[3]) * (dest3(arr123))
                + (1 - p[0]) * (1 - p[1]) * (p[2]) * (1 - p[3]) * (dest3(arr013))
                + (1 - p[0]) * (p[1]) * (1 - p[2]) * (1 - p[3]) * (dest3(arr023))
                + (1 - p[0]) * (p[1]) * (p[2]) * (p[3]) * (1 / p[0])
                + (1 - p[1]) * (p[0]) * (p[2]) * (p[3]) * (1 / p[1])
                + (1 - p[2]) * (p[0]) * (p[1]) * (p[3]) * (1 / p[2])
                + (p[2]) * (p[0]) * (p[1]) * (1 - p[3]) * (1 / p[3]))
                / (1 - (1 - p[0]) * (1 - p[1]) * (1 - p[2]) * (1 - p[3])); 
    return x;
}

int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    if (n < 1) exit(0);
    float mtx[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mtx[i][j] = 0;
        }
    }
    while (1) {
        int from, to;
        float prob;
        printf("Enter the nodes to connect (0 to %d) or (-1 to exit):\n", n - 1);
        printf("From node: ");
        scanf("%d", &from);
        if (from == -1) break;
        printf("To node: ");
        scanf("%d", &to);
        if (to == -1) break;
        if (from >= n || to >= n || from < 0 || to < 0) {
            printf("\nNot within the limits\n");
            continue;
        }
        printf("Enter the probability (0 to 1): ");
        scanf("%f", &prob);
        if (prob < 0 || prob > 1) {
            printf("\nNot within the limits\n");
            continue;
        }
        mtx[from][to] = prob;
    }
    printf("Enter the source node: ");
    int s;
    scanf("%d", &s);
    while (s < 0 || s >= n) {
        printf("Enter the source node again: ");
        scanf("%d", &s);
    }
    float* arr = (float*) malloc(n * sizeof(float));
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (mtx[s][i] > 0) {
            arr[count] = mtx[s][i];
            count++;
        }
    }
    if (count == 2) {
        printf("Minimum expected transmissions: %f\n", dest2(arr));
    } else if (count == 3) {
        printf("Minimum expected transmissions: %f\n", dest3(arr));
    } else if (count == 4) {
        printf("Minimum expected transmissions: %f\n", dest4(arr));
    } else {
        printf("ERROR: The source node must have exactly 2, 3, or 4 connected nodes.\n");
    }
    printf("\nAdjacency Matrix\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.2f", mtx[i][j]);
        }
        printf("\n");
    }
    free(arr);
    return 0;
}