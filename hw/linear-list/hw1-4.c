// 将已有商品链表和新进商品链表，进行归类整合
//
//        用例：输入： 已有：A 3, C 5, D 6;
// 新进：A 2, B 3, C 5, E 7, F 8;
//
// 输出：A 5, B 3, C 10, D 6, E 7, F 8;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char commodity;
    int quantity;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    int len;
} List;

void createNodeAndInsert(List *l, char commod, int quant, Node *prev);
Node *InitNode(char c, int q);
List *InitList(void);
void InsertNode(List *l, Node *prev, Node *n);
void ShowList(List *l);

int main(void) {
    List *l = InitList();
    char commod, after;
    int quant;

    // read inherent data
    while (scanf("%c %d%c", &commod, &quant, &after)) {
        createNodeAndInsert(l, commod, quant, NULL);

        getchar(); // discard trailing space
        if (after == ';')
            break;
    }

    // read new data
    Node *curr = l->head;
    // if list empty, append first new node
    if (curr == NULL) {
        scanf("%c %d%c", &commod, &quant, &after);
        createNodeAndInsert(l, commod, quant, NULL);
    }

    while (scanf("%c %d%c", &commod, &quant, &after)) {
        // find matching or previous node, do nothing if `curr` after or equals to `newNode`
        while (curr->commodity < commod && curr->next != NULL && curr->next->commodity <= commod)
            curr = curr->next;

        if (curr->commodity < commod) {
            createNodeAndInsert(l, commod, quant, curr);
        } else if (curr->commodity == commod) {
            curr->quantity += quant;
        } else if (curr->next == NULL){
            // reached the end of list but didn't match
            createNodeAndInsert(l, commod, quant, NULL);
        } else {
            perror("undefined behavior");
            exit(-1);
        }

        getchar(); // discard trailing space
        if (after == ';')
            break;
    }

    ShowList(l);
    return 0;
}

/**
 *
 * @param l
 * @param commod
 * @param quant
 * @param prev set to `NULL` to append
 */
void createNodeAndInsert(List *l, char commod, int quant, Node *prev) {
    Node *newNode = InitNode(commod, quant);
    InsertNode(l, prev, newNode);
}

Node *InitNode(char c, int q) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->commodity = c;
    newNode->quantity = q;
    newNode->next = NULL;
    return newNode;
}

List *InitList(void) {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->len = 0;
    return l;
}

/**
 *
 * @param l
 * @param prev if `NULL`, append to the end of list
 * @param n
 */
void InsertNode(List *l, Node *prev, Node *n) {
    // if list empty
    if (l->len == 0) {
        if (prev != NULL) {
            perror("invalid pointer access");
            exit(-1);
        }
        l->head = n;
        l->len++;
        return;
    }

    if (prev == NULL) {
        // find last node
        Node *scan = l->head;
        while (scan->next != NULL)
            scan = scan->next;

        scan->next = n;
    } else {
        n->next = prev->next;
        prev->next = n;
    }

    l->len++;
    return;
}

void ShowList(List *l) {
    Node *scan = l->head;
    while (true) {
        printf("%c %d", scan->commodity, scan->quantity);
        if (scan->next != NULL) {
            printf(", ");
            scan = scan->next;
        } else {
            printf(";");
            break;
        }
    }
}
