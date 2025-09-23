
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Battle-Sity)

add_executable(Battle-Sity src/main.cpp)

add_subdirectory(external/glfw)
target_link_libraries(Battle-Sity glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(Battle-Sity OpenGL::GL)

add_subdirectory(external/glad)
target_link_libraries(Battle-Sity Glad)

