#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

typedef struct node {
    char data;
    struct node* left;
    struct node* right;
} Node;

Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* copyTree(Node* root) {
    if (root == NULL) return NULL;

    Node* newNode = createNode(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}

void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

Node* buildFormulaTree(char* expr, int* pos) {
    if (expr[*pos] == '\0' || expr[*pos] == ')') return NULL;

    while (expr[*pos] == ' ') (*pos)++;

    if (isdigit(expr[*pos])) {
        return createNode(expr[(*pos)++]);
    }

    if (expr[*pos] == '(') {
        (*pos)++;

        Node* left = buildFormulaTree(expr, pos);

        while (expr[*pos] == ' ') (*pos)++;

        char op = expr[*pos];
        (*pos)++;

        while (expr[*pos] == ' ') (*pos)++;

        Node* right = buildFormulaTree(expr, pos);

        while (expr[*pos] == ' ') (*pos)++;

        if (expr[*pos] == ')') (*pos)++;

        Node* root = createNode(op);
        root->left = left;
        root->right = right;
        return root;
    }

    return NULL;
}

int evaluate(Node* root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        if (isdigit(root->data))
            return root->data - '0';
        return 0;
    }

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        default: return 0;
    }
}

int isFormulaTree(Node* root) {
    if (root == NULL) return 1;

    // Если лист - должен быть цифрой
    if (root->left == NULL && root->right == NULL) {
        return isdigit(root->data) != 0;
    }

    if (root->left == NULL || root->right == NULL) return 0;

    char op = root->data;
    if (op != '+' && op != '-' && op != '*') return 0;

    return isFormulaTree(root->left) && isFormulaTree(root->right);
}

Node* transformDistributiveLeft(Node* root) {
    if (root == NULL) return NULL;

    root->left = transformDistributiveLeft(root->left);
    root->right = transformDistributiveLeft(root->right);

    if (root != NULL && root->data == '*' &&
        root->left != NULL && (root->left->data == '+' || root->left->data == '-')) {

        Node* f1 = root->left->left;
        Node* f2 = root->left->right;
        Node* f3 = root->right;
        char op = root->left->data;

        Node* leftMult = createNode('*');
        leftMult->left = copyTree(f1);
        leftMult->right = copyTree(f3);

        Node* rightMult = createNode('*');
        rightMult->left = copyTree(f2);
        rightMult->right = copyTree(f3);

        Node* newRoot = createNode(op);
        newRoot->left = leftMult;
        newRoot->right = rightMult;

        free(root->left);
        free(root);

        return newRoot;
    }

    return root;
}

Node* transformDistributiveRight(Node* root) {
    if (root == NULL) return NULL;

    root->left = transformDistributiveRight(root->left);
    root->right = transformDistributiveRight(root->right);

    if (root != NULL && root->data == '*' &&
        root->right != NULL && (root->right->data == '+' || root->right->data == '-')) {

        Node* f1 = root->left;
        Node* f2 = root->right->left;
        Node* f3 = root->right->right;
        char op = root->right->data;

        Node* leftMult = createNode('*');
        leftMult->left = copyTree(f1);
        leftMult->right = copyTree(f2);

        Node* rightMult = createNode('*');
        rightMult->left = copyTree(f1);
        rightMult->right = copyTree(f3);

        Node* newRoot = createNode(op);
        newRoot->left = leftMult;
        newRoot->right = rightMult;

        free(root->right);
        free(root);

        return newRoot;
    }

    return root;
}

Node* transformForward(Node* root) {
    root = transformDistributiveLeft(root);
    root = transformDistributiveRight(root);
    return root;
}

Node* transformFactorLeft(Node* root) {
    if (root == NULL) return NULL;

    root->left = transformFactorLeft(root->left);
    root->right = transformFactorLeft(root->right);

    if (root != NULL && (root->data == '+' || root->data == '-') &&
        root->left != NULL && root->left->data == '*' &&
        root->right != NULL && root->right->data == '*') {

        Node* f3_left = root->left->right;
        Node* f3_right = root->right->right;

        Node* f1 = root->left->left;
        Node* f2 = root->right->left;
        Node* f3 = root->left->right;

        Node* innerOp = createNode(root->data);
        innerOp->left = copyTree(f1);
        innerOp->right = copyTree(f2);

        Node* newRoot = createNode('*');
        newRoot->left = innerOp;
        newRoot->right = copyTree(f3);

        free(root->left);
        free(root->right);
        free(root);

        return newRoot;
    }

    return root;
}

Node* transformFactorRight(Node* root) {
    if (root == NULL) return NULL;

    root->left = transformFactorRight(root->left);
    root->right = transformFactorRight(root->right);

    if (root != NULL && (root->data == '+' || root->data == '-') &&
        root->left != NULL && root->left->data == '*' &&
        root->right != NULL && root->right->data == '*') {

        Node* f1_left = root->left->left;
        Node* f1_right = root->right->left;

        Node* f1 = root->left->left;
        Node* f2 = root->left->right;
        Node* f3 = root->right->right;

        Node* innerOp = createNode(root->data);
        innerOp->left = copyTree(f2);
        innerOp->right = copyTree(f3);

        Node* newRoot = createNode('*');
        newRoot->left = copyTree(f1);
        newRoot->right = innerOp;

        free(root->left);
        free(root->right);
        free(root);

        return newRoot;
    }

    return root;
}

// Полное обратное преобразование из пункта г
Node* transformBackward(Node* root) {
    root = transformFactorLeft(root);
    root = transformFactorRight(root);
    return root;
}

