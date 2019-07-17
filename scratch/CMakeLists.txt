add_executable(scratch scratch.cpp)
target_link_libraries(scratch core server)

add_executable(gen-board gen-board.cpp)
target_link_libraries(gen-board core server)
