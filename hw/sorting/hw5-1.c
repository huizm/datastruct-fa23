// 写出给出序列，以希尔排序，gap=3，2，1的排序结果。

// 用例：:3 35 13 15 20 5 9 14 6 37 59 64
// 输出：3 14 5 9 20 6 15 35 13 37 59 64
// 3 6 5 9 13 14 15 35 20 37 59 64
// 3 5 6 9 13 14 15 20 35 37 59 64

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void ShellSort(int *restrict arr, const int size, const int gap);
void hSort(int *restrict arr, const int size, const int h);

int main(void) {
    int arr[31];
    int size = 0;
    char following = ' ';
    while (following == ' ' && scanf("%d%c", &arr[size++], &following) == 2);

    ShellSort(arr, size, 3);
    return 0;
}

void ShellSort(int *restrict arr, const int size, const int gap) {
    for (int h = gap; h > 0; h--) {
        hSort(arr, size, h);
        
        printf("%d", arr[0]);
        for (int i = 1; i < size; i++) {
            printf(" %d", arr[i]);
        }
        putchar('\n');
    }
}

void hSort(int *restrict arr, const int size, const int h) {
    for (int i = h; i < size; i++) {
        for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
            int temp = arr[j];
            arr[j] = arr[j - h];
            arr[j - h] = temp;
        }
    }
}
