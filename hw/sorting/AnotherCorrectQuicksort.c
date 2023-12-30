// This explains part of the reason why these hw is extremely annoying. When you are working them out, you're not
// inventing correct algorithms, but you're chasing the only one given output.

// 给出已给序列快速排序的每趟结果。

// 用例：输入：3 35 13 15 20 5 9 14 6 37 59 64
// 输出：[3] 35 13 15 20 5 9 14 6 37 59 64
// 3 | 6 13 15 20 5 9 14 [35] 37 59 64
// 3 | 5 [6] 15 20 13 9 14 | 35 | [37] 59 64
// 3 | [5] | 6 | 14 9 13 [15] 20 | 35 | 37 | [59] 64
// 3 | 5 | 6 | 13 9 [14] | 15 | [20] | 35 | 37 | 59 | [64]
// 3 | 5 | 6 | 9 [13] | 14 | 15 | 20 | 35 | 37 | 59 | 64

// testcase 1: 21 25 49 25 16 8

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int maxRound = 0;

int (*Quicksort(int *restrict input, const int size))[31];
void sort(int *restrict input, int (*restrict rounds)[31], const int round, const int lo, const int hi);
int partition(int *restrict input, const int lo, const int hi);

int main(void) {
    int input[31];
    int size = 0;
    char following = ' ';
    while (following == ' ' && scanf("%d%c", &input[size++], &following) == 2);

    int (*rounds)[31] = Quicksort(input, size);

    for (int i = 0; i <= maxRound; i++) {
        printf("%d", rounds[i][0]);
        for (int j = 1; j < size; j++) {
            printf(" %d", rounds[i][j]);
        }
        putchar('\n');
    }

    return 0;
}

int (*Quicksort(int *restrict input, const int size))[31] {
    int (*rounds)[31] = (int (*)[31]) malloc(10 * 31 * sizeof(int));

    sort(input, rounds, 0, 0, size -1);

    return rounds;
}

void sort(int *restrict input, int (*restrict rounds)[31], const int round, const int lo, const int hi) {
    if (hi == lo) {
        for (int i = round; i < 10; i++) {
            rounds[i][lo] = input[lo];
        }
        return;
    } else if (hi < lo) return;

    int mid = partition(input, lo, hi);

    for (int i = lo; i <= hi; i++) {
        rounds[round][i] = input[i];
    }
    for (int i = round + 1; i < 10; i++) {
        rounds[i][mid] = input[mid];
    }

    sort(input, rounds, round + 1, lo, mid - 1);
    sort(input, rounds, round + 1, mid + 1, hi);

    if (round > maxRound) maxRound = round;
}

int partition(int *restrict input, const int lo, const int hi) {
    int pivot = input[lo];
    int i = lo, j = hi + 1;
    while (i < j) {
        while (input[++i] < pivot) { if (i >= hi) break; }
        while (input[--j] > pivot) { if (j <= lo) break; }
        if (j <= i) break;

        int temp = input[i];
        input[i] = input[j];
        input[j] = temp;
    }

    input[lo] = input[j];
    input[j] = pivot;
    return j;
}
