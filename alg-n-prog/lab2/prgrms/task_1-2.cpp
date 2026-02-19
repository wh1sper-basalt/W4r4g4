#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int x, y;
    cout << "Введите число: ";
    cin >> x;

    ofstream s1("S1.txt");
    if (!s1) {
        cout << "Ошибка создания S1.txt" << endl;
        return 1;
    }
    s1 << x;
    s1.close();
    ifstream s1_in("S1.txt");
    ofstream s2("S2.txt");
    if (!s1_in || !s2) {
        cout << "Ошибка открытия файлов" << endl;
        return 1;
    }

    s1_in >> y;
    y += 3;
    s2 << y;
    s1_in.close();
    s2.close();
    cout << "Результат записан в S2.txt" << endl;
    ifstream check("S2.txt");
    int result;
    check >> result;
    cout << "Число из S2.txt: " << result << endl;
    check.close();

    return 0;
}