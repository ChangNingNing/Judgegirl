#include <stdio.h>
#include <stdint.h>
// #define DEBUG
#define UINT uint32_t
#define MAXN 1024
void multiply(int N, UINT A[][MAXN], UINT B[][MAXN], UINT C[][MAXN]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            UINT sum = 0;    // overflow, let it go.
            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}
void add(int N, UINT A[][MAXN], UINT B[][MAXN], UINT C[][MAXN]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}
void rand_gen(UINT c, int N, UINT A[][MAXN]) {
    UINT x = 2, n = N*N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c + i + j)%n;
            A[i][j] = x;
        }
    }
}
void print_matrix(int N, UINT A[][MAXN]) {
    for (int i = 0; i < N; i++) {
        fprintf(stderr, "[");
        for (int j = 0; j < N; j++)
            fprintf(stderr, " %u", A[i][j]);
        fprintf(stderr, " ]\n");
    }
}
UINT signature(int N, UINT A[][MAXN]) {
    UINT h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            h = (h + A[i][j]) * 2654435761LU;
    }
    return h;
}
UINT IN[6][MAXN][MAXN], TMP[6][MAXN][MAXN];
int main() {
    int N, S[6];
    scanf("%d", &N);
    for (int i = 0; i < 6; i++) {
        scanf("%d", &S[i]);
        rand_gen(S[i], N, IN[i]);
    }
    // AB
    multiply(N, IN[0], IN[1], TMP[0]);
    // CD
    multiply(N, IN[2], IN[3], TMP[1]);
    // AB+CD
    add(N, TMP[0], TMP[1], TMP[2]);
    printf("%u\n", signature(N, TMP[2]));
 
    // ABE
    multiply(N, TMP[0], IN[4], TMP[3]);
    // CDF
    multiply(N, TMP[1], IN[5], TMP[4]);
    // ABE+CDF
    add(N, TMP[3], TMP[4], TMP[5]);
    printf("%u\n", signature(N, TMP[5]));
    return 0;
}
