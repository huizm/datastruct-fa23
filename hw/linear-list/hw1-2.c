// 将元素x插入到给定顺序表的指定位置
// 用例1：输入 1 2 3 4 5
// 位置3
// 输出： 1 2 x 3 4 5
// 用例2：输入 1 2 3 4 5
// 位置1
// 输出：x 1 2 3 4 5
// 用例3：输入 1 2 3 4 5
// 位置6
// 输出：1 2 3 4 5 x
// 用例4：输入
// 位置1；
// 输出：x

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct table {
    int *head;
    int length;
    int size;
} Table;

Table *InitTable(int size);
void ShowTable(Table *t);
void InsertElement(Table *t, int ele, int loc);

int main(void) {
    Table *t = InitTable(6);
    char *first_line = (char *)malloc(20 * sizeof(char));
    size_t fl_len = 19UL;
    int loc;

    getline(&first_line, &fl_len, stdin);
    scanf("%d", &loc);

    // read initial elements into table
    if (strlen(first_line) > 1UL) {
        long ele = strtol(first_line, &first_line, 10);
        while (first_line[0] != '\n') {
            InsertElement(t, (int)ele, t->length);
            ele = strtol(first_line, &first_line, 10);
        }
        InsertElement(t, (int)ele, t->length); // last element
    }

    // insert 'x' to table
    InsertElement(t, 'x', loc-1);

    ShowTable(t);
    return 0;
}

Table *InitTable(const int size) {
    Table *t = (Table *)malloc(sizeof(Table));
    t->length = 0;
    t->size = size;
    t->head = (int *)malloc(size * sizeof(int));
    if (t->head == NULL) {
        exit(-1);
    }
    return t;
}

void ShowTable(Table *t) {
    int buf = t->head[0];
    if (t->length > 0) {
        if (buf == 120)
            printf("x");
        else
            printf("%d", buf);
    }
    for (int i = 1; i < t->length; i++) {
        buf = t->head[i];
        if (buf == 120)
            printf(" x");
        else
            printf(" %d", t->head[i]);
    }
}

void InsertElement(Table *t, int ele, int loc) {
    for (int i = t->length - 1; i >= loc; i--)
        t->head[i+1] = t->head[i];
    t->head[loc] = ele;
    t->length++;
}
