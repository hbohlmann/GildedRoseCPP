include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests
        GildedRoseUnitTests.cpp
        )

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests GildedRose)
