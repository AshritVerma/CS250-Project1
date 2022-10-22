cmake_minimum_required(VERSION 3.23)
project(image LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

add_library(common progargs.cpp progargs.hpp)
add_library(aos main-aos.cpp)
add_library(soa main-soa.cpp)

add_executable(image-aos imageaos.cpp)
target_link_libraries(image-aos common aos)
add_executable(image-soa imagesoa.cpp)
target_link_libraries(image-soa common soa)
