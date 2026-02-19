#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream test("f.txt");
    test << "Строка 1\n";
    test << "Строка 2\n";
    test << "Строка 3\n";
    test << "Строка 4\n";
    test << "Строка 5";
    test.close();

    ifstream in("f.txt");
    if (!in) {
        cout << "Ошибка открытия файла f.txt" << endl;
        return 1;
    }

    vector<string> lines;
    string line;

    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    ofstream out("g.txt");
    if (!out) {
        cout << "Ошибка создания файла g.txt" << endl;
        return 1;
    }

    for (int i = lines.size() - 1; i >= 0; i--) {
        out << lines[i] << endl;
    }
    out.close();

    cout << "Файл успешно записан в обратном порядке!" << endl;

    cout << "\nСодержимое g.txt (обратный порядок):" << endl;
    ifstream show("g.txt");
    while (getline(show, line)) {
        cout << line << endl;
    }
    show.close();

    return 0;
}