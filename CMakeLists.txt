
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Battle-Sity)




add_executable(Battle-Sity src/main.cpp
	src/renderer/shaderProgram.cpp
	src/renderer/shaderProgram.h
	src/renderer/Texture2d.h
	src/renderer/Texture2d.cpp
	src/renderer/Sprite.cpp
	src/renderer/Sprite.h
	src/resources/ResourceManager.h
	src/resources/ResourceManager.cpp 
	src/resources/stb_image.h
)



# - set(CMAKE_CXX_STANDARD, 17)
target_compile_features(Battle-Sity PUBLIC cxx_std_17)




# - загружает и билдит cmake file
add_subdirectory(external/glfw)
target_link_libraries(Battle-Sity glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(Battle-Sity OpenGL::GL)

# - загружает  file математики
include_directories(external/glm)

# - загружает и билдит cmake file
add_subdirectory(external/glad)
target_link_libraries(Battle-Sity Glad)

set_target_properties(Battle-Sity PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET Battle-Sity POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res  $<TARGET_FILE_DIR:Battle-Sity>/res 
				)


