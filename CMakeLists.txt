cmake_minimum_required(VERSION 2.8)
project(GildedRose)

add_definitions(-std=c++11)

set(SOURCE_FILES main.cpp)
add_executable(GildedRose_run ${SOURCE_FILES})

include_directories(main)

add_subdirectory(main)
add_subdirectory(test)

target_link_libraries(GildedRose_run GildedRose)
