cmake_minimum_required(VERSION 3.12) 

project(library_management)  

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(manage_library main.cpp UserRegistration.cpp ItemManagement.cpp)  