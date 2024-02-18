cmake_minimum_required(VERSION 2.4)

project(overnight)

add_executable(overnight main.c ../../src/ftoa.c)
include_directories(../../src)
