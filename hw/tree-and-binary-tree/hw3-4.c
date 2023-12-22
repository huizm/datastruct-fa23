// 利用筛选法对给定的关键字序列构成大顶堆，并采用顺序表存储输出该大顶堆（关键字之间以空格分隔）。
// 测试用例1：输入：14 16 21 18 30 35
// 输出：35 30 21 18 16 14

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void MaxHeap(int input[21], const int size);
void sink(int input[21], const int root, const int size);

int main(void) {
    int maxHeap[21];

    char following = ' ';
    int index = 0;
    int success = 2;
    while (success > 1 && following == ' ') success = scanf("%d%c", &maxHeap[++index], &following);

    MaxHeap(maxHeap, index);

    printf("%d", maxHeap[1]);
    for (int i = 2; i <= index; i++) {
        printf(" %d", maxHeap[i]);
    }

    return 0;
}

void MaxHeap(int input[21], const int size) {
    for (int root = size / 2; root >= 1; root--) {
        sink(input, root, size);
    }
}

void sink(int input[21], const int root, const int size) {
    if (root * 2 > size) return;

    int largest = root * 2 + 1 <= size && input[root * 2 + 1] > input[root * 2] ? root * 2 + 1 : root * 2;

    if (input[root] >= input[largest]) return;
    else {
        int temp = input[root];
        input[root] = input[largest];
        input[largest] = temp;
        sink(input, largest, size);
    }
}
