cmake_minimum_required(VERSION 2.8.12)
project(table)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
find_package(GMP REQUIRED)
add_executable(table table.c)
target_link_libraries(table gmp gmp)
