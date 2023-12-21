// 求出所给出图的最小生成树的最小代价。
// 用例：输入：
/*
0 4 3 -1 7 -1
4 0 1 9 -1 10
3 1 0 8 2 -1
-1 9 8 0 12 5
7 -1 2 12 0 13
-1 10 -1 5 13 0
*/

// 输出：19

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct edge {
    int v, w;
    int weight;
} Edge;

typedef struct minPQ {
    struct edge *arr[16];
    int size;
} MinPQ;

int PrimMST(int adj[6][6]);
void visit(int adj[6][6], MinPQ *pq, bool marked[6], int v);

Edge *initEdge(int v, int w, int weight);
int compareTo(Edge *this, Edge *that);

MinPQ *initMinPQ(void);
void insert(MinPQ *pq, Edge *e);
Edge *delMin(MinPQ *pq);
int size(MinPQ *pq);
bool isEmpty(MinPQ *pq);

int main(void) {
    int adj[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    printf("%d", PrimMST(adj));
    return 0;
}

int PrimMST(int adj[6][6]) {
    bool marked[6] = { false };
    int total = 0;
    MinPQ *pq = initMinPQ();

    visit(adj, pq, marked, 0);
    while (!isEmpty(pq)) {
        Edge *e = delMin(pq);
        int v = e->v, w = e->w, weight = e->weight;
        free(e);
        if (marked[v] && marked[w]) continue;

        total += weight;
        if (marked[v]) visit(adj, pq, marked, w);
        else visit(adj, pq, marked, v);
    }

    free(pq);
    return total;
}

void visit(int adj[6][6], MinPQ *pq, bool marked[6], int v) {
    marked[v] = true;
    for (int i = 0; i < 6; i++) {
        if (adj[v][i] > 0 && !marked[i]) {
            insert(pq, initEdge(v, i, adj[v][i]));
        }
    }
}

Edge *initEdge(int v, int w, int weight) {
    Edge *e = (Edge *) malloc(sizeof(Edge));
    e->v = v;
    e->w = w;
    e->weight = weight;
    return e;
}

int compareTo(Edge *this, Edge *that) {
    return this->weight - that->weight;
}

MinPQ *initMinPQ(void) {
    MinPQ *pq = (MinPQ *) malloc(sizeof(MinPQ));
    pq->size = 0;
    return pq;
}

void insert(MinPQ *pq, Edge *e) {
    // swim
    int index = size(pq) + 1;
    while (index > 1 && compareTo(e, pq->arr[index / 2]) < 0) {
        pq->arr[index] = pq->arr[index / 2];
        index /= 2;
    }
    pq->arr[index] = e;

    pq->size++;
}

Edge *delMin(MinPQ *pq) {
    if (isEmpty(pq)) return NULL;
    
    Edge *min = pq->arr[1];
    Edge *last = pq->arr[size(pq)];
    pq->size--;

    // sink
    int index = 1;
    while (index * 2 <= size(pq)) {
        int j = index * 2;
        if (j + 1 <= size(pq) && compareTo(pq->arr[j], pq->arr[j + 1]) > 0)
            j += 1;
        
        if (compareTo(last, pq->arr[j]) <= 0) break;
        else {
            pq->arr[index] = pq->arr[j];
            index = j;
        }
    }
    pq->arr[index] = last;

    return min;
}

int size(MinPQ *pq) {
    return pq->size;
}

bool isEmpty(MinPQ *pq) {
    return pq->size == 0;
}
