cmake_minimum_required(VERSION 3.10)

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

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
