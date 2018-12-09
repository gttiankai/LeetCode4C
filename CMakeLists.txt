cmake_minimum_required(VERSION 3.12)
project(LeetCode)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS -g)
add_executable(LeetCode

        tree/rebuild_tree.c
        tree/balanced_tree.c
        array/find_second_smallest_elements.cpp
        sort/sort_list.c )