#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <windows.h>
using namespace std;

struct Car {
    string brand;
    string number;
    string owner;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ofstream test("f.txt");
    test << "Toyota ABC123 Иванов\n";
    test << "BMW XYZ789 Петров\n";
    test << "Toyota DEF456 Сидоров\n";
    test << "Lada GHI789 Кузнецов\n";
    test << "BMW JKL012 Смирнов\n";
    test << "Toyota MNO345 Васильев\n";
    test << "Lada PQR678 Николаев\n";
    test << "Mercedes STU901 Орлов\n";
    test << "Toyota VWX234 Павлов";
    test.close();

    ifstream in("f.txt");
    if (!in) {
        cout << "Ошибка открытия файла f.txt" << endl;
        return 1;
    }

    vector<Car> cars;
    Car temp;

    while (in >> temp.brand >> temp.number >> temp.owner) {
        cars.push_back(temp);
    }
    in.close();

    cout << "Все автомобили из файла f.txt:" << endl;
    cout << "--------------------------------" << endl;
    for (const auto& car : cars) {
        cout << car.brand << " " << car.number << " " << car.owner << endl;
    }
    cout << "--------------------------------\n" << endl;

    string searchBrand;
    cout << "Введите марку автомобиля для поиска (Toyota, BMW, Lada, Mercedes): ";
    cin >> searchBrand;

    ofstream out("g.txt");
    if (!out) {
        cout << "Ошибка создания файла g.txt" << endl;
        return 1;
    }

    out << "ОТЧЕТ ПО АВТОМОБИЛЯМ\n";
    out << "===================\n\n";

    out << "1. Владельцы и номера автомобилей марки '" << searchBrand << "':\n";
    out << "------------------------------------------------\n";

    bool found = false;
    for (const auto& car : cars) {
        if (car.brand == searchBrand) {
            out << car.owner << " - " << car.number << endl;
            found = true;
        }
    }

    if (!found) {
        out << "Автомобилей данной марки не найдено.\n";
    }

    out << "\n\n2. Количество автомобилей по маркам:\n";
    out << "------------------------------------\n";

    map<string, int> brandCount;
    for (const auto& car : cars) {
        brandCount[car.brand]++;
    }

    for (const auto& entry : brandCount) {
        out << entry.first << ": " << entry.second << " шт.\n";
    }

    out.close();

    cout << "\nРезультаты записаны в файл g.txt:\n";
    cout << "1. Владельцы и номера автомобилей марки '" << searchBrand << "'\n";
    cout << "2. Количество автомобилей каждой марки\n\n";

    cout << "Содержимое файла g.txt:\n";
    cout << "=======================\n";
    ifstream show("g.txt");
    string line;
    while (getline(show, line)) {
        cout << line << endl;
    }
    show.close();

    return 0;
}