#include <iostream>
#include <string>
#include <windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string text;

    std::cout << "Введите строку: ";
    std::getline(std::cin, text);

    size_t pos = text.find(';');

    if (pos == std::string::npos) {
        std::cout << "Точка с запятой не найдена в строке." << std::endl;
    }
    else {
        int before = pos;
        int after = text.length() - pos - 1;

        std::cout << "Символов до точки с запятой: " << before << std::endl;
        std::cout << "Символов после точки с запятой: " << after << std::endl;
    }

    return 0;
}