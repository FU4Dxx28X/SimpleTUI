cmake_minimum_required(VERSION 3.10)
project(simple_tui)
add_executable(run
main.cxx
tuilib/tuilib.cpp)
target_include_directories(run PRIVATE tuilib)
target_link_libraries(run PRIVATE ncurses)
set_target_properties(run PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
