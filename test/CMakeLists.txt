include_directories(${tic-tac-toe_SOURCE_DIR}/src)
add_executable(tests test.cpp)
target_link_libraries(tests tic-tac-toe_lib)

add_test(NAME TestTicTacToe COMMAND tests)
