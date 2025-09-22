cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(BattleSity)

add_executable(BattleSity src/main.cpp)

add_subdirectory(external/glfw)
target_link_libraries(BattleSity glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(BattleSity OpenGL::GL)

