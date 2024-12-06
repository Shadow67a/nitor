add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
	PRIVATE
		./glad.c
		./Window.cpp
		./Init.cpp
		./Mesh.cpp
		./Shader.cpp
		./Elements.cpp
		./Error.cpp
		./Camera.cpp
		./Light.cpp
		./Text.cpp
		./Model.cpp
		./Skybox.cpp
		./Scene.cpp
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	# Internal library headers and dependencies.

	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freetype-2.10.0/include
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include

	PUBLIC
	# Library's public headers for top-level project.

	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>

	# Library's public headers for external projects.

	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} glm freetype assimp)
