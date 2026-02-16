#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Улучшенная версия программы для определения вида треугольника.
Объединяет задания 1 и 3 с исправлениями по результатам тестирования (task4.md).
"""

import math

def get_float(prompt):
    """
    Запрашивает у пользователя число, повторяет ввод до получения корректного значения.
    Проверяет, что ввод не пустой.
    """
    while True:
        s = input(prompt).strip()
        if s == '':
            print("Ошибка: ввод не может быть пустым. Попробуйте снова.")
            continue
        try:
            return float(s)
        except ValueError:
            print("Ошибка: необходимо ввести число. Попробуйте снова.")

def triangle_type_by_sides(a, b, c):
    """Определяет вид треугольника по длинам сторон."""
    if a <= 0 or b <= 0 or c <= 0:
        return "Не треугольник"
    if a + b <= c or a + c <= b or b + c <= a:
        return "Не треугольник"
    if a == b == c:
        return "Равносторонний"
    if a == b or a == c or b == c:
        return "Равнобедренный"
    return "Разносторонний"

def triangle_type_by_angles(a, b, c):
    """Определяет вид треугольника по углам (на основе длин сторон)."""
    if a <= 0 or b <= 0 or c <= 0:
        return "Не треугольник"
    if a + b <= c or a + c <= b or b + c <= a:
        return "Не треугольник"

    sides = sorted([a, b, c])
    x, y, z = sides[0], sides[1], sides[2]

    # Используем math.isclose для надёжного сравнения (улучшение DEF-05, DEF-06)
    if math.isclose(x**2 + y**2, z**2, rel_tol=1e-9, abs_tol=1e-9):
        return "Прямоугольный"
    elif x**2 + y**2 < z**2:
        return "Тупоугольный"
    else:
        return "Остроугольный"

def calculate_area(a, b, c):
    """Вычисляет площадь треугольника по формуле Герона."""
    p = (a + b + c) / 2
    return math.sqrt(p * (p - a) * (p - b) * (p - c))

def format_area(area):
    """Возвращает отформатированную строку с площадью."""
    if area < 0.01:
        return f"{area:.2e}"
    else:
        return f"{area:.2f}"

def main():
    print("=" * 70)
    print("        ПРОГРАММА ОПРЕДЕЛЕНИЯ ВИДА ТРЕУГОЛЬНИКА (УЛУЧШЕННАЯ ВЕРСИЯ)")
    print("=" * 70)
    print("\nВыберите режим работы:")
    print("  1 – по сторонам (разносторонний / равнобедренный / равносторонний)")
    print("  2 – по углам    (остроугольный / прямоугольный / тупоугольный)")
    print("  0 – выход")

    while True:
        print("\n" + "-" * 40)
        choice = input("Ваш выбор (1/2/0): ").strip()
        if choice == '0':
            print("Программа завершена. До свидания!")
            break
        if choice not in ('1', '2'):
            print("Неверный выбор. Попробуйте снова.")
            continue

        print("\nВведите длины сторон треугольника (положительные числа):")
        a = get_float("Сторона a: ")
        b = get_float("Сторона b: ")
        c = get_float("Сторона c: ")

        # Проверка на слишком большие значения (дополнительная защита)
        MAX_SIDE = 1e150
        if a > MAX_SIDE or b > MAX_SIDE or c > MAX_SIDE:
            print("Ошибка: стороны слишком велики (переполнение).")
            continue

        if choice == '1':
            ttype = triangle_type_by_sides(a, b, c)
        else:
            ttype = triangle_type_by_angles(a, b, c)

        if ttype == "Не треугольник":
            print("\nТакой треугольник не существует.")
            # Детализация причины
            if a <= 0 or b <= 0 or c <= 0:
                print("   Причина: одна или несколько сторон ≤ 0.")
            else:
                print("   Причина: нарушено неравенство треугольника.")
        else:
            area = calculate_area(a, b, c)
            area_str = format_area(area)
            print(f"\nВид треугольника: {ttype}")
            print(f"   Площадь: {area_str}")

        # Предложение повторить
        cont = input("\nХотите выполнить ещё одно вычисление? (y/n): ").lower()
        if cont != 'y':
            print("Программа завершена. До свидания!")
            break

if __name__ == "__main__":
    main()