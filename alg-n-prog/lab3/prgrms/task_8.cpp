#include <stdio.h>
#include <windows.h>

#define N 100

struct queue {
    int f;
    int r;
    float d[N];
};
void init(struct queue* q) {
    q->f = -1;
    q->r = -1;
}
void enqueue(struct queue* q, float v) {
    if (q->f == -1) q->f = 0;
    q->r++;
    q->d[q->r] = v;
}
float dequeue(struct queue* q) {
    float v = q->d[q->f];
    q->f++;
    return v;
}
int isempty(struct queue* q) {
    return (q->f > q->r || q->f == -1);
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    struct queue q;
    init(&q);
    FILE* f = NULL;
    fopen_s(&f, "numbers.txt", "r");
    float c, x;
    printf("C = ");
    scanf_s("%f", &c);
    while (fscanf_s(f, "%f", &x) == 1) {
        enqueue(&q, x);
    }
    fclose(f);
    printf("Меньше %.2f: ", c);
    struct queue temp = q;
    while (!isempty(&temp)) {
        x = dequeue(&temp);
        if (x < c) printf("%.2f ", x);
    }
    printf("\nОстальные: ");
    temp = q;
    while (!isempty(&temp)) {
        x = dequeue(&temp);
        if (x >= c) printf("%.2f ", x);
    }
    return 0;
}