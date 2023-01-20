cmake_minimum_required(VERSION 3.23)
project(CFlags C)

set(CMAKE_C_STANDARD 99)

add_library(CFlags src/cflags.c)
add_executable(CFlagsTest test/main.c)

target_link_libraries(CFlagsTest CFlags)