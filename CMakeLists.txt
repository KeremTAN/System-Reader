cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 17)

project(System-Reader)

set (PROJECT_DIR ${CMAKE_SOURCE_DIR})

set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/WindowsReader.cpp
    ${PROJECT_SOURCE_DIR}/MacOsReader.cpp)

set(PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIR}/ISystemReader.hpp
    ${PROJECT_SOURCE_DIR}/WindowsReader.hpp
    ${PROJECT_SOURCE_DIR}/MacOsReader.hpp
    ${PROJECT_INCLUDE_DIR}/nlohmann/*.hpp)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})