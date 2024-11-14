cmake_minimum_required(VERSION 3.12)

project(genesis)

include_directories(include)

file(GLOB SOURCES "rdma/*.cc")
file(GLOB TEST_SOURCES "test/*.cc")

add_library(${PROJECT_NAME} ${SOURCES})

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
endforeach()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_TYPE=1)
else()
    add_definitions(-DCMAKE_BUILD_TYPE=2)
endif()

