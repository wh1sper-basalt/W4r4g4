#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Задание 3. Определение вида треугольника по углам и вычисление площади.
"""

import math

def triangle_type_by_angles(a, b, c):
    """Определяет вид треугольника по углам (на основе длин сторон)."""
    if a <= 0 or b <= 0 or c <= 0:
        return "Не треугольник"
    if a + b <= c or a + c <= b or b + c <= a:
        return "Не треугольник"

    # Сортируем стороны, чтобы большая была последней
    sides = sorted([a, b, c])
    x, y, z = sides[0], sides[1], sides[2]

    epsilon = 1e-10
    if abs(x**2 + y**2 - z**2) < epsilon:
        return "Прямоугольный"
    elif x**2 + y**2 < z**2:
        return "Тупоугольный"
    else:
        return "Остроугольный"

def calculate_area(a, b, c):
    p = (a + b + c) / 2
    return math.sqrt(p * (p - a) * (p - b) * (p - c))

def main():
    print("=" * 60)
    print("ЗАДАНИЕ 3. ОПРЕДЕЛЕНИЕ ВИДА ТРЕУГОЛЬНИКА ПО УГЛАМ")
    print("=" * 60)
    try:
        a = float(input("Сторона a: "))
        b = float(input("Сторона b: "))
        c = float(input("Сторона c: "))

        ttype = triangle_type_by_angles(a, b, c)
        if ttype == "Не треугольник":
            print("Результат: Не треугольник")
            print("Введенные значения не могут быть сторонами треугольника.")
        else:
            area = calculate_area(a, b, c)
            print(f"Вид треугольника: {ttype}")
            print(f"Площадь треугольника: {area}")
    except ValueError:
        print("Ошибка: введены некорректные данные. Ожидались числа.")

if __name__ == "__main__":
    main()