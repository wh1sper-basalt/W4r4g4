#include <iostream>
#include <set>
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

bool hasDuplicates(Node* root, set<char>& seen) {
    if (!root) return false;
    
    if (seen.find(root->data) != seen.end()) {
        return true;
    }
    seen.insert(root->data);
    
    return hasDuplicates(root->left, seen) || hasDuplicates(root->right, seen);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    cout << "Введите дерево в списочной записи:\n";
    cout << "Пример 1 (без повторов): (A,(B,(D,0,0),0),(C,(E,0,(G,0,0)),(F,(H,0,0),(I,0,0))))\n";
    cout << "Пример 2 (с повторами): (A,(B,(A,0,0),0),(C,(B,0,(G,0,0)),(F,(H,0,0),(I,0,0))))\n";
    cout << "Ваш ввод: ";
    Node* root = buildTree();
    
    cout << "\nИсходное дерево (прямой обход): ";
    printPreorder(root);
    
    set<char> seen;
    if (hasDuplicates(root, seen)) {
        cout << "\n\nВ дереве есть одинаковые элементы" << endl;
    } else {
        cout << "\n\nВ дереве нет одинаковых элементов" << endl;
    }
    
    return 0;
}