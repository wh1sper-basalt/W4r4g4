#include <stdio.h>
#include <windows.h>
#define N 100

struct stack { int top, data[N]; };

void push(struct stack* s, int v) { s->data[++s->top] = v; }
int pop(struct stack* s) { return s->data[s->top--]; }

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    struct stack s = { -1 };
    int arr[N], n;

    printf("n="); scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &arr[i]);
        push(&s, arr[i]);
    }

    for (int i = 0; i < n; i++) arr[i] = pop(&s);

    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}