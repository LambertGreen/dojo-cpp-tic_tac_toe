# create library
add_library(tic-tac-toe_lib game.cpp board.cpp)

# create executable
add_executable(tic-tac-toe main.cpp)
target_link_libraries(tic-tac-toe tic-tac-toe_lib)
