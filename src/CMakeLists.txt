add_library(gamelogic gamelogic.cpp)
target_include_directories(gamelogic
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(gui)
