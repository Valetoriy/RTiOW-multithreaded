cmake_minimum_required(VERSION 3.23.2)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

project(rays LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
    fmt
    -fsanitize=address,undefined)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall -Wextra -Wpedantic -Wconversion
    -fsanitize=address,undefined)
