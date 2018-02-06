cmake_minimum_required(VERSION 3.4)

project(yal)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(YAL_ROOT "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

option(YAL_BUILD_FMTLIB "Builds the fmtlib-4.0.0" ON)
option(YAL_BUILD_GTEST "Builds the gtest-1.8.0" ON)
option(YAL_BUILD_TESTS "Builds the tests" ON)
option(YAL_BUILD_EXAMPLES "Builds the examples" ON)

set(3RD_PARTY_DIR ${YAL_ROOT}/3rd-party)

if(YAL_BUILD_FMTLIB)
    set(YAL_FMTLIB_DIR "${3RD_PARTY_DIR}/fmt-4.0.0")
    add_subdirectory(${YAL_FMTLIB_DIR})
    include_directories(${YAL_FMTLIB_DIR})
endif()

if(YAL_BUILD_GTEST)
    set(BUILD_GTEST ON CACHE BOOL "Build gtest")
    set(BUILD_GMOCK OFF CACHE BOOL "Build gmock")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(YAL_GTEST_DIR "${3RD_PARTY_DIR}/gtest-1.8.0")
    add_subdirectory(${YAL_GTEST_DIR})
    include_directories(${YAL_GTEST_DIR}/googletest/include)
endif()

find_package(Boost COMPONENTS filesystem system)
if(Boost_FOUND)
    add_definitions(-DYAL_USES_BOOST)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Threads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${YAL_ROOT}/bin)

set(YAL_INCLUDE "${YAL_ROOT}/include")
include_directories(${YAL_INCLUDE})

set(YAL_HEADERS "${YAL_INCLUDE}/yal")
set(YAL_SOURCES "${YAL_ROOT}/src")

set(HEADERS
    ${YAL_HEADERS}/abstract_sink.h
    ${YAL_HEADERS}/core.h
    ${YAL_HEADERS}/entries.h
    ${YAL_HEADERS}/formatter.h
    ${YAL_HEADERS}/items.h
    ${YAL_HEADERS}/sinks.h
    ${YAL_HEADERS}/severities.h
    ${YAL_HEADERS}/utils.h
    ${YAL_HEADERS}/yal.h)

set(SOURCES
    ${YAL_SOURCES}/core.cpp
    ${YAL_SOURCES}/entries.cpp
    ${YAL_SOURCES}/items.cpp
    ${YAL_SOURCES}/sinks.cpp
    ${YAL_SOURCES}/severities.cpp
    ${YAL_SOURCES}/utils.cpp)

if(Boost_FOUND)
    set(HEADERS ${HEADERS}
        ${YAL_HEADERS}/rolling_file.h)
    set(SOURCES ${SOURCES}
        ${YAL_SOURCES}/rolling_file.cpp)
endif()

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

if(YAL_BUILD_TESTS)
    set(YAL_TEST_PROJECT test_${PROJECT_NAME})
    add_test(NAME ${YAL_TEST_PROJECT} COMMAND ${YAL_TEST_PROJECT})

    add_subdirectory(tests)

    enable_testing()
endif()

if(YAL_BUILD_EXAMPLES)
    set(YAL_EXAMPLES
        custom_formatting
        custom_sinks
        default_settings)
    foreach(example IN ITEMS ${YAL_EXAMPLES})
        add_executable(${example} examples/${example}.cpp)
        target_link_libraries(${example}
            fmt
            yal
            ${CMAKE_THREAD_LIBS_INIT}
            ${Boost_LIBRARIES})
    endforeach()
endif()
