cmake_minimum_required(VERSION 3.15)
project (template_linked_list CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(target templateLinkedList)
add_executable(${target} templateLinkedList.cpp)