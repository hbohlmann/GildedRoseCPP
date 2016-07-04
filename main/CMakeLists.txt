cmake_minimum_required(VERSION 2.8)

project(GildedRose)

add_definitions(-std=c++11)

set(HEADER_FILES
    GildedRose.h
        )

set(SOURCE_FILES
    GildedRose.cpp
    )

add_library(GildedRose STATIC ${SOURCE_FILES} ${HEADER_FILES})
