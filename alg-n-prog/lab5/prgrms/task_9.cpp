#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Вставка в дерево поиска
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

// Построение дерева поиска из последовательности
Node* buildSearchTree() {
    Node* root = nullptr;
    int val;
    cin >> val;
    while (val != 0) {
        root = insert(root, val);
        cin >> val;
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
    
    cout << "Введите последовательность целых чисел, оканчивающуюся нулем:\n";
    cout << "Пример: 5 3 7 2 4 6 8 0\n";
    
    Node* root = buildSearchTree();
    
    cout << "\nИсходное дерево поиска:\n";
    cout << "Прямой обход: ";
    printPrefix(root);
    cout << "\nОбратный обход: ";
    printInfix(root);
    cout << "\nКонцевой обход: ";
    printPostfix(root);
    
    int newVal;
    cout << "\n\nВведите число для добавления: ";
    cin >> newVal;
    
    root = insert(root, newVal);
    
    cout << "\nДерево после добавления " << newVal << ":\n";
    cout << "Прямой обход: ";
    printPrefix(root);
    cout << "\nОбратный обход: ";
    printInfix(root);
    cout << "\nКонцевой обход: ";
    printPostfix(root);
    cout << endl;
    
    return 0;
}