#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Вставка в дерево поиска
Node* insert(Node* root, char val) {
    if (!root) return new Node(val);

    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    // Если равно - не вставляем (дерево поиска без повторов)
    return root;
}

// Построение дерева поиска из последовательности
Node* buildSearchTree(const string& seq) {
    Node* root = nullptr;
    for (char c : seq) {
        if (c == '.') break;
        root = insert(root, c);
    }
    return root;
}

// Удаление символа из дерева поиска
Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, char key) {
    if (!root) return nullptr;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Узел найден
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

void printPrefix(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    printPrefix(root->left);
    printPrefix(root->right);
}

void printInfix(Node* root) {
    if (!root) return;
    printInfix(root->left);
    cout << root->data << " ";
    printInfix(root->right);
}

void printPostfix(Node* root) {
    if (!root) return;
    printPostfix(root->left);
    printPostfix(root->right);
    cout << root->data << " ";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    cout << "Введите последовательность строчных латинских букв, оканчивающуюся точкой:\n";
    cout << "Пример: moscow\n";
    string seq;
    cin >> seq;

    Node* root = buildSearchTree(seq);

    cout << "\nИсходное дерево поиска:\n";
    cout << "Прямой обход: ";
    printPrefix(root);
    cout << "\nОбратный обход: ";
    printInfix(root);
    cout << "\nКонцевой обход: ";
    printPostfix(root);

    char toDelete;
    cout << "\n\nВведите символ для удаления: ";
    cin >> toDelete;

    root = deleteNode(root, toDelete);

    cout << "\nДерево после удаления " << toDelete << ":\n";
    cout << "Прямой обход: ";
    printPrefix(root);
    cout << "\nОбратный обход: ";
    printInfix(root);
    cout << "\nКонцевой обход: ";
    printPostfix(root);
    cout << endl;

    return 0;
}