 
# lib_pair/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Укажите имя библиотеки
add_library(Pair pair.cpp)

# Укажите заголовочные файлы
target_include_directories(Pair PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
