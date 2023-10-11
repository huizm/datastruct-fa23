// 使用大小为100得队列存储杨辉三角形，并输出杨辉三角形得第x行
// 用例1：输入：1
// 输出：1
// 用例2：输入：5
// 输出：1 4 6 4 1
// 用例3：输入：20
// 输出：1 19 171 969 3876 11628 27132 50388 75582 92378 92378 75582 50388 27132 11628 3876 969 171 19 1
// 用例4：输入：100
// 输出：队列已满

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 102

typedef struct node {
    unsigned long long data; // turns out that even `unsigned long long` is not large enough
    struct node *next;
} Node;

typedef struct queue {
    Node *front, *rear;
    int size;
} Queue;

Queue *InitQueue(int size);
void Enqueue(Queue * restrict q, unsigned long long data);
unsigned long long Dequeue(Queue * restrict q);
bool IsFull(const Queue * restrict q);
bool IsEmpty(const Queue * restrict q);
void DestroyQueue(Queue * restrict q);
void ShowAndDestroyQueue(Queue * restrict q);
Queue *NthPascal(Queue * restrict q);

int main(void) {
    int x;
    scanf("%d", &x);

    if (x >= 100) {
        printf("队列已满");
        return 0;
    }

    // init first line
    Queue *q = InitQueue(SIZE);
    Enqueue(q, 1ULL);

    // init xth line
    for (int i = 2; i <= x; i++) {
        q = NthPascal(q);
    }

    ShowAndDestroyQueue(q);
    return 0;
}

Queue *InitQueue(const int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q) {
        perror("failed to allocate memory");
        exit(-1);
    }

    q->size = size;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void Enqueue(Queue * restrict q, const unsigned long long data) {
    if (IsFull(q)) {
        perror("queue is full");
        return;
    }

    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        perror("failed to allocate memory");
        exit(-1);
    }
    n->data = data;
    n->next = NULL;

    if (IsEmpty(q)) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
}

/**
 *
 * @param q
 * @return -1 when queue empty
 */
unsigned long long Dequeue(Queue * restrict q) {
    if (IsEmpty(q)) {
        return -1;
    }

    unsigned long long data = q->front->data;
    Node *temp = q->front;
    q->front = q->front->next;
    free(temp);

    if (q->front == NULL)
        q->rear = NULL;

    return data;
}

bool IsFull(const Queue * restrict q) {
    if (q->rear - q->front + 1 == q->size)
        return true;
    else
        return false;
}

bool IsEmpty(const Queue * restrict q) {
    if (q->front == NULL)
        return true;
    else
        return false;
}

void DestroyQueue(Queue * restrict q) {
    while (!IsEmpty(q))
        (void)Dequeue(q);
    free(q);
}

void ShowAndDestroyQueue(Queue * restrict q) {
    if (IsEmpty(q)) {
        printf("\n");
        return;
    }

    unsigned long long buf;
    buf = Dequeue(q);
    printf("%llu", buf);

    while (!IsEmpty(q)) {
        buf = Dequeue(q);
        printf(" %llu", buf);
    }

    free(q);
}

Queue *NthPascal(Queue * restrict q) {
    Queue *newQueue = InitQueue(SIZE);
    Enqueue(q, 0ULL);

    unsigned long long first = 0ULL;
    unsigned long long second = Dequeue(q);
    while (second != -1ULL) {
        Enqueue(newQueue, first + second);
        first = second;
        second = Dequeue(q);
    }

    DestroyQueue(q);
    return newQueue;
}
