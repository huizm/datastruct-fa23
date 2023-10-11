// 在已给出的顺序表中删除x元素
// 用例1：输入 1 2 x 4 5
// 输出 1 2 4 5
// 用例2：输入 x 11 22 x 22
// 输出 11 22 22
// 用例3 输入 x y x x x y
// 输出 y y
// 用例4： 输入 1 2 3 4 x
// 输出：1 2 3 4

#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[10];
    scanf("%s", &buf);
    if (strstr(buf, "x") == NULL)
        printf("%s", buf);

    while (scanf("%s", &buf) > 0) {
        if (strstr(buf, "x") == NULL)
            printf(" %s", buf);
    }

    return 0;
}
