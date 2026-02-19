#include <stdio.h>
#include <windows.h>
#define N 100

struct queue { int f, r, d[N]; };

void init(struct queue* q) { q->f = q->r = -1; }
void enq(struct queue* q, int v) {
    if (q->f == -1) q->f = 0;
    q->d[++q->r] = v;
}
int deq(struct queue* q) { return q->d[q->f++]; }
int front(struct queue* q) { return q->d[q->f]; }
int empty(struct queue* q) { return q->f > q->r || q->f == -1; }

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    struct queue q1, q2, res;
    init(&q1); init(&q2); init(&res);
    int n1, n2, v;

    printf("n1="); scanf_s("%d", &n1);
    for (int i = 0; i < n1; i++) { scanf_s("%d", &v); enq(&q1, v); }

    printf("n2="); scanf_s("%d", &n2);
    for (int i = 0; i < n2; i++) { scanf_s("%d", &v); enq(&q2, v); }

    while (!empty(&q1) && !empty(&q2)) {
        if (front(&q1) <= front(&q2)) enq(&res, deq(&q1));
        else enq(&res, deq(&q2));
    }
    while (!empty(&q1)) enq(&res, deq(&q1));
    while (!empty(&q2)) enq(&res, deq(&q2));

    while (!empty(&res)) printf("%d ", deq(&res));
    printf("\n");
    return 0;
}