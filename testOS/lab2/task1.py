#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Задание 1. Определение вида треугольника по сторонам и вычисление площади.
"""

import math

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

def calculate_area(a, b, c):
    """Вычисляет площадь треугольника по формуле Герона."""
    p = (a + b + c) / 2
    return math.sqrt(p * (p - a) * (p - b) * (p - c))

def main():
    print("=" * 60)
    print("ЗАДАНИЕ 1. ОПРЕДЕЛЕНИЕ ВИДА ТРЕУГОЛЬНИКА ПО СТОРОНАМ")
    print("=" * 60)
    try:
        a = float(input("Сторона a: "))
        b = float(input("Сторона b: "))
        c = float(input("Сторона c: "))

        ttype = triangle_type_by_sides(a, b, c)
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