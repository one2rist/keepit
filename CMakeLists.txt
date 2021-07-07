cmake_minimum_required(VERSION 3.10)

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(
    keepit_app
    VERSION 0.1
    DESCRIPTION "Task for KEEPIT"
    LANGUAGES CXX
)

# Project targets:
set(TARGET ${PROJECT_NAME})
message(STATUS "target: ${TARGET}")
message(STATUS "description: ${DESCRIPTION}")

add_executable(
    ${TARGET}
    src/fileReader.h
    src/functions.h
    src/main.cpp
)

target_compile_features(${TARGET} PRIVATE cxx_std_17)
target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${TARGET} PRIVATE Threads::Threads)
