cmake_minimum_required(VERSION 3.4)

project(yal)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_FMTLIB "Builds the fmtlib-4.0.0" ON)
option(BUILD_GTEST "Builds the gtest-1.8.0" ON)
option(BUILD_TESTS "Builds the tests" ON)
option(BUILD_EXAMPLES "Builds the examples" ON)

set(3RD_PARTY_DIR 3rd-party)

if(BUILD_FMTLIB)
    set(FMTLIB_DIR "${3RD_PARTY_DIR}/fmt-4.0.0")
    add_subdirectory(${FMTLIB_DIR})
    include_directories(${FMTLIB_DIR})
endif()

if(BUILD_GTEST)
    set(BUILD_GTEST ON CACHE BOOL "Build gtest-1.80")
    set(BUILD_GMOCK OFF CACHE BOOL "Build gmock-1.80")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(GTEST_DIR "${3RD_PARTY_DIR}/gtest-1.8.0")
    add_subdirectory(${GTEST_DIR})
    include_directories(${GTEST_DIR}/googletest/include)
endif()

find_package(Threads)

get_filename_component(YAL_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${YAL_ROOT}/bin)

set(YAL_INCLUDE "${YAL_ROOT}/include")
include_directories(${YAL_INCLUDE})

set(YAL_HEADERS "${YAL_INCLUDE}/yal")
set(YAL_SOURCES "${YAL_ROOT}/src")

set(HEADERS
    ${YAL_HEADERS}/core.h
    ${YAL_HEADERS}/entries.h
    ${YAL_HEADERS}/printers.h
    ${YAL_HEADERS}/sinks.h
    ${YAL_HEADERS}/severities.h
    ${YAL_HEADERS}/utils.h
    ${YAL_HEADERS}/yal.h)

set(SOURCES
    ${YAL_SOURCES}/core.cpp
    ${YAL_SOURCES}/entries.cpp
    ${YAL_SOURCES}/printers.cpp
    ${YAL_SOURCES}/sinks.cpp
    ${YAL_SOURCES}/severities.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

if(BUILD_TESTS)
    set(TEST_PROJECT test_${PROJECT_NAME})
    add_test(NAME ${TEST_PROJECT} COMMAND ${TEST_PROJECT})

    add_subdirectory(tests)

    enable_testing()
endif()

if(BUILD_EXAMPLES)
    set(EXAMPLES
        custom_printers
        custom_sinks
        default_settings)
    foreach(example IN ITEMS ${EXAMPLES})
        add_executable(${example} examples/${example}.cpp)
        target_link_libraries(${example}
            fmt
            yal
            ${CMAKE_THREAD_LIBS_INIT})
    endforeach()
endif()
