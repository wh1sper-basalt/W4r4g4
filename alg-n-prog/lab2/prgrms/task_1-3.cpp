#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream create("test.txt");
    create << "hello world\n";
    create << "programming\n";
    create << "c plus plus\n";
    create.close();

    ifstream in("test.txt");
    if (!in.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string lines[100];
    int count = 0;

    while (getline(in, lines[count]) && count < 100) {
        count++;
    }
    in.close();

    for (int i = 0; i < count; i++) {
        sort(lines[i].begin(), lines[i].end());
    }

    ofstream out("test.txt");
    if (!out.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }
    for (int i = 0; i < count; i++) {
        out << lines[i] << endl;
    }
    out.close();
    cout << "Символы в строках отсортированы по алфавиту!" << endl;
    cout << "Содержимое файла test.txt после сортировки:" << endl;

    ifstream show("test.txt");
    string line;
    while (getline(show, line)) {
        cout << line << endl;
    }
    show.close();

    return 0;
}