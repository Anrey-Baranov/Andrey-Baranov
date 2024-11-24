#include <chrono>  // ���������� ���������� ��� ������ � ��������
#include <iostream>  // ���������� ���������� ��� �����-������
#include <string>  // ���������� ���������� ��� ������ �� ��������
#include <iomanip>  // ���������� ���������� ��� ���������� �������� ������
#include "TLStack.h"  // ���������� ���������� ����� �� ������
#include "TVStack.h"  // ���������� ���������� ����� �� ������������ �������

// ������� ��� ������������ ������� ���������� �������� push
template <typename Stack>
auto push_test(Stack stack, int N, int element_count) {
    std::string s = "1234567891011";  // ������ ��� ���������� � ����
    std::chrono::duration<double> result{};  // ���������� ��� �������� ������� ����������

    for (int i = 0; i < N; i++) {  // ���� ��� ������������� ������������
        auto begin = std::chrono::high_resolution_clock::now();  // ���������� ����� ������
        for (int j = 0; j < element_count; j++) {  // ���� ��� ���������� ��������� � ����
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // ���� ��� �������� - ������, ��������� ������
            }
            else {
                stack.push(j);  // � ��������� ������ ��������� ����� �����
            }
        }
        auto end = std::chrono::high_resolution_clock::now();  // ���������� ����� ���������
        result += end - begin;  // ��������� ����� ���������� � ��������� � ����������
    }
    return result / N;  // ���������� ������� ����� ����������
}

// ������� ��� ������������ ������� ���������� �������� pop
template <typename Stack>
auto pop_test(Stack stack, int N, int element_count) {
    std::string s = "1234567891011";  // ������ ��� ���������� � ����
    std::chrono::duration<double> result{};  // ���������� ��� �������� ������� ����������

    for (int i = 0; i < N; i++) {  // ���� ��� ������������� ������������
        for (int j = 0; j < element_count; j++) {  // ���� ��� ���������� ��������� � ����
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // ���� ��� �������� - ������, ��������� ������
            }
            else {
                stack.push(j);  // � ��������� ������ ��������� ����� �����
            }
        }
        auto begin = std::chrono::high_resolution_clock::now();  // ���������� ����� ������
        for (int j = 0; j < element_count; j++) {  // ���� ��� �������� ��������� �� �����
            stack.pop();  // ������� ������� ������� �����
        }
        auto end = std::chrono::high_resolution_clock::now();  // ���������� ����� ���������
        result += end - begin;  // ��������� ����� ���������� � ��������� � ����������
    }
    return result / N;  // ���������� ������� ����� ����������
}

// ������� ��� ������������ ������� ���������� �������� push � pop
template <typename Stack>
auto push_and_pop_test(Stack stack, int N, int element_count) {
    std::string s = "1234567891011";  // ������ ��� ���������� � ����
    std::chrono::duration<double> result{};  // ���������� ��� �������� ������� ����������

    for (int i = 0; i < N; i++) {  // ���� ��� ������������� ������������
        for (int j = 0; j < element_count; j++) {  // ���� ��� ���������� ��������� � ����
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // ���� ��� �������� - ������, ��������� ������
            }
            else {
                stack.push(j);  // � ��������� ������ ��������� ����� �����
            }
        }
        auto begin = std::chrono::high_resolution_clock::now();  // ���������� ����� ������
        for (int j = 0; j < element_count; j++) {  // ���� ��� �������� � ���������� ��������� �� �����
            stack.pop();  // ������� ������� ������� �����
            if constexpr (std::is_same_v<typename Stack::value_type, std::string>) {
                stack.push(s);  // ���� ��� �������� - ������, ��������� ������
            }
            else {
                stack.push(j);  // � ��������� ������ ��������� ����� �����
            }
        }
        auto end = std::chrono::high_resolution_clock::now();  // ���������� ����� ���������
        result += end - begin;  // ��������� ����� ���������� � ��������� � ����������
    }
    return result / N;  // ���������� ������� ����� ����������
}

// ������� ��� ���������������� ������ �����������
void print_line(std::string_view prefix, std::chrono::duration<double> t1, std::chrono::duration<double> t2) {
    std::cout << std::setw(15) << prefix  // ������� �������
        << std::setw(15) << t1.count()  // ������� ����� ���������� ��� ������� �����
        << std::setw(15) << t2.count()  // ������� ����� ���������� ��� ������� �����
        << std::setw(15) << (t2.count() / t1.count())  // ������� ��������� ������� ����������
        << std::endl;  // ��������� ������ ������
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        TLStack<std::string> list_stack_str;  // ������� ���� �� ������ ��� �����
        TVStack<std::string> array_stack_str;  // ������� ���� �� ������������ ������� ��� �����

        TLStack<int> list_stack_int;            // ������� ���� �� ������ ��� ����� �����
        TVStack<int> array_stack_int;           // ������� ���� �� ������������ ������� ��� ����� �����

        int element_count;  // ���������� ��� �������� ���������� ���������
        std::cout << "������� ���������� ��������� ��� ���������� � ����: ";
        std::cin >> element_count;  // ����������� � ������������ ���������� ���������

        // ������� ��������� ��� ������������ �����
        std::cout << "String Testing\n";
        std::cout << std::setw(15) << "Prefix"  // ��������� ��� ��������
            << std::setw(15) << "Array"  // ��������� ��� ����� �� �������
            << std::setw(15) << "List"  // ��������� ��� ����� �� ������
            << std::setw(15) << "List/Array"  // ��������� ��� ��������� �������
            << std::endl;

        // ������� ���������� ������������ �������� push, pop � push_and_pop ��� �����
        print_line("push", push_test(array_stack_str, 50, element_count), push_test(list_stack_str, 50, element_count));
        print_line("pop", pop_test(array_stack_str, 50, element_count), pop_test(list_stack_str, 50, element_count));
        print_line("push_and_pop", push_and_pop_test(array_stack_str, 50, element_count), push_and_pop_test(list_stack_str, 50, element_count));

        // ������� ��������� ��� ������������ ����� �����
        std::cout << "Int Testing\n";
        std::cout << std::setw(15) << "Prefix"  // ��������� ��� ��������
            << std::setw(15) << "Array"  // ��������� ��� ����� �� �������
            << std::setw(15) << "List"  // ��������� ��� ����� �� ������
            << std::setw(15) << "List/Array"  // ��������� ��� ��������� �������
            << std::endl;

        // ������� ���������� ������������ �������� push, pop � push_and_pop ��� ����� �����
        print_line("push", push_test(array_stack_int, 50, element_count), push_test(list_stack_int, 50, element_count));
        print_line("pop", pop_test(array_stack_int, 50, element_count), pop_test(list_stack_int, 50, element_count));
        print_line("push_and_pop", push_and_pop_test(array_stack_int, 50, element_count), push_and_pop_test(list_stack_int, 50, element_count));
    }
    catch (const std::exception& e) {  // ��������� ����������
        std::cerr << "Exception: " << e.what() << std::endl;  // ����� ��������� �� ������
    }
    return 0;  // ���������� ���������
}
