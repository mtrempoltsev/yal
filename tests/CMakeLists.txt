project(${YAL_TEST_PROJECT})

set(SOURCES
    main.cpp)

include_directories(${YAL_INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} yal fmt gtest_main ${Boost_LIBRARIES})
