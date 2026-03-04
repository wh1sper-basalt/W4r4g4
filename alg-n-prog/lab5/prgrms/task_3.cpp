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
int findPathLengthPreorder(Node* root, char target) {
    if (!root) return -1;
    
    stack<pair<Node*, int>> st;
    st.push({root, 0});
    
    cout << "а) Пройденные узлы: ";
    while (!st.empty()) {
        Node* current = st.top().first;
        int depth = st.top().second;
        st.pop();
        
        cout << current->data << " ";
        if (current->data == target) {
            cout << "\n   Длина пути до " << target << ": " << depth << endl;
            return depth;
        }
        
        if (current->right) st.push({current->right, depth + 1});
        if (current->left) st.push({current->left, depth + 1});
    }
    
    cout << "\n   Элемент не найден" << endl;
    return -1;
}

// б) Рекурсивный поиск
int findPathLengthRecursive(Node* root, char target, int depth, bool& found) {
    if (!root || found) return -1;
    
    cout << root->data << " ";
    if (root->data == target) {
        found = true;
        return depth;
    }
    
    int left = findPathLengthRecursive(root->left, target, depth + 1, found);
    if (left != -1) return left;
    
    return findPathLengthRecursive(root->right, target, depth + 1, found);
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
    
    char target;
    cout << "\n\nВведите искомый элемент: ";
    cin >> target;
    cout << endl;
    
    findPathLengthPreorder(root, target);
    cout << endl;
    
    bool found = false;
    cout << "б) Пройденные узлы: ";
    int length = findPathLengthRecursive(root, target, 0, found);
    if (found) {
        cout << "\n   Длина пути до " << target << ": " << length << endl;
    } else {
        cout << "\n   Элемент не найден" << endl;
    }
    
    return 0;
}