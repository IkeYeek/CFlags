cmake_minimum_required(VERSION 3.23)
project(CFlags)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

#target_link_libraries(CFlagsTest CFlags)
#target_link_libraries(CFlagsTest BooleanByteArray)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#add_library(CFlags src/cflags.c src/boolean_byte_array.c src/boolean_byte_array.h)
add_library(BooleanByteArray src/cbitset.c src/cbitset.h)
add_executable(CFlagMain test/main.c)

target_link_libraries(CFlagMain BooleanByteArray)

enable_testing()

add_executable(
        testbitset
        test/testbitset.cpp
)
target_link_libraries(
        testbitset
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testbitset)