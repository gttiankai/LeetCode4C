cmake_minimum_required(VERSION 3.12)
project(LeetCode)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER  "clang")
set(CMAKE_C_FLAGS "-g")
add_executable(LeetCode

        tree/rebuild_tree.c
        tree/balanced_tree.c
        array/find_second_smallest_elements.c
        array/find_first_and_last_position.c
        sort/sort_list.c
        binary_search_tree/validate_binaray_search_tree.c
        tree/binary_tree_inorder_traversal_94.c tree/black_red_tree.c)