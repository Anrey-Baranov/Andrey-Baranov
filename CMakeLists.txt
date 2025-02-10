# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.31.0 FATAL_ERROR)


# название проекта
project(Algorithms-and-Data-Structures)


# Подключаем дополнительные CMakeLists.txt
include(cmake/function.cmake)

add_subdirectory(lib_easy_example)
add_subdirectory(lib_queue)
add_subdirectory(lib_polynom_monom)
add_subdirectory(lib_pair)
add_subdirectory(lib_list)
add_subdirectory(lib_stack)
add_subdirectory(main)
add_subdirectory(lib_dsu)

option(BTEST "build test?" ON)

if(BTEST)
    add_subdirectory(gtest)  # Убедитесь, что gtest правильно подключен
    add_subdirectory(tests)   # Убедитесь, что здесь есть CMakeLists.txt для тестов
endif()