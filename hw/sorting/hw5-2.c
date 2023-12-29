// 写出给出序列的2路归并排序每趟的结果。

// 用例：输入：3 35 13 15 20 5 9 14 6 37 59 64
// 输出：3 13 35 15 5 20 9 6 14 37 59 64
// 3 13 35 5 15 20 6 9 14 37 59 64
// 3 5 13 15 20 35 6 9 14 37 59 64
// 3 5 6 9 13 14 15 20 35 37 59 64

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int maxRound = 0;

int (*MergeSort(int *restrict input, const int size))[31];
void sort(int *restrict input, int (*restrict rounds)[31], const int round, const int lo, const int hi);
void merge(int *restrict input, int (*restrict rounds)[31], const int round, const int lo, const int mid, const int hi);

int main(void) {
    int input[31];
    int size = 0;
    char following = ' ';
    while (following == ' ' && scanf("%d%c", &input[size++], &following) == 2);

    int (*rounds)[31] = MergeSort(input, size);
    for (int i = maxRound; i >= 0; i--) {
        printf("%d", rounds[i][0]);
        for (int j = 1; j < size; j++) {
            printf(" %d", rounds[i][j]);
        }
        putchar('\n');
    }

    return 0;
}

int (*MergeSort(int *restrict input, const int size))[31] {
    int (*rounds)[31] = (int (*)[31]) malloc(8 * 31 * sizeof(int));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < size; j++) {
            rounds[i][j] = input[j];
        }
    }

    sort(input, rounds, 0, 0, size - 1);

    return rounds;
}

void sort(int *restrict input, int (*restrict rounds)[31], const int round, const int lo, const int hi) {
    if (hi <= lo) return;

    int mid = (lo + hi) / 2;
    if ((hi - lo + 1) % 2 > 0) mid--;
    sort(input, rounds, round + 1, lo, mid);
    sort(input, rounds, round + 1, mid + 1, hi);
    merge(input, rounds, round, lo, mid, hi);
}

void merge(int *restrict input, int (*restrict rounds)[31], const int round, const int lo, const int mid, const int hi) {
    int i = lo, j = mid + 1;
    int aux[31];

    for (int k = lo; k <= hi; k++) {
        aux[k] = input[k];
    }

    for (int k = lo; k <= hi; k++) {
        if (i > mid) input[k] = aux[j++];
        else if (j > hi) input[k] = aux[i++];
        else if (aux[i] <= aux[j]) input[k] = aux[i++];
        else input[k] = aux[j++];
    }

    // record current round
    for (int k = lo; k <= hi; k++) {
        rounds[round][k] = input[k];
    }

    maxRound = round > maxRound ? round : maxRound;
}
