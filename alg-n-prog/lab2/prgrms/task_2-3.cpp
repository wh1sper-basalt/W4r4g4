#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream f("f.txt");
    ofstream g("g.txt");

    f << "Первая строка из f\n";
    f << "Вторая строка из f\n";
    f << "Третья строка из f";

    g << "Строка 1 из g\n";
    g << "Строка 2 из g\n";
    g << "Строка 3 из g\n";
    g << "Последняя строка из g";

    f.close();
    g.close();

    ifstream file_f("f.txt");
    ifstream file_g("g.txt");
    ofstream file_h("h.txt");

    if (!file_f || !file_g || !file_h) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    string line;

    cout << "Объединяем файлы..." << endl;

    while (getline(file_f, line)) {
        file_h << line << endl;
    }

    file_h << "---\n";

    while (getline(file_g, line)) {
        file_h << line << endl;
    }

    file_f.close();
    file_g.close();
    file_h.close();

    cout << "Файлы успешно объединены в h.txt" << endl;

    cout << "\nСодержимое h.txt:" << endl;
    ifstream show("h.txt");
    while (getline(show, line)) {
        cout << line << endl;
    }
    show.close();

    return 0;
}