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
bool searchPreorder(Node* root, char target) {
    if (!root) return false;
    
    stack<Node*> st;
    st.push(root);
    
    cout << "а) Пройденные узлы (прямой обход): ";
    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        
        cout << current->data << " ";
        if (current->data == target) {
            cout << "\n   Найден элемент: " << target << endl;
            return true;
        }
        
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
    cout << "\n   Элемент не найден" << endl;
    return false;
}

// б) Обратный обход (итеративно)
bool searchInorder(Node* root, char target) {
    if (!root) return false;
    
    stack<Node*> st;
    Node* current = root;
    
    cout << "б) Пройденные узлы (обратный обход): ";
    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }
        
        current = st.top();
        st.pop();
        
        cout << current->data << " ";
        if (current->data == target) {
            cout << "\n   Найден элемент: " << target << endl;
            return true;
        }
        
        current = current->right;
    }
    cout << "\n   Элемент не найден" << endl;
    return false;
}

// в) Концевой обход (итеративно)
bool searchPostorder(Node* root, char target) {
    if (!root) return false;
    
    stack<Node*> st1, st2;
    st1.push(root);
    
    while (!st1.empty()) {
        Node* current = st1.top();
        st1.pop();
        st2.push(current);
        
        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }
    
    cout << "в) Пройденные узлы (концевой обход): ";
    while (!st2.empty()) {
        Node* current = st2.top();
        st2.pop();
        cout << current->data << " ";
        if (current->data == target) {
            cout << "\n   Найден элемент: " << target << endl;
            return true;
        }
    }
    cout << "\n   Элемент не найден" << endl;
    return false;
}

// г) Рекурсивный поиск
bool searchRecursive(Node* root, char target, bool& found) {
    if (!root || found) return false;
    
    cout << root->data << " ";
    if (root->data == target) {
        found = true;
        return true;
    }
    
    if (searchRecursive(root->left, target, found)) return true;
    return searchRecursive(root->right, target, found);
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
    
    char target;
    cout << "\n\nВведите искомый элемент: ";
    cin >> target;
    cout << endl;
    
    searchPreorder(root, target);
    cout << endl;
    searchInorder(root, target);
    cout << endl;
    searchPostorder(root, target);
    cout << endl;
    
    bool found = false;
    cout << "г) Пройденные узлы (рекурсивно): ";
    searchRecursive(root, target, found);
    if (found) {
        cout << "\n   Элемент найден" << endl;
    } else {
        cout << "\n   Элемент не найден" << endl;
    }
    
    return 0;
}