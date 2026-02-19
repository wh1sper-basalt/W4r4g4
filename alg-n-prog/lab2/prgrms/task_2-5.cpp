#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream test("f.txt");
    test << "а б в   большой   тест с   д   слово   е   ё   ж   последнее";
    test.close();

    cout << "Удаляем однобуквенные слова..." << endl;

    ifstream in("f.txt");
    ofstream out("g.txt");

    if (!in || !out) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string word;
        string result;

        while (ss >> word) {
            if (word.length() > 1) {
                if (!result.empty()) result += " ";
                result += word;
            }
        }

        out << result << endl;
    }

    in.close();
    out.close();

    cout << "Однобуквенные слова удалены!" << endl;

    cout << "\nСодержимое f.txt (исходный файл):" << endl;
    ifstream show_f("f.txt");
    getline(show_f, line);
    cout << line << endl;
    show_f.close();

    cout << "\nСодержимое g.txt (после обработки):" << endl;
    ifstream show_g("g.txt");
    getline(show_g, line);
    cout << line << endl;
    show_g.close();

    return 0;
}