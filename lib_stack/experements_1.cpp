#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include "Vector.h"
#include "../lib_list/TList.h"

// Функция для генерации случайной строки
std::string generateRandomString() {
    static const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.length() - 1);

    std::string randomString;
    for (int i = 0; i < 10; ++i) {
        randomString += characters[distribution(generator)];
    }
    return randomString;
}

// Тест для Vector
template <typename T>
double push_test_vector(Vector<T>& vec, const T& element) {
    auto start = std::chrono::high_resolution_clock::now();
    vec.push_back(element);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template <typename T>
double pop_test_vector(Vector<T>& vec) {
    auto start = std::chrono::high_resolution_clock::now();
    vec.pop_back();
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Тест для TList
template <typename T>
double push_test_list(TList<T>& list, const T& element) {
    auto start = std::chrono::high_resolution_clock::now();
    list.pushBack(element);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template <typename T>
double pop_test_list(TList<T>& list) {
    auto start = std::chrono::high_resolution_clock::now();
    list.removeLast();
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "Russian");

    int initial_elements;
    std::cout << "Введите количество начальных элементов: ";
    std::cin >> initial_elements;

    // Тесты со строками
    std::cout << "Тесты со строками:\n";
    std::cout << std::setw(20) << "Операция"
        << std::setw(20) << "Vector (мкс)"
        << std::setw(20) << "List (мкс)"
        << std::setw(20) << "List/Vector" << std::endl;

    double total_push_time_vector_str = 0.0;
    double total_push_time_list_str = 0.0;
    double total_pop_time_vector_str = 0.0;
    double total_pop_time_list_str = 0.0;

    for (int i = 0; i < 10; ++i) {
        Vector<std::string> vec_str;
        TList<std::string> list_str;

        // Заполнение начальными элементами
        for (int j = 0; j < initial_elements; ++j) {
            std::string str = generateRandomString();
            vec_str.push_back(str);
            list_str.pushBack(str);
        }

        std::string test_string = generateRandomString();

        // Push тест
        total_push_time_vector_str += push_test_vector(vec_str, test_string);
        total_push_time_list_str += push_test_list(list_str, test_string);

        // Pop тест
        total_pop_time_vector_str += pop_test_vector(vec_str);
        total_pop_time_list_str += pop_test_list(list_str);
    }

    std::cout << std::setw(20) << "Push"
        << std::setw(20) << total_push_time_vector_str / 10
        << std::setw(20) << total_push_time_list_str / 10
        << std::setw(20) << total_push_time_list_str / total_push_time_vector_str << std::endl;

    std::cout << std::setw(20) << "Pop"
        << std::setw(20) << total_pop_time_vector_str / 10
        << std::setw(20) << total_pop_time_list_str / 10
        << std::setw(20) << total_pop_time_list_str / total_pop_time_vector_str << std::endl;

    // Аналогичные тесты с целыми числами
    std::cout << "\nТесты с целыми числами:\n";
    std::cout << std::setw(20) << "Операция"
        << std::setw(20) << "Vector (мкс)"
        << std::setw(20) << "List (мкс)"
        << std::setw(20) << "List/Vector" << std::endl;

    double total_push_time_vector_int = 0.0;
    double total_push_time_list_int = 0.0;
    double total_pop_time_vector_int = 0.0;
    double total_pop_time_list_int = 0.0;

    for (int i = 0; i < 10; ++i) {
        Vector<int> vec_int;
        TList<int> list_int;

        // Заполнение начальными элементами
        for (int j = 0; j < initial_elements; ++j) {
            int num = rand() % 1000;
            vec_int.push_back(num);
            list_int.pushBack(num);
        }

        int test_number = rand() % 1000;

        // Push тест
        total_push_time_vector_int += push_test_vector(vec_int, test_number);
        total_push_time_list_int += push_test_list(list_int, test_number);

        // Pop тест
        total_pop_time_vector_int += pop_test_vector(vec_int);
        total_pop_time_list_int += pop_test_list(list_int);
    }

    std::cout << std::setw(20) << "Push"
        << std::setw(20) << total_push_time_vector_int / 10
        << std::setw(20) << total_push_time_list_int / 10
        << std::setw(20) << total_push_time_list_int / total_push_time_vector_int << std::endl;

    std::cout << std::setw(20) << "Pop"
        << std::setw(20) << total_pop_time_vector_int / 10
        << std::setw(20) << total_pop_time_list_int / 10
        << std::setw(20) << total_pop_time_list_int / total_pop_time_vector_int << std::endl;

    return 0;
}
