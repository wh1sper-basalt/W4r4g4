#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Word {
    char w[100];
    struct Word* next;
};
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    FILE* f = NULL;
    struct Word* stack = NULL, * p = NULL, * temp = NULL;
    char word[100] = { 0 };
    errno_t err = fopen_s(&f, "test.txt", "r");
    if (err != 0 || f == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    while (fscanf_s(f, "%s", word, (unsigned)_countof(word)) == 1) {
        p = (struct Word*)malloc(sizeof(struct Word));
        if (p == NULL) {
            printf("Ошибка выделения памяти!\n");
            while (stack != NULL) {
                temp = stack;
                stack = stack->next;
                free(temp);
            }
            fclose(f);
            return 1;
        }
        strcpy_s(p->w, sizeof(p->w), word);
        p->next = stack;
        stack = p;
        memset(word, 0, sizeof(word));
    }
    fclose(f);

    printf("Слова в обратном порядке:\n");
    while (stack != NULL) {
        stack->w[sizeof(stack->w) - 1] = '\0';
        printf("%s ", stack->w);

        temp = stack;
        stack = stack->next;
        free(temp);
    }
    printf("\n");

    return 0;
}