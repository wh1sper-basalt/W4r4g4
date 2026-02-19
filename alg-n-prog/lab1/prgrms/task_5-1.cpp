#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string text;
    cout << "¬ведите строку: ";
    getline(cin, text);
    string result;

    for (char ch : text) {
        if (ch == '.') {
            result += "...";
        }
        else {
            result += ch;
        }
    }

    cout << "–езультат: " << result << endl;

    return 0;
}