cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)

project(Nitor LANGUAGES CXX C VERSION 0.1)

option(Examples "Build Examples?" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freetype-2.10.0)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (Examples)
	set(CMAKE_CXX_FLAGS "-g")
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
	unset(Examples CACHE)
endif()
