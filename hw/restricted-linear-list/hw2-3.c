// 实现有三个缓冲轨得火车重排算法，使得无序得火车车厢，重排为小号车厢在前端，大号车厢在后端得有序序列。
// 用例1：输入：4 2 1 3 5
// 输出：5 4 3 2 1
// 用例2：1 2 3 4 5
// 输出：重排失败

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct queue {
    Node *front, *rear;
    int size;
} Queue;

Queue *InitQueue(void);
void DestroyQueue(Queue *q);
void Enqueue(Queue *q, int data);
int Dequeue(Queue *q);
int PeekFront(Queue *q);
int PeekRear(Queue *q);
bool IsEmpty(Queue *q);
int SizeOf(Queue *q);

int main(void) {
    Queue *pullIn = InitQueue();
    Queue *pullOut = InitQueue();
    Queue *buffer[3];
    for (int i=0; i<3; i++) {
        buffer[i] = InitQueue();
    }

    int buf;
    int largest = 0, carCount = 0;
    char adjacent;
    int success = 2;
    do {
        success = scanf("%d%c", &buf, &adjacent);
        Enqueue(pullIn, buf);
        carCount++;
        if (buf > largest)
            largest = buf;
    } while (success > 1 && adjacent != '\n' && adjacent != EOF);

    while (!IsEmpty(pullIn)) {
        buf = Dequeue(pullIn);
        if (buf == largest) {
            if (IsEmpty(buffer[0]) || IsEmpty(buffer[1]) || IsEmpty(buffer[2])) {
                Enqueue(pullOut, buf);
                largest--;
            } else {
                printf("重排失败");
                return 0;
            }
        } else {
            bool enqueued = false;
            for (int i=0; i<3; i++) {
                if (!IsEmpty(buffer[i]) && PeekRear(buffer[i]) > buf) {
                    Enqueue(buffer[i], buf);
                    enqueued = true;
                    break;
                }
            }

            if (enqueued) continue;
            for (int i=0; i<3; i++) {
                if (IsEmpty(buffer[i])) {
                    Enqueue(buffer[i], buf);
                    enqueued = true;
                    break;
                }
            }

            if (enqueued) continue;
            else {
                printf("重排失败");
                return 0;
            }
        }
    }

    while (SizeOf(pullOut) < carCount) {
        for (int i=0; i<3; i++) {
            if (!IsEmpty(buffer[i]) && PeekFront(buffer[i]) == largest) {
                Enqueue(pullOut, Dequeue(buffer[i]));
                largest--;
            }
        }
    }

    printf("%d", Dequeue(pullOut));
    while (!IsEmpty(pullOut))
        printf(" %d", Dequeue(pullOut));

    DestroyQueue(pullIn);
    DestroyQueue(pullOut);
    for (int i=0; i<3; i++) {
        DestroyQueue(buffer[i]);
    }
    return 0;
}

Queue *InitQueue(void) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void DestroyQueue(Queue *q) {
    while (!IsEmpty(q))
        Dequeue(q);
    free(q);
    return;
}

void Enqueue(Queue *q, int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;

    if (IsEmpty(q)) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }

    q->size++;
    return;
}

int Dequeue(Queue *q) {
    if (IsEmpty(q))
        return 0;

    int data = q->front->data;
    Node *temp = q->front;
    q->front = q->front->next;
    free(temp);

    q->size--;
    if (q->size == 0) {
        q->rear = NULL;
    }
    return data;
}

int PeekFront(Queue *q) {
    if (IsEmpty(q))
        return 0;
    return q->front->data;
}

int PeekRear(Queue *q) {
    if (IsEmpty(q))
        return 0;
    return q->rear->data;
}

bool IsEmpty(Queue *q) {
    return q->size == 0 ? true : false;
}

int SizeOf(Queue *q) {
    return q->size;
}
