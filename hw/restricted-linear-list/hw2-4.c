// 实现主串为“abacababdeadcde”，模式串为任意输入串得，字符串匹配结果，同时输出模式串得Next数组；
// 用例1：输入：abab
// 输出：匹配成功
// -1001；
// 用例2：输入：ababb
// 输出：匹配未成功
// -10012
// 用例3：deadc
// 输出：匹配成功
// -10001
// 用例4：输入：abced
// 输出：匹配未成功
// -10000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define txt "abacababdeadcde"

int *Next(const char * restrict pat);
bool KMPNext(const char * restrict pat, const int * restrict next);

int main(void) {
    char pat[16];
    scanf("%s", pat);
    int *n = Next(pat);
    bool doesMatch = KMPNext(pat, n);

    if (doesMatch)
        printf("匹配成功\n");
    else
        printf("匹配未成功\n");

    size_t n_len = strlen(pat);
    for (unsigned i = 0; i < n_len; i++)
        printf("%d", n[i]);
    return 0;
}

int *Next(const char * restrict pat) {
    size_t len = strlen(pat);
    int *n = (int *)malloc(len * sizeof(int));
    if (n == NULL)
        exit(-1);

    n[0] = -1;
    n[1] = 0;
    for (unsigned i = 1U; i < len - 1; i++) {
        if (pat[i] == pat[n[i]])
            n[i + 1] = n[i] + 1;
        else
            n[i + 1] = 0;
    }

    return n;
}

bool KMPNext(const char * restrict pat, const int * restrict next) {
    size_t n = strlen(txt);
    size_t m = strlen(pat);
    int i, j;

    for (i = 0, j = 0; i < n && j < m; i++, j++) {
        if (pat[j] != txt[i])
            j = next[j];
    }

    if (j == m)
        return true;
    else
        return false;
}
