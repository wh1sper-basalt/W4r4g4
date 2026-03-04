#include <iostream>
#include <stack>
#include <windows.h>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

Node* buildTree() {
    char sym;
    cin >> sym;

    switch(sym) {
        case '(': {
            cin >> sym;
            Node* node = new Node(sym);
            node->left = buildTree();
            node->right = buildTree();
            cin >> sym;
            return node;
        }
        case '0':
            return nullptr;
        case ',':
            return buildTree();
        default:
            return nullptr;
    }
}

void printPreorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

// а) Прямой обход (итеративно)
void countLeavesPreorder(Node* root) {
    if (!root) return;

    stack<Node*> st;
    st.push(root);
    int count = 0;

    cout << "а) Листья при прямом обходе: ";
    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        if (!current->left && !current->right) {
            cout << current->data << " ";
            count++;
        }

        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
    cout << "\n   Количество листьев: " << count << endl;
}

// б) Обратный обход (итеративно)
void countLeavesInorder(Node* root) {
    if (!root) return;

    stack<Node*> st;
    Node* current = root;
    int count = 0;

    cout << "б) Листья при обратном обходе: ";
    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        if (!current->left && !current->right) {
            cout << current->data << " ";
            count++;
        }

        current = current->right;
    }
    cout << "\n   Количество листьев: " << count << endl;
}

// в) Концевой обход (итеративно)
void countLeavesPostorder(Node* root) {
    if (!root) return;

    stack<Node*> st1, st2;
    st1.push(root);
    int count = 0;

    while (!st1.empty()) {
        Node* current = st1.top();
        st1.pop();
        st2.push(current);

        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }

    cout << "в) Листья при концевом обходе: ";
    while (!st2.empty()) {
        Node* current = st2.top();
        st2.pop();
        if (!current->left && !current->right) {
            cout << current->data << " ";
            count++;
        }
    }
    cout << "\n   Количество листьев: " << count << endl;
}

// г) Рекурсивный подсчет
void printLeavesRecursive(Node* root, int& count) {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->data << " ";
        count++;
        return;
    }
    printLeavesRecursive(root->left, count);
    printLeavesRecursive(root->right, count);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    cout << "Введите дерево в списочной записи:\n";
    cout << "Пример: (A,(B,(D,0,0),0),(C,(E,0,(G,0,0)),(F,(H,0,0),(I,0,0))))\n";
    cout << "Ваш ввод: ";
    Node* root = buildTree();

    cout << "\nИсходное дерево (прямой обход): ";
    printPreorder(root);
    cout << "\n\n";

    if (!root) {
        cout << "Дерево пусто\n";
        return 0;
    }

    countLeavesPreorder(root);
    cout << endl;
    countLeavesInorder(root);
    cout << endl;
    countLeavesPostorder(root);
    cout << endl;

    int count = 0;
    cout << "г) Листья (рекурсивно): ";
    printLeavesRecursive(root, count);
    cout << "\n   Количество листьев: " << count << endl;

    return 0;
}