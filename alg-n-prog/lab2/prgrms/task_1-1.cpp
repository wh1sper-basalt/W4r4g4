#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream file("my.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return 1;
    }

    string content;
    while (getline(file, content)) {
        cout << content << endl;
    }

    file.close();
    return 0;
}