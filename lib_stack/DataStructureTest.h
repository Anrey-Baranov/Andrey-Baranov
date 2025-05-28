#ifndef DATA_STRUCTURE_TEST_H
#define DATA_STRUCTURE_TEST_H

#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <random>

template <typename Container>
class DataStructureTest {
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    DataStructureTest() : gen(rd()) {}

    // Тест на добавление одного элемента
    auto push_test(Container& container, int initial_size, int test_iterations) {
        // Заполнение начального контейнера
        for (int i = 0; i < initial_size; ++i) {
            if constexpr (std::is_same_v<typename Container::value_type, std::string>) {
                container.push_back("initial");
            }
            else {
                container.push_back(gen() % 1000);
            }
        }

        std::chrono::duration<double, std::milli> total_time{};

        for (int i = 0; i < test_iterations; ++i) {
            auto begin = std::chrono::high_resolution_clock::now();

            if constexpr (std::is_same_v<typename Container::value_type, std::string>) {
                container.push_back("test");
            }
            else {
                container.push_back(gen() % 1000);
            }

            auto end = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

            // Удаляем последний добавленный элемент
            container.pop_back();
        }

        return total_time / test_iterations;
    }

    // Тест на удаление последнего элемента
    auto pop_test(Container& container, int initial_size, int test_iterations) {
        // Заполнение начального контейнера
        for (int i = 0; i < initial_size; ++i) {
            if constexpr (std::is_same_v<typename Container::value_type, std::string>) {
                container.push_back("initial");
            }
            else {
                container.push_back(gen() % 1000);
            }
        }

        std::chrono::duration<double, std::milli> total_time{};

        for (int i = 0; i < test_iterations; ++i) {
            if constexpr (std::is_same_v<typename Container::value_type, std::string>) {
                container.push_back("test");
            }
            else {
                container.push_back(gen() % 1000);
            }

            auto begin = std::chrono::high_resolution_clock::now();
            container.pop_back();
            auto end = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        }

        return total_time / test_iterations;
    }
};

// Функция для форматированного вывода результатов
void print_line(std::string_view prefix, std::chrono::duration<double, std::milli> t1, std::chrono::duration<double, std::milli> t2) {
    std::cout << std::setw(15) << prefix
        << std::setw(15) << t1.count()
        << std::setw(15) << t2.count()
        << std::setw(15) << (t1.count() / t2.count())
        << std::endl;
}

#endif // DATA_STRUCTURE_TEST_H