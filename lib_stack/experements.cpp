#include <chrono>  // Подключаем библиотеку для работы с временем
#include <iostream>  // Подключаем библиотеку для ввода-вывода
#include <string>  // Подключаем библиотеку для работы со строками
#include <iomanip>  // Подключаем библиотеку для управления форматом вывода
#include "TLStack.h"  // Подключаем реализацию стека на списке
#include "TVStack.h"  // Подключаем реализацию стека на динамическом массиве

// Функция для тестирования времени выполнения операции push
template <typename Stack>
auto push_test(Stack stack, int N, int element_count) {
    std::string s = "1234567891011";  // Строка для добавления в стек
    std::chrono::duration<double> result{};  // Переменная для хранения времени выполнения

    for (int i = 0; i < N; i++) {  // Цикл для многократного тестирования
        auto begin = std::chrono::high_resolution_clock::now();  // Запоминаем время начала
        for (int j = 0; j < element_count; j++) {  // Цикл для добавления элементов в стек
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // Если тип элемента - строка, добавляем строку
            }
            else {
                stack.push(j);  // В противном случае добавляем целое число
            }
        }
        auto end = std::chrono::high_resolution_clock::now();  // Запоминаем время окончания
        result += end - begin;  // Вычисляем время выполнения и добавляем к результату
    }
    return result / N;  // Возвращаем среднее время выполнения
}

// Функция для тестирования времени выполнения операции pop
template <typename Stack>
auto pop_test(Stack stack, int N, int element_count) {
    std::string s = "1234567891011";  // Строка для добавления в стек
    std::chrono::duration<double> result{};  // Переменная для хранения времени выполнения

    for (int i = 0; i < N; i++) {  // Цикл для многократного тестирования
        for (int j = 0; j < element_count; j++) {  // Цикл для добавления элементов в стек
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // Если тип элемента - строка, добавляем строку
            }
            else {
                stack.push(j);  // В противном случае добавляем целое число
            }
        }
        auto begin = std::chrono::high_resolution_clock::now();  // Запоминаем время начала
        for (int j = 0; j < element_count; j++) {  // Цикл для удаления элементов из стека
            stack.pop();  // Удаляем верхний элемент стека
        }
        auto end = std::chrono::high_resolution_clock::now();  // Запоминаем время окончания
        result += end - begin;  // Вычисляем время выполнения и добавляем к результату
    }
    return result / N;  // Возвращаем среднее время выполнения
}

// Функция для тестирования времени выполнения операций push и pop
template <typename Stack>
auto push_and_pop_test(Stack stack, int N, int element_count) {
    std::string s = "1234567891011";  // Строка для добавления в стек
    std::chrono::duration<double> result{};  // Переменная для хранения времени выполнения

    for (int i = 0; i < N; i++) {  // Цикл для многократного тестирования
        for (int j = 0; j < element_count; j++) {  // Цикл для добавления элементов в стек
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // Если тип элемента - строка, добавляем строку
            }
            else {
                stack.push(j);  // В противном случае добавляем целое число
            }
        }
        auto begin = std::chrono::high_resolution_clock::now();  // Запоминаем время начала
        for (int j = 0; j < element_count; j++) {  // Цикл для удаления и добавления элементов из стека
            stack.pop();  // Удаляем верхний элемент стека
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // Если тип элемента - строка, добавляем строку
            }
            else {
                stack.push(j);  // В противном случае добавляем целое число
            }
        }
        auto end = std::chrono::high_resolution_clock::now();  // Запоминаем время окончания
        result += end - begin;  // Вычисляем время выполнения и добавляем к результату
    }
    return result / N;  // Возвращаем среднее время выполнения
}

// Функция для форматированного вывода результатов
void print_line(std::string_view prefix, std::chrono::duration<double> t1, std::chrono::duration<double> t2) {
    std::cout << std::setw(15) << prefix  // Выводим префикс
        << std::setw(15) << t1.count()  // Выводим время выполнения для первого стека
        << std::setw(15) << t2.count()  // Выводим время выполнения для второго стека
        << std::setw(15) << (t2.count() / t1.count())  // Выводим отношение времени выполнения
        << std::endl;  // Завершаем строку вывода
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        TLStack<std::string> list_stack_str;  // Создаем стек на списке для строк
        TVStack<std::string> array_stack_str;  // Создаем стек на динамическом массиве для строк

        TLStack<int> list_stack_int;            // Создаем стек на списке для целых чисел
        TVStack<int> array_stack_int;           // Создаем стек на динамическом массиве для целых чисел

        int element_count;  // Переменная для хранения количества элементов
        std::cout << "Введите количество элементов для добавления в стек: ";
        std::cin >> element_count;  // Запрашиваем у пользователя количество элементов

        // Выводим заголовок для тестирования строк
        std::cout << "String Testing\n";
        std::cout << std::setw(15) << "Prefix"  // Заголовок для префикса
            << std::setw(15) << "Array"  // Заголовок для стека на массиве
            << std::setw(15) << "List"  // Заголовок для стека на списке
            << std::setw(15) << "List/Array"  // Заголовок для отношения времени
            << std::endl;

        // Выводим результаты тестирования операций push, pop и push_and_pop для строк
        print_line("push", push_test(array_stack_str, 50, element_count), push_test(list_stack_str, 50, element_count));
        print_line("pop", pop_test(array_stack_str, 50, element_count), pop_test(list_stack_str, 50, element_count));
        print_line("push_and_pop", push_and_pop_test(array_stack_str, 50, element_count), push_and_pop_test(list_stack_str, 50, element_count));

        // Выводим заголовок для тестирования целых чисел
        std::cout << "Int Testing\n";
        std::cout << std::setw(15) << "Prefix"  // Заголовок для префикса
            << std::setw(15) << "Array"  // Заголовок для стека на массиве
            << std::setw(15) << "List"  // Заголовок для стека на списке
            << std::setw(15) << "List/Array"  // Заголовок для отношения времени
            << std::endl;

        // Выводим результаты тестирования операций push, pop и push_and_pop для целых чисел
        print_line("push", push_test(array_stack_int, 50, element_count), push_test(list_stack_int, 50, element_count));
        print_line("pop", pop_test(array_stack_int, 50, element_count), pop_test(list_stack_int, 50, element_count));
        print_line("push_and_pop", push_and_pop_test(array_stack_int, 50, element_count), push_and_pop_test(list_stack_int, 50, element_count));
    }
    catch (const std::exception& e) {  // Обработка исключений
        std::cerr << "Exception: " << e.what() << std::endl;  // Вывод сообщения об ошибке
    }
    return 0;  // Завершение программы
}
