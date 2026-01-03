cmake_minimum_required(VERSION 4.0)
project(codebox-tests)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_executable(codebox-tests)

target_sources(
    codebox-tests PRIVATE
    cbcore/test.cbcore.strings.cpp
)

target_link_libraries(
    codebox-tests
    GTest::gtest_main
    cbcore
)

include(GoogleTest)
gtest_discover_tests(codebox-tests)
