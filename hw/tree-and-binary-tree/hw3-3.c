// 对于给定的整数序列，构造平衡二叉查找树，并分层遍历构成的二叉查找树，关键字间以空格分隔。
// 测试用例1：输入：3 10 24 65 32
// 输出：10 3 32 24 65

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node {
    int val;
    int maxDepth;
    struct node *left, *right;
} Node;

typedef struct balancedST {
    Node *root;
    int size;
} BST;

typedef struct qNode {
    Node *val;
    struct qNode *next;
} QNode;

typedef struct linkedListQueue {
    QNode *head, *tail;
    int size;
} Queue;

void put(BST *bst, int val);
Node *putRecursive(Node *root, Node *new);

Node *newNode(int val, int maxDepth, Node *left, Node *right);
BST *initBST(void);
void layerPrint(BST *bst);
int maxDepth(Node *x);
Node *rotateLeft(Node *x);
Node *rotateRight(Node *x);
void destroyBST(BST *bst);
void destroyBSTRecursive(Node *n);

Queue *initQueue(void);
void enqueue(Queue *q, Node *x);
Node *dequeue(Queue *q);
bool isEmpty(Queue *q);
void destroyQueue(Queue *q);

int main(void) {
    int input;
    char following = ' ';
    BST *bst = initBST();

    while (following != '\n' && following != EOF && scanf("%d%c", &input, &following) >= 1) {
        put(bst, input);
    }

    layerPrint(bst);
    destroyBST(bst);
    return 0;

}

void put(BST *bst, int val) {
    Node *n = newNode(val, 1, NULL, NULL);

    if (bst->size == 0) {
        bst->root = n;
    } else {
        bst->root = putRecursive(bst->root, n);
    }

    bst->size++;
}

Node *putRecursive(Node *root, Node *new) {
    if (root == NULL) {
        root = new;
        return new;
    }

    if (root->val < new->val) {
        root->right = putRecursive(root->right, new);
    } else if (root->val > new->val) {
        root->left = putRecursive(root->left, new);
    }
    root->maxDepth = maxDepth(root);

    int diff = maxDepth(root->left) - maxDepth(root->right);
    if (diff >= 2) {
        if (maxDepth(root->left->left) - maxDepth(root->left->right) >= 1) {
            root = rotateRight(root);
        } else if (maxDepth(root->left->left) - maxDepth(root->left->right) <= -1) {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    } else if (diff <= -2) {
        if (maxDepth(root->right->left) - maxDepth(root->right->right) >= 1) {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        } else if (maxDepth(root->right->left) - maxDepth(root->right->right) <= -1) {
            root = rotateLeft(root);
        }
    }

    return root;
}

Node *rotateLeft(Node *x) {
    Node *newRoot = x->right;
    x->right = newRoot->left;
    newRoot->left = x;

    x->maxDepth = maxDepth(x);
    newRoot->maxDepth = maxDepth(newRoot);
    return newRoot;
}

Node *rotateRight(Node *x) {
    Node *newRoot = x->left;
    x->left = newRoot->right;
    newRoot->right = x;

    x->maxDepth = maxDepth(x);
    newRoot->maxDepth = maxDepth(newRoot);
    return newRoot;
}

int maxDepth(Node *x) {
    if (x == NULL) return 0;

    int leftDepth = x->left == NULL ? 0 : x->left->maxDepth;
    int rightDepth = x->right == NULL ? 0 : x->right->maxDepth;
    return (leftDepth >= rightDepth ? leftDepth : rightDepth) + 1;
}

Node *newNode(int val, int maxDepth, Node *left, Node *right) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->val = val;
    n->maxDepth = maxDepth;
    n->left = left;
    n->right = right;
    return n;
}

BST *initBST(void) {
    BST *bst = (BST *) malloc(sizeof(BST));
    bst->root = NULL;
    bst->size = 0;
    return bst;
}

void destroyBST(BST *bst) {
    destroyBSTRecursive(bst->root);
    free(bst);
}

void destroyBSTRecursive(Node *n) {
    if (n == NULL) return;

    if (n->left != NULL) destroyBSTRecursive(n->left);
    if (n->right != NULL) destroyBSTRecursive(n->right);

    free(n);
}

void layerPrint(BST *bst) {
    Queue *q = initQueue();
    printf("%d", bst->root->val);
    if (bst->root->left != NULL) enqueue(q, bst->root->left);
    if (bst->root->right != NULL) enqueue(q, bst->root->right);
    while (q->size > 0) {
        Node *x = dequeue(q);
        printf(" %d", x->val);
        if (x->left != NULL) enqueue(q, x->left);
        if (x->right != NULL) enqueue(q, x->right);
    }

    destroyQueue(q);
}

Queue *initQueue(void) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, Node *x) {
    if (x == NULL) return;

    QNode *n = (QNode *) malloc(sizeof(QNode));
    n->val = x;
    n->next = NULL;

    if (isEmpty(q)) {
        q->head = n;
        q->tail = n;
        q->size++;
        return;
    }

    q->tail->next = n;
    q->tail = n;
    q->size++;
}

Node *dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;

    QNode *x = q->head;
    Node *n = x->val;
    q->head = x->next;
    free(x);

    q->size--;
    return n;
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

void destroyQueue(Queue *q) {
    while (!isEmpty(q)) dequeue(q);
    free(q);
}