void printPreorder(Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void printInorder(Node* root) {
    if (root != NULL) {
        if (root->left != NULL || root->right != NULL) printf("(");
        printInorder(root->left);
        printf("%c", root->data);
        printInorder(root->right);
        if (root->left != NULL || root->right != NULL) printf(")");
    }
}

void printPostorder(Node* root) {
    if (root != NULL) {
        printPostorder(root->left);
        printPostorder(root->right);
        printf("%c ", root->data);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    printf("========================================\n");
    printf("ЗАДАНИЕ 7: ДЕРЕВО-ФОРМУЛА\n");
    printf("========================================\n\n");

    // ЧАСТЬ А
    printf("ЧАСТЬ А: Построение дерева-формулы и вычисление значения\n");
    printf("--------------------------------------------------------\n");

    char expression[] = "((3+5)*2)";
    int pos = 0;

    printf("Исходная формула: %s\n", expression);

    Node* formulaTree = buildFormulaTree(expression, &pos);

    printf("\nОбходы построенного дерева:\n");
    printf("1) Прямой обход: ");
    printPreorder(formulaTree);
    printf("\n2) Обратный обход: ");
    printInorder(formulaTree);
    printf("\n3) Концевой обход: ");
    printPostorder(formulaTree);
    printf("\n");

    int result = evaluate(formulaTree);
    printf("\nВычисленное значение: %d\n", result);

    printf("\n========================================\n\n");

    printf("ЧАСТЬ Б: Проверка, является ли дерево деревом-формулой\n");
    printf("------------------------------------------------------\n");

    if (isFormulaTree(formulaTree)) {
        printf("Дерево ЯВЛЯЕТСЯ деревом-формулой\n");
    } else {
        printf("Дерево НЕ ЯВЛЯЕТСЯ деревом-формулой\n");
    }

    Node* badTree = createNode('+');
    badTree->left = createNode('a');
    badTree->right = createNode('b');

    printf("\nПроверка другого дерева (с буквами):\n");
    printf("Обход: ");
    printInorder(badTree);
    printf("\n");

    if (isFormulaTree(badTree)) {
        printf("Дерево ЯВЛЯЕТСЯ деревом-формулой\n");
    } else {
        printf("Дерево НЕ ЯВЛЯЕТСЯ деревом-формулой\n");
    }

    freeTree(badTree);

    printf("\n========================================\n\n");

    printf("ЧАСТЬ В: Преобразование с раскрытием скобок (дистрибутивность)\n");
    printf("------------------------------------------------------------\n");

    Node* treeForTransform = createNode('*');

    treeForTransform->left = createNode('+');
    treeForTransform->left->left = createNode('a');
    treeForTransform->left->right = createNode('b');

    treeForTransform->right = createNode('c');

    printf("Исходное дерево: ((a+b)*c)\n");
    printf("1) Прямой обход: ");
    printPreorder(treeForTransform);
    printf("\n2) Обратный обход: ");
    printInorder(treeForTransform);
    printf("\n3) Концевой обход: ");
    printPostorder(treeForTransform);
    printf("\n\n");

    Node* transformed = transformForward(copyTree(treeForTransform));

    printf("Преобразованное дерево (раскрытие скобок):\n");
    printf("1) Прямой обход: ");
    printPreorder(transformed);
    printf("\n2) Обратный обход: ");
    printInorder(transformed);
    printf("\n3) Концевой обход: ");
    printPostorder(transformed);
    printf("\n\n");

    Node* treeForTransform2 = createNode('*');
    treeForTransform2->left = createNode('a');
    treeForTransform2->right = createNode('+');
    treeForTransform2->right->left = createNode('b');
    treeForTransform2->right->right = createNode('c');

    printf("Исходное дерево: (a*(b+c))\n");
    printf("1) Прямой обход: ");
    printPreorder(treeForTransform2);
    printf("\n2) Обратный обход: ");
    printInorder(treeForTransform2);
    printf("\n3) Концевой обход: ");
    printPostorder(treeForTransform2);
    printf("\n\n");

    Node* transformed2 = transformForward(copyTree(treeForTransform2));

    printf("Преобразованное дерево (раскрытие скобок):\n");
    printf("1) Прямой обход: ");
    printPreorder(transformed2);
    printf("\n2) Обратный обход: ");
    printInorder(transformed2);
    printf("\n3) Концевой обход: ");
    printPostorder(transformed2);
    printf("\n");

    printf("\n========================================\n\n");

    printf("ЧАСТЬ Г: Обратное преобразование (вынесение за скобки)\n");
    printf("----------------------------------------------------\n");

    printf("Исходное дерево (результат раскрытия скобок):\n");
    printf("1) Прямой обход: ");
    printPreorder(transformed);
    printf("\n2) Обратный обход: ");
    printInorder(transformed);
    printf("\n3) Концевой обход: ");
    printPostorder(transformed);
    printf("\n\n");

    Node* backTransformed = transformBackward(copyTree(transformed));

    printf("Дерево после обратного преобразования (вынесение за скобки):\n");
    printf("1) Прямой обход: ");
    printPreorder(backTransformed);
    printf("\n2) Обратный обход: ");
    printInorder(backTransformed);
    printf("\n3) Концевой обход: ");
    printPostorder(backTransformed);
    printf("\n");

    freeTree(formulaTree);
    freeTree(treeForTransform);
    freeTree(treeForTransform2);
    freeTree(transformed);
    freeTree(transformed2);
    freeTree(backTransformed);

    printf("\n========================================\n");
    printf("ЗАДАНИЕ 7 ВЫПОЛНЕНО ПОЛНОСТЬЮ\n");
    printf("========================================\n");
    
    return 0;
}