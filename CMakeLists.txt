cmake_minimum_required(VERSION 3.26.3)
set(DOWNLOAD_EXTRACT_TIMESTAMP true)

project(tarantinopp VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src)

OPTION(BUILD_EXAMPLE "Build example executables" ON)
if(BUILD_EXAMPLE)
    message(STATUS "Building examples...")
    add_subdirectory(examples)
    endif()
    
    OPTION(BUILD_TESTS "Build test executables" ON)
if(BUILD_TESTS)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
endif()
