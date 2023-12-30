// 求给定图的中顶点A（第一个顶点，即邻接矩阵中第一行第一列）到其他顶点的最短路径。

// 用例： 输入：
/*
0 10 -1 25 80
-1 0 40 -1 -1
-1 -1 0 -1 10
-1 -1 20 0 55
-1 -1 -1 -1 0
*/

// 输出：0 10 45 25 55

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static int vCount = 0;

typedef struct node {
    int index;
    int val;
} Node;

typedef struct minPQ {
    Node *heap[32];
    int size;
} MinPQ;

int *DijkstraSP(const int G[vCount][vCount]);
void relax(const int G[vCount][vCount], int distTo[vCount], MinPQ *restrict pq, const int index);

MinPQ *initPQ(void);
void insert(MinPQ *restrict pq, const int index, const int val);
int delMin(MinPQ *restrict pq);
void swim(MinPQ *restrict pq, int i);
void sink(MinPQ *restrict pq, int i);
bool isEmpty(const MinPQ *restrict pq);
void destroyPQ(MinPQ *restrict pq);

int main(void) {
    int firstLine[10];
    char following = ' ';
    while (following == ' ' && scanf("%d%c", &firstLine[vCount++], &following) == 2) { if (following == '\n') break; }

    int G[vCount][vCount];
    for (int j = 0; j < vCount; j++) {
        G[0][j] = firstLine[j];
    }
    for (int i = 1; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    int *distTo = DijkstraSP(G);

    printf("%d", distTo[0]);
    for (int i = 1; i < vCount; i++) {
        printf(" %d", distTo[i]);
    }
    putchar('\n');

    free(distTo);
    return 0;
}

int *DijkstraSP(const int G[vCount][vCount]) {
    int *distTo = (int *) malloc(vCount * sizeof(int));
    distTo[0] = 0;
    for (int i = 1; i < vCount; i++) {
        distTo[i] = INT_MAX;
    }

    MinPQ *pq = initPQ();
    insert(pq, 0, 0);
    while (!isEmpty(pq)) {
        relax(G, distTo, pq, delMin(pq));
    }

    destroyPQ(pq);
    return distTo;
}

void relax(const int G[vCount][vCount], int distTo[vCount], MinPQ *restrict pq, const int index) {
    for (int j = 0; j < vCount; j++) {
        if (G[index][j] > 0 && distTo[j] > distTo[index] + G[index][j]) {
            distTo[j] = distTo[index] + G[index][j];
            insert(pq, j, distTo[j]);
        }
    }
}

MinPQ *initPQ(void) {
    MinPQ *pq = (MinPQ *) malloc(sizeof(MinPQ));
    pq->size = 0;
    return pq;
}

void insert(MinPQ *restrict pq, const int index, const int val) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->index = index;
    n->val = val;

    pq->heap[++pq->size] = n;
    swim(pq, pq->size);
}

int delMin(MinPQ *restrict pq) {
    if (isEmpty(pq)) exit(EXIT_FAILURE);

    int min = pq->heap[1]->index;
    pq->heap[1] = pq->heap[pq->size--];
    sink(pq, 1);

    return min;
}

void swim(MinPQ *restrict pq, int i) {
    if (i > pq->size) exit(EXIT_FAILURE);

    while (i >= 2 && pq->heap[i]->val <= pq->heap[i / 2]->val) {
        Node *temp = pq->heap[i];
        pq->heap[i] = pq->heap[i / 2];
        pq->heap[i / 2] = temp;

        i /= 2;
    }
}

void sink(MinPQ *restrict pq, int i) {
    while (i * 2 <= pq->size) {
        int smallestChild = i * 2;
        if (i * 2 + 1 <= pq->size && pq->heap[i * 2 + 1]->val < pq->heap[i * 2]->val) smallestChild += 1;

        if (pq->heap[smallestChild]->val > pq->heap[i]->val) break;
        Node *temp = pq->heap[i];
        pq->heap[i] = pq->heap[smallestChild];
        pq->heap[smallestChild] = temp;

        i = smallestChild;
    }
}

bool isEmpty(const MinPQ *restrict pq) {
    return pq->size == 0;
}

void destroyPQ(MinPQ *restrict pq) {
    for (int i = 1; i <= pq->size; i++) free(pq->heap[i]);
    free(pq);
}
