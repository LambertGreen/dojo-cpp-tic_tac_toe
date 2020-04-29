cmake_minimum_required(VERSION 3.10)

# set project name
project(tic-tac-toe)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# add src subdirectory
add_subdirectory(src)

# add testing support
enable_testing()
add_subdirectory(test)

