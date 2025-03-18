cmake_minimum_required(VERSION 3.10)
project(s2o)

set(CMAKE_C_STANDARD 11)

include_directories(src/l8w8jwt)
add_subdirectory(src/lib/l8w8jwt)

add_executable(s2o src/l8w8.c)
target_link_libraries(s2o l8w8jwt)