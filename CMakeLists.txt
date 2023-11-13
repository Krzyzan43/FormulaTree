cmake_minimum_required(VERSION 3.5.0)
project(formula_tree VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 98)

add_executable(formula_tree
    main.cpp
    Node.cpp
    Node.h
    Tree.h
    Utils.h
    Utils.cpp
    CLI.cpp
    CLI.h
    Tree.cpp
)

