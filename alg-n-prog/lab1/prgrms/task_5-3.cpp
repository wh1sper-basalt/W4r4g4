#include <iostream>
#include <string>
#include <cctype>
#include <windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string text;

    std::cout << "Введите строку: ";
    std::getline(std::cin, text);

    std::string result;

    for (char ch : text) {
        if (!std::ispunct(static_cast<unsigned char>(ch))) {
            result += ch;
        }
    }

    std::cout << "Строка без знаков препинания: " << result << std::endl;

    return 0;
}