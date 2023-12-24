// 对给定的二叉树分别输出其先序遍历、中序遍历后序遍历序列。测试用例中，0代表空。
// 测试用例：输入：AB0C
// 输出：ABC
// CBA
// CBA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void preOrderPrint(char *bst, int i);
void inOrderPrint(char *bst, int i);
void postOrderPrint(char *bst, int i);

int main(void) {
    char bst[31];
    for (int i = 0; i < 31; i++) {
        bst[i] = '0';
    }
    scanf("%s", bst + 1);

    preOrderPrint(bst, 1);
    printf("\n");
    inOrderPrint(bst, 1);
    printf("\n");
    postOrderPrint(bst, 1);
    return 0;
}

void preOrderPrint(char *bst, int i) {
    if (i >= 31 || bst[i] == '0' || bst[i] == '\0') return;
    printf("%c", bst[i]);
    preOrderPrint(bst, i * 2);
    preOrderPrint(bst, i * 2 + 1);
}

void inOrderPrint(char *bst, int i) {
    if (i >= 31 || bst[i] == '0' || bst[i] == '\0') return;
    inOrderPrint(bst, i * 2);
    printf("%c", bst[i]);
    inOrderPrint(bst, i * 2 + 1);
}

void postOrderPrint(char *bst, int i) {
    if (i >= 31 || bst[i] == '0' || bst[i] == '\0') return;
    postOrderPrint(bst, i * 2);
    postOrderPrint(bst, i * 2 + 1);
    printf("%c", bst[i]);
}
