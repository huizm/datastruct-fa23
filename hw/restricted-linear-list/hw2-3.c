// 实现有三个缓冲轨得火车重排算法，使得无序得火车车厢，重排为小号车厢在前端，大号车厢在后端得有序序列。
// 用例1：输入：4 2 1 3 5
// 输出：5 4 3 2 1
// 用例2：1 2 3 4 5
// 输出：重排失败

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

typedef struct queue {
    int rear;
    int data[SIZE];
} Queue;

Queue *InitQueue(void);
void Enqueue(Queue * restrict q, int data);
int Dequeue(Queue * restrict q);
int PeekFront(const Queue * restrict q);
int PeekRear(const Queue * restrict q);
bool IsEmpty(const Queue * restrict q);
bool IsFull(const Queue * restrict q);

int main(void) {
    int largest = 0;
    int buf;

    // init queues
    Queue *inbound = InitQueue();
    Queue *outbound = InitQueue();
    Queue *tracks[3];
    for (int i = 0; i < 3; i++) {
        tracks[i] = InitQueue();
    }

    // read data into `inbound` queue
    while (scanf("%d", &buf)) {
        Enqueue(inbound, buf);
        if (buf > largest)
            largest = buf;

        if (getchar() == '\n')
            break;
    }

    // iterate through `inbound`
    while (!IsEmpty(inbound)) {
        buf = Dequeue(inbound);
        bool success = false;

        if (buf == largest) {
            for (int i = 0; i < 3; i++) {
                if (IsEmpty(tracks[i])) {
                    Enqueue(outbound, buf);
                    success = true;
                    largest--;
                }
            }
        } else {
            // enqueue `buf` to a buffer track

            for (int i = 0; i < 3; i++) {
                // tracks[i] not empty and rear number greater than buf
                if (!IsEmpty(tracks[i]) && PeekRear(tracks[i]) > buf) {
                    Enqueue(tracks[i], buf);
                    success = true;
                    break;
                }

                // tracks[i] empty
                if (IsEmpty(tracks[i])) {
                    Enqueue(tracks[i], buf);
                    success = true;
                    break;
                }
            }
        }

        if (!success) {
            printf("重排失败");
            return 0;
        }
    }

    // iterate through buffer tracks
    while (!IsEmpty(tracks[0]) || !IsEmpty(tracks[1]) || !IsEmpty(tracks[2])) {
        for (int i = 0; i < 3; i++) {
            if (PeekFront(tracks[i]) == largest) {
                Enqueue(outbound, Dequeue(tracks[i]));
                largest--;
            }
        }
    }

    // print outbound queue
    if (!IsEmpty(outbound)) {
        buf = Dequeue(outbound);
        printf("%d", buf);
    }
    while (!IsEmpty(outbound)) {
        buf = Dequeue(outbound);
        printf(" %d", buf);
    }
    return 0;
}

Queue *InitQueue(void) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->rear = 0; // next of rear element
    return q;
}

void Enqueue(Queue * restrict q, const int data) {
    if (IsFull(q))
        return;

    q->data[q->rear] = data;
    q->rear++;
}

int Dequeue(Queue * restrict q) {
    if (IsEmpty(q))
        return -1;

    int data = q->data[0];
    for (int i = 1; i < q->rear; i++)
        q->data[i - 1] = q->data[i];
    q->rear--;
    return data;
}

int PeekFront(const Queue * restrict q) {
    if (IsEmpty(q))
        return -1;

    int data = q->data[0];
    return data;
}

int PeekRear(const Queue * restrict q) {
    if (IsEmpty(q))
        return -1;

    int data = q->data[q->rear - 1];
    return data;
}

bool IsEmpty(const Queue * restrict q) {
    if (q->rear == 0)
        return true;
    else
        return false;
}

bool IsFull(const Queue * restrict q) {
    if (q->rear >= SIZE)
        return true;
    else
        return false;
}
