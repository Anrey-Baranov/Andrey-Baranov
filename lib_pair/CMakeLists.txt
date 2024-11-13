<<<<<<< HEAD
﻿# указывайте последнюю доступную вам версию CMake
cmake_minimum_required(VERSION 3.31.0 FATAL_ERROR)

create_project_lib(Pair)
=======
 
# lib_pair/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Укажите имя библиотеки
add_library(Pair pair.cpp)

# Укажите заголовочные файлы
target_include_directories(Pair PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
>>>>>>> 989b449b77dd9db91fb4f879bbafc8aa6e06d032
