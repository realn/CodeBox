CMAKE_MINIMUM_REQUIRED(VERSION 4.0)

project(codebox)

set(CODEBOX_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/googletest)

add_subdirectory(src/cbcore)

add_subdirectory(test)
