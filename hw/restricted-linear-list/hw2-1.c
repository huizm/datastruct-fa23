// 对给出得表达式进行括号匹配，若成功输出“匹配成功”，若不成功则输出“缺少X括号”；
// 用例1：输入：{a+[b*(d+c)]}
// 输出：匹配成功
// 用例2：输入：(a+b)*c]
// 输出：缺少[括号
// 用例3：输入：{[(a+b)*(c+d)]+e
// 输出：缺少}括号
// 用例4：输入：{[(a+b)*(c+d)]+e)
// 输出：缺少(括号缺少}括号

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char data;
    struct node *next; // node beneath this node
} Node;

typedef struct stack {
    Node *top;
    int size;
} Stack;

Stack *InitStack(void);
void DestroyStack(Stack *s);
void Push(Stack *s, char data);
char Pop(Stack *s);
char Peek(Stack *s);
bool IsEmpty(Stack *s);

int main(void) {
    Stack *s = InitStack();
    bool success = true;

    char buf;
    while ((buf = getchar()) != '\n' && buf != EOF) {
        switch (buf) {
            case '{':
            case '[':
            case '(':
                Push(s, buf);
                break;
            case ')':
                if (Peek(s) == '(')
                    Pop(s);
                else {
                    printf("缺少(括号");
                    success = false;
                }
                break;
            case ']':
                if (Peek(s) == '[')
                    Pop(s);
                else {
                    printf("缺少[括号");
                    success = false;
                }
                break;
            case '}':
                if (Peek(s) == '{')
                    Pop(s);
                else {
                    printf("缺少{括号");
                    success = false;
                }
                break;
            default:
                break;
        }
    }

    if (IsEmpty(s) && success) {
        printf("匹配成功");
        return 0;
    }

    while (!IsEmpty(s)) {
        buf = Pop(s);
        switch (buf)
        {
        case '(':
            printf("缺少)括号");
            break;
        case '[':
            printf("缺少]括号");
            break;
        case '{':
            printf("缺少}括号");
            break;
        default:
            break;
        }
    }
    return 0;
}

Stack *InitStack(void) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->size = 0;
    s->top = NULL;
    return s;
}

void DestroyStack(Stack *s) {
    while (!IsEmpty(s))
        Pop(s);
    free(s);
    return;
}

void Push(Stack *s, char data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = s->top;
    s->top = n;
    s->size++;
    return;
}

char Pop(Stack *s) {
    if (IsEmpty(s))
        return '\0';
    
    Node *temp = s->top;
    char data = s->top->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return data;
}

char Peek(Stack *s) {
    if (IsEmpty(s))
        return '\0';
    return s->top->data;
}

bool IsEmpty(Stack *s) {
    if (s->size == 0)
        return true;
    else
        return false;
}
