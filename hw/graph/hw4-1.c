// 根据给定的顶点为A,B,C,D,E,F,G，H，I的做组成图的邻接矩阵，给出图的深度优先及广度优先遍历序列。
// 用例1：输入：
/*
0 1 1 1 -1 -1 -1 -1 -1
1 0 1 -1 1 -1 -1 -1 -1
1 1 0 -1 -1 1 -1 -1 -1
1 -1 -1 0 -1 1 -1 -1 -1
-1 1 -1 -1 0 -1 1 -1 -1
-1 -1 1 1 -1 0 -1 1 -1
-1 -1 -1 -1 1 -1 0 -1 1
-1 -1 -1 -1 -1 1 -1 0 1
-1 -1 -1 -1 -1 -1 1 1 0
*/
// 输出：ABCFDHIGE
// ABCDEFGHI

// 用例2：输入：
/*
0 1 1 1 -1 -1 -1 -1 -1
-1 0 1 -1 1 -1 -1 -1 -1
-1 -1 0 -1 -1 1 -1 -1 -1
-1 -1 -1 0 -1 -1 -1 -1 -1
-1 1 -1 -1 0 -1 1 -1 -1
-1 -1 1 1 -1 0 -1 1 -1
-1 -1 -1 -1 -1 -1 0 -1 1
-1 -1 -1 -1 -1 -1 -1 0 1
-1 -1 -1 -1 -1 -1 -1 -1 0
*/
// 输出：ABCFDHIEG
// ABCDEFGHI

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct queue {
    struct node *head;
    struct node *tail;
    int size;
} Queue;

void dfs(const int adj[9][9]);
void dfsRecursive(const int adj[9][9], bool visited[9], int v);
void bfs(const int adj[9][9]);

Queue *initQueue(void);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
bool isEmpty(Queue *q);
int size(Queue *q);
void destroyQueue(Queue *q);

int main(void) {
    int adj[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; ++j) {
            scanf("%d", &adj[i][j]);
        }
    }
    dfs(adj);
    putchar('\n');
    bfs(adj);
    putchar('\n');
    return 0;
}

void dfs(const int adj[9][9]) {
    bool visited[9] = { false };
    dfsRecursive(adj, visited, 0);
}

void dfsRecursive(const int adj[9][9], bool visited[9], int v) {
    if (visited[v] == true) return;

    visited[v] = true;
    putchar('A' + v);

    for (int i = 0; i < 9; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfsRecursive(adj, visited, i);
        }
    }
}

void bfs(const int adj[9][9]) {
    bool visited[9] = { false };
    Queue *q = initQueue();
    enqueue(q, 0);
    visited[0] = true;

    while(!isEmpty(q)) {
        int v = dequeue(q);
        putchar('A' + v);

        for (int i = 0; i < 9; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }

    destroyQueue(q);
}

Queue *initQueue(void) {
    Queue *q = (Queue *) malloc(sizeof(Queue));

    q->size = 0;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

void enqueue(Queue *q, int value) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;

    if (isEmpty(q)) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }

    q->size++;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;

    int value = q->head->value;
    Node *n = q->head;

    if (size(q) == 1) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
    }

    free(n);

    q->size--;
    return value;
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

int size(Queue *q) {
    return q->size;
}

void destroyQueue(Queue *q) {
    while(!isEmpty(q)) dequeue(q);
    free(q);
}
