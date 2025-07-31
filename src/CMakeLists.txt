add_library(tictactoe tictactoe.cpp)
target_include_directories(tictactoe 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)