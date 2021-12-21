cmake_minimum_required (VERSION 3.6.1)
project(celldevs-tutorial)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_COMPILER "g++")
add_compile_options(-g)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../cadmium/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../cadmium-web-extension/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../cadmium/json/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../DESTimes/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(Boost_USE_MULTITHREADED TRUE)
find_package(Boost COMPONENTS unit_test_framework system thread REQUIRED)

file(MAKE_DIRECTORY logs)


add_executable(cancer cancer/main.cpp)


target_link_libraries(cancer  PUBLIC ${Boost_LIBRARIES})


