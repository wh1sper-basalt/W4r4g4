#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream test("f.txt");
    test << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";
    test.close();

    cout << "Фильтруем четные числа..." << endl;

    ifstream in("f.txt");
    ofstream out("g.txt");

    if (!in || !out) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    int num;
    bool first = true;

    while (in >> num) {
        if (num % 2 == 0) {
            if (!first) out << " ";
            out << num;
            first = false;
        }
    }

    in.close();
    out.close();

    cout << "Четные числа записаны в g.txt" << endl;

    cout << "\nСодержимое f.txt (исходный файл):" << endl;
    ifstream show_f("f.txt");
    char buffer_f[100];
    show_f.getline(buffer_f, 100);
    cout << buffer_f << endl;
    show_f.close();

    cout << "\nСодержимое g.txt (четные числа):" << endl;
    ifstream show_g("g.txt");
    char buffer_g[100];
    show_g.getline(buffer_g, 100);
    cout << buffer_g << endl;
    show_g.close();

    return 0;
}