// 构建一个大小可变的约瑟夫环，并输出步长为3时的剩余元素
// 用例1：输入 41；
// 输出： 16 31
// 用例2：输入2
// 输出：1 2
// 用例3：输入16
// 输出：1 8
// 用例4：输入100
// 输出：58 91

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} Node;

typedef struct table {
    Node *head;
    int length;
    int size;
} Table;

Table *InitTable(int size);
Node *AppendNode(Table *t, int number);
void RemoveNextNode(Table *t, Node *i);

int main (void) {
    int size;
    scanf("%d", &size);
    Table *t = InitTable(size);

    Node *curr = t->head->next;
    while (t->length > 2) {
        RemoveNextNode(t, curr);
        curr = curr->next->next;
    }
    printf("%d %d", t->head->number, t->head->next->number);
    return 0;
}

Table *InitTable(const int size) {
    Table *t = (Table *)malloc(sizeof(Table));
    if (t == NULL)
        exit(-1);
    t->size = size;

    // initialize nodes
    t->head = AppendNode(t, 1);
    Node *curr = t->head;
    for (int i=1; i<size; i++) {
        curr->next = AppendNode(t, i+1); // also setting `t->tail` and `t->length`
        curr = curr->next;
    }
    return t;
}

/**
 * usage: `curr->next = AppendNode(t, number);`
 *
 * @param t
 * @param number
 * @return pointer to newly appended node
 */
Node *AppendNode(Table *t, const int number) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL)
        exit(-1);
    n->number = number;
    n->next = t->head;
    t->length++;
    return n;
}

void RemoveNextNode(Table *t, Node *i) {
    if (i->next == t->head)
        t->head = t->head->next;
    Node *temp = i->next;
    i->next = i->next->next;
    free(temp);
    t->length--;
}
