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
int empty(struct queue* q) { return q->f > q->r || q->f == -1; }

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    struct queue q; init(&q);
    int n, v;

    printf("n="); scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &v);
        enq(&q, v);
    }

    printf("Извлечено: ");
    while (!empty(&q)) {
        v = deq(&q);
        printf("%d ", v);
        if (v % 2 == 0) break;
    }
    printf("\n");
    return 0;
}