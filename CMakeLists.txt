cmake_minimum_required(VERSION 3.10.0)
project(curves VERSION 0.1.0 LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared lib" ON)

add_library(curves_lib src/curves_lib.cpp)
target_include_directories(curves_lib PUBLIC include)
set_target_properties(curves_lib PROPERTIES OUTPUT_NAME "curves_library")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
