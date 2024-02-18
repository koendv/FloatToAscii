cmake_minimum_required(VERSION 2.4)

project(test)

add_executable(test main.c ../../src/ftoa.c)
include_directories(../../src)
