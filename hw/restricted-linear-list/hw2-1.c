// 对给出得表达式进行括号匹配，若成功输出“匹配成功”，若不成功则输出“缺少X括号”；
// 用例1：输入：{a+[b*(d+c)]}
// 输出：匹配成功
//        用例2：输入：(a+b)*c]
// 输出：缺少[括号
//        用例3：输入：{[(a+b)*(c+d)]+e
//        输出：缺少}括号
//        用例4：输入：{[(a+b)*(c+d)]+e)
// 输出：缺少(括号缺少}括号

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
    unsigned top;
    unsigned size;
    char *bottom;
} Stack;

Stack *InitStack(unsigned size);
void Push(Stack *s, char data);
char Pop(Stack *s); // if empty return '\0'
char Peek(Stack *s); // if empty return '\0'
bool IsEmpty(Stack *s);
bool IsFull(Stack *s);


int main(void) {
    Stack *s = InitStack(6U);
    char buf;
    bool success_flag = true;

    while ((buf = (char)getchar()) != '\n') {
        switch (buf) {
            case '(':
            case '[':
            case '{':
                Push(s, buf);
                break;
            case ')':
                if (Peek(s) == '(')
                    Pop(s);
                else {
                    printf("缺少(括号");
                    success_flag = false;
                }
                break;
            case ']':
                if (Peek(s) == '[')
                    Pop(s);
                else {
                    printf("缺少[括号");
                    success_flag = false;
                }
                break;
            case '}':
                if (Peek(s) == '{')
                    Pop(s);
                else {
                    printf("缺少{括号");
                    success_flag = false;
                }
                break;
            default:
                break;
        }
    }

    while (!IsEmpty(s)) {
        buf = Pop(s);
        switch (buf) {
            case '(':
                printf("缺少)括号");
                success_flag = false;
                break;
            case '[':
                printf("缺少]括号");
                success_flag = false;
                break;
            case '{':
                printf("缺少}括号");
                success_flag = false;
                break;
            default:
                break;
        }
    }

    if (success_flag)
        printf("匹配成功");

    return 0;
}

Stack *InitStack(unsigned size) {
    char *arr = (char *)malloc(size * sizeof(char));
    if (arr == NULL) {
        perror("failed to allocate memory");
        exit(-1);
    }
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL) {
        perror("failed to allocate memory");
        exit(-1);
    }

    s->top = 0U;
    s->size = size;
    s->bottom = arr;
    return s;
}

void Push(Stack *s, char data) {
    if (IsFull(s))
        perror("index out of range");

    *(s->bottom + s->top) = data;
    s->top++;
}

char Pop(Stack *s) {
    if (IsEmpty(s))
        return '\0';

    char data = *(s->bottom + s->top - 1);
    s->top--;
    return data;
}

char Peek(Stack *s) {
    if (IsEmpty(s))
        return '\0';

    char data = *(s->bottom + s->top - 1);
    return data;
}

bool IsEmpty(Stack *s) {
    if (s->top == 0)
        return true;
    else
        return false;
}

bool IsFull(Stack *s) {
    if (s->top == s->size - 1)
        return true;
    else
        return false;
}
