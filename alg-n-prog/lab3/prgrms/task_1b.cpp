#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Node { int data; struct Node* next; };

struct Node* push(struct Node* top, int v) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v; n->next = top; return n;
}

struct Node* pop(struct Node* top, int* v) {
    if (!top) { *v = -1; return top; }
    struct Node* t = top; *v = top->data;
    top = top->next; free(t); return top;
}

int isEmpty(struct Node* top) { return top == NULL; }

void display(struct Node* top) {
    if (!top) { printf("Стек пуст\n"); return; }
    for (struct Node* p = top; p; p = p->next) printf("%d ", p->data);
    printf("\n");
}

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    struct Node* top = NULL;
    int c, v;
    do {
        printf("\n1-push 2-pop 3-show 0-exit: ");
        scanf_s("%d", &c);
        switch (c) {
        case 1: printf("v="); scanf_s("%d", &v); top = push(top, v); display(top); break;
        case 2: top = pop(top, &v); if (v != -1) printf("pop=%d\n", v); display(top); break;
        case 3: display(top); break;
        }
    } while (c);
    return 0;
}