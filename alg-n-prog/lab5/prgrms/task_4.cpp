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

int countNodesAtLevel(Node* root, int n) {
    if (!root || n < 0) return 0;
    if (n == 0) return 1;
    
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    int count = 0;
    
    while (!q.empty()) {
        Node* current = q.front().first;
        int level = q.front().second;
        q.pop();
        
        if (level == n) {
            count++;
        } else if (level < n) {
            if (current->left) q.push({current->left, level + 1});
            if (current->right) q.push({current->right, level + 1});
        }
    }
    
    return count;
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
    
    int level;
    cout << "\n\nВведите номер уровня (корень - уровень 0): ";
    cin >> level;
    
    int count = countNodesAtLevel(root, level);
    cout << "Количество вершин на " << level << "-м уровне: " << count << endl;
    
    return 0;
}