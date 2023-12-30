// 给出已给序列基数排序得每趟收集结果

// 用例：输入：3 35 13 15 20 5 9 14 6 37 59 64
// 输出：20 3 13 14 64 35 15 5 6 37 9 59
// 3 5 6 9 13 14 15 20 35 37 59 64

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct node {
    int val;
    struct node *next;
} Node;

typedef struct linkedList {
    Node *head;
    int size;
} LinkedList;

void RadixSort(int *restrict input, const int size);
void radixSort(int *restrict input, const int size, const int digit);

int powInteger(int base, int exponent);

LinkedList *initLL(void);
void insert(LinkedList *ll, int val);
int delFirst(LinkedList *ll);
bool isEmpty(LinkedList *ll);
void destroyLL(LinkedList *ll);

int main(void) {
    int input[31];
    int size = 0;
    char following = ' ';
    while (following == ' ' && scanf("%d%c", &input[size++], &following) == 2);

    RadixSort(input, size);
    return 0;
}

void RadixSort(int *restrict input, const int size) {
    int max = input[0];
    for (int i = 1; i < size; i++) {
        if (input[i] > max) max = input[i];
    }
    int maxDigit = (int) log10(max) + 1;

    for (int d = 1; d <= maxDigit; d++) {
        radixSort(input, size, d);

        printf("%d", input[0]);
        for (int i = 1; i < size; i++) {
            printf(" %d", input[i]);
        }
        putchar('\n');
    }
}

void radixSort(int *restrict input, const int size, const int digit) {
    LinkedList *aux[10];
    for (int i = 0; i < 10; i++) {
        aux[i] = initLL();
    }
    int index = powInteger(10, digit - 1);

    for (int i = 0; i < size; i++) {
        insert(aux[input[i] / index % 10], input[i]);
    }

    int j = 0;
    for (int i = 0; i < 10; i++) {
        while (!isEmpty(aux[i])) {
            input[j++] = delFirst(aux[i]);
        }
        destroyLL(aux[i]);
    }
}

int powInteger(int base, int exponent) {
    if (exponent == 0) return 1;

    for (int i = 1; i < exponent; i++) {
        base *= base;
    }
    return base;
}

LinkedList *initLL(void) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));

    Node *sentinel = (Node *) malloc(sizeof(Node));
    sentinel->val = 0;
    sentinel->next = NULL;

    ll->size = 0;
    ll->head = sentinel;
    return ll;
}

void insert(LinkedList *ll, int val) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;

    Node *current = ll->head;
    while (current->next != NULL) current = current->next;
    current->next = n;
    ll->size++;
}

int delFirst(LinkedList *ll) {
    Node *temp = ll->head->next;
    ll->head->next = temp->next;
    int val = temp->val;
    free(temp);
    ll->size--;
    return val;
}

bool isEmpty(LinkedList *ll) {
    return ll->size == 0;
}

void destroyLL(LinkedList *ll) {
    while (!isEmpty(ll)) {
        delFirst(ll);
    }
    free(ll->head);
    free(ll);
}
