#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Node { int data; struct Node* next; };

struct Node* push(struct Node* top, int v) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v; n->next = top; return n;
}

void display(struct Node* top) {
    if (!top) return;
    display(top->next);
    printf("%d ", top->data);
}

void freeStack(struct Node* top) {
    if (!top) return;
    freeStack(top->next);
    free(top);
}

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    struct Node* stack = NULL;
    int n, v;

    printf("n="); scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &v);
        stack = push(stack, v);
    }

    printf("Стек: "); display(stack); printf("\n");
    freeStack(stack);
    return 0;
}