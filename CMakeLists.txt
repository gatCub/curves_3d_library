cmake_minimum_required(VERSION 3.10.0)
project(curves VERSION 0.1.0 LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared lib" ON)

add_library(curves_library 
            src/curves_lib.cpp
            src/curvefactory.cpp
)
target_include_directories(curves_library PUBLIC include)
set_target_properties(curves_library PROPERTIES OUTPUT_NAME "curves_library")

add_executable(main src/main.cpp)
target_link_libraries(main curves_library)

add_executable(tests src/test/tests.cpp)
target_link_libraries(tests curves_library)
include(CTest)
enable_testing()

add_test(NAME AutoTests
        COMMAND  tests       
)

add_custom_command(TARGET tests POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND $<TARGET_FILE:tests>
    COMMENT "Running auto tests after build..."
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
