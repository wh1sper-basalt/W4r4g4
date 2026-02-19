#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <climits>
#include <windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);
    std::stringstream ss(text);
    std::string word;

    int shortest = INT_MAX;
    int longest = 0;

    while (ss >> word) {
        int length = word.length();

        while (!word.empty() && std::ispunct(static_cast<unsigned char>(word.back()))) {
            word.pop_back();
            length--;
        }
        while (!word.empty() && std::ispunct(static_cast<unsigned char>(word.front()))) {
            word.erase(0, 1);
            length--;
        }
        if (length < shortest && length > 0) {
            shortest = length;
        }
        if (length > longest) {
            longest = length;
        }
    }
    if (shortest == INT_MAX) {
        shortest = 0;
    }
    std::cout << "Длина самого короткого слова: " << shortest << std::endl;
    std::cout << "Длина самого длинного слова: " << longest << std::endl;

    return 0;
}