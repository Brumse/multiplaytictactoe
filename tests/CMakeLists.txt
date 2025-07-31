include(${CMAKE_SOURCE_DIR}/cmake/GetGoogleTest.cmake)

enable_testing()

add_executable(
        hello_test
        hello_test.cpp
)
target_link_libraries(
        hello_test
        GTest::gtest_main
)

add_executable(
        test_tictactoe
        test_tictactoe.cpp
        )
target_link_libraries(
        test_tictactoe
        GTest::gtest_main
        tictactoe
)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(test_tictactoe)
