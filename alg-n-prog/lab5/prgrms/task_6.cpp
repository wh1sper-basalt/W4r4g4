#include <iostream>
#include <queue>
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

void printLevelOrder(Node* root) {
    if (!root) return;
    
    queue<Node*> q;
    q.push(root);
    
    cout << "Обход в ширину (по уровням):\n";
    int level = 0;
    
    while (!q.empty()) {
        int levelSize = q.size();
        cout << "Уровень " << level << ": ";
        
        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();
            q.pop();
            
            cout << current->data << " ";
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
        level++;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    cout << "Введите непустое дерево в списочной записи:\n";
    cout << "Пример: (A,(B,(D,0,0),0),(C,(E,0,(G,0,0)),(F,(H,0,0),(I,0,0))))\n";
    cout << "Ваш ввод: ";
    Node* root = buildTree();
    
    cout << "\nИсходное дерево (прямой обход): ";
    printPreorder(root);
    cout << "\n\n";
    
    printLevelOrder(root);
    
    return 0;
}