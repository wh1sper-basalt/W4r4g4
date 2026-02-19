#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream f1("f1.txt");
    ofstream f2("f2.txt");
    f1 << "Содержимое файла f1\n";
    f1 << "Вторая строка f1\n";
    f1 << "Третья строка f1";
    f2 << "Данные из файла f2\n";
    f2 << "Еще строка f2\n";
    f2 << "Последняя строка f2";
    f1.close();
    f2.close();

    cout << "Исходные файлы созданы." << endl;

    ifstream file1("f1.txt");
    ifstream file2("f2.txt");
    ofstream temp("temp.txt");

    if (!file1 || !file2 || !temp) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    string line;
    while (getline(file2, line)) {
        temp << line << endl;
    }
    file2.close();
    temp.close();

    ofstream new_f2("f2.txt");
    file1.clear();
    file1.seekg(0);

    while (getline(file1, line)) {
        new_f2 << line << endl;
    }
    file1.close();
    new_f2.close();

    ifstream temp_in("temp.txt");
    ofstream new_f1("f1.txt");

    while (getline(temp_in, line)) {
        new_f1 << line << endl;
    }
    temp_in.close();
    new_f1.close();

    remove("temp.txt");
    cout << "Содержимое файлов f1 и f2 успешно обменяно!" << endl;
    cout << "\nСодержимое f1 после обмена:" << endl;
    ifstream show_f1("f1.txt");
    while (getline(show_f1, line)) {
        cout << line << endl;
    }
    show_f1.close();

    cout << "\nСодержимое f2 после обмена:" << endl;
    ifstream show_f2("f2.txt");
    while (getline(show_f2, line)) {
        cout << line << endl;
    }
    show_f2.close();

    return 0;
}