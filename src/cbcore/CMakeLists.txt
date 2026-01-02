CMAKE_MINIMUM_REQUIRED(VERSION 4.00)

project(cbcore LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(cbcore SHARED)

target_include_directories(cbcore PRIVATE ${CODEBOX_ROOT_DIR}/external/)

target_sources(
    cbcore PRIVATE
    FILE_SET CXX_MODULES
    FILES
    module.core.cpp
    string.cpp
    string.functions.cpp
    string.convert.cpp
    util.functions.cpp
    file.cpp
    log.cpp
    log.logger.cpp
    log.formatter.cpp
    log.formatter.plaintext.cpp
)

set_target_properties(cbcore PROPERTIES CXX_MODULE_TYPE GLOBAL)