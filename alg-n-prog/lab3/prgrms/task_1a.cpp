#include <stdio.h>
#include <windows.h>
#define N 100

struct stack { int top, data[N]; };

void init(struct stack* s) { s->top = -1; }
int isEmpty(struct stack* s) { return s->top == -1; }
int isFull(struct stack* s) { return s->top == N - 1; }

void push(struct stack* s, int v) {
    if (!isFull(s)) s->data[++s->top] = v;
    else printf("Стек полон!\n");
}

int pop(struct stack* s) {
    return isEmpty(s) ? -1 : s->data[s->top--];
}

void display(struct stack* s) {
    if (isEmpty(s)) { printf("Стек пуст\n"); return; }
    for (int i = s->top; i >= 0; i--) printf("%d ", s->data[i]);
    printf("\n");
}

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    struct stack s; init(&s);
    int c, v;
    do {
        printf("\n1-push 2-pop 3-show 0-exit: ");
        scanf_s("%d", &c);
        switch (c) {
        case 1: printf("v="); scanf_s("%d", &v); push(&s, v); display(&s); break;
        case 2: v = pop(&s); if (v != -1) printf("pop=%d\n", v); display(&s); break;
        case 3: display(&s); break;
        }
    } while (c);
    return 0;
}