// 对于给定的字符集合A,B,C,D,E,F,G,H，依次按给定的出现频率构建哈夫曼树，并输出
// 字符串ABCDEFGH的哈夫曼序列或哈夫曼序列代表的字符串。哈夫曼树要求左孩子不大于右孩子。
// 测试示例1：输入：
/*
1 2 4 8 16 32 64 128
ABCDEFGH
 */
// 输出：00000000000001000001000010001001011
// 测试示例2：输入：
/*
5 10 7 9 11 13 14 16
1010011101101010011011100
 */
// 输出：ABCDEFGH

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define R  8
enum charset { A, B, C, D, E, F, G, H };

typedef struct node {
    char val;
    int freq;
    struct node *left, *right;
} Node;

typedef struct minPQ {
    struct node *arr[R + 1];
    int size;
} MinPQ;

void compress(const char input[51], const int freq[R]);
void expand(const char input[51], const int freq[R]);
Node *buildTrie(const int freq[R]);
void buildCode(Node *trie, char codes[R][8]);
void buildCodeRecursive(char codes[R][8], char code[8], Node *trie);

Node *newNode(char val, int freq, Node *left, Node *right);
int compareTo(Node *this, Node *that);
bool isLeaf(Node *n);

MinPQ *newMinPQ(void);
void insert(MinPQ *pq, Node *n);
void swim(MinPQ *pq, int n);
void sink(MinPQ *pq, int n);
Node *delMin(MinPQ *pq);
int size(MinPQ *pq);
bool isEmpty(MinPQ *pq);

int main(void) {
    int freq[R];
    for (int i = A; i <= H; i++) {
        scanf("%d", &freq[i]);
    }
    getchar(); // discard trailing `\n`

    char input[51];
    fgets(input, 50, stdin);
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = '\0';

    if (input[0] >= 'A') compress(input, freq);
    else expand(input, freq);
    return 0;
}

void compress(const char input[51], const int freq[R]) {
    // build trie
    Node *root = buildTrie(freq);

    // build symbol table
    char codes[R][8];
    buildCode(root, codes);

    for (int i = 0; i < strlen(input); i++) {
        printf("%s", codes[input[i] - 'A']);
    }
    fflush(stdout);
}

void expand(const char input[51], const int freq[R]) {
    // build trie
    Node *root = buildTrie(freq);

    Node *current = root;
    int i = 0;
    while (i <= strlen(input)) {
        if (isLeaf(current)) {
            printf("%c", current->val);
            current = root;
        } else {
            switch (input[i]) {
                case '0':
                    current = current->left;
                    break;
                case '1':
                    current = current->right;
                    break;
            }
            i++;
        }
    }
    fflush(stdout);
}

Node *buildTrie(const int freq[R]) {
    MinPQ *pq = newMinPQ();
    for (char c = 'A'; c <= 'H'; c++) {
        Node *n = newNode(c, freq[c - 'A'], NULL, NULL);
        insert(pq, n);
    }

    while (size(pq) > 1) {
        Node *lchild = delMin(pq);
        Node *rchild = delMin(pq);
        Node *new = newNode('\0', lchild->freq + rchild->freq, lchild, rchild);
        insert(pq, new);
    }

    Node *root = delMin(pq);
    free(pq);
    return root;
}

Node *newNode(char val, int freq, Node *left, Node *right) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->val = val;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

int compareTo(Node *this, Node *that) {
    return this->freq - that->freq;
}

bool isLeaf(Node *n) {
    return n->val != '\0';
}

MinPQ *newMinPQ(void) {
    MinPQ *pq = (MinPQ *) malloc(sizeof(MinPQ));
    pq->size = 0;
    return pq;
}

void insert(MinPQ *pq, Node *n) {
    pq->size++;
    pq->arr[size(pq)] = n;
    swim(pq, size(pq));
}

void swim(MinPQ *pq, int n) {
    if (n == 1) return;

    if (compareTo(pq->arr[n], pq->arr[n / 2]) < 0) {
        Node *temp = pq->arr[n];
        pq->arr[n] = pq->arr[n /2];
        pq->arr[n / 2] = temp;
        swim(pq, n / 2);
    }
}

void sink(MinPQ *pq, int n) {
    if (n * 2 > size(pq)) return;

    int smallest = n * 2;
    if (n * 2 + 1 <= size(pq) && compareTo(pq->arr[n * 2], pq->arr[n * 2 + 1]) > 0) smallest += 1;

    if (compareTo(pq->arr[n], pq->arr[smallest]) > 0) {
        Node *temp = pq->arr[n];
        pq->arr[n] = pq->arr[smallest];
        pq->arr[smallest] = temp;
        sink(pq, smallest);
    }
}

Node *delMin(MinPQ *pq) {
    Node *min = pq->arr[1];
    pq->arr[1] = pq->arr[size(pq)];
    pq->arr[size(pq)] = NULL;
    pq->size--;
    sink(pq, 1);
    return min;
}

int size(MinPQ *pq) {
    return pq->size;
}

bool isEmpty(MinPQ *pq) {
    return pq->size == 0;
}

void buildCode(Node *trie, char codes[R][8]) {
    buildCodeRecursive(codes, "", trie);
}

void buildCodeRecursive(char codes[R][8], char code[8], Node *trie) {
    if (isLeaf(trie)) {
        strncpy(codes[trie->val - 'A'], code, 8);
        return;
    }

    char leftCode[8];
    char rightCode[8];
    strncpy(leftCode, code, 8);
    strncpy(rightCode, code, 8);
    strcat(leftCode, "0");
    strcat(rightCode, "1");

    if (trie->left != NULL) buildCodeRecursive(codes, leftCode, trie->left);
    if (trie->right != NULL) buildCodeRecursive(codes, rightCode, trie->right);
}
