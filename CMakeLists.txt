project(CerealKiller)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

#aux_source_directory(. SRC_LIST)
set(SRC_LIST
	Math/Vec3.cpp
	Math/Vec2.cpp
	Shader/PointLineShader.cpp
	Shader/TriangleShader.cpp
	Shader/Shader.cpp
	ResourceManager.cpp
	RenderManager.cpp
	Layer.cpp
	Triangles.cpp
	Selection.cpp
	Actions/Action.cpp
	Actions/ActionManager.cpp
	Actions/SelectVertices.cpp
	Actions/RemoveSelection.cpp
	Actions/MoveSelection.cpp
	Actions/ScaleSelection.cpp
	Actions/RotateSelection.cpp
	Actions/CreateTriangle.cpp
	Actions/FillTriangle.cpp
	ActionHandler/ActionHandler.cpp
	ActionHandler/MoveHandler.cpp
	ActionHandler/ScaleHandler.cpp
	ActionHandler/RotationHandler.cpp
	ActionHandler/TriangleCreationHandler.cpp
	Core.cpp
	main.cpp
)

#SDL2 plus dependencies
set(SDL2
    /usr/local/lib/libSDL2.a
	/usr/local/lib/libSDL2_image.a
    pthread
    dl
    rt
    m
)

find_package(OpenGL)
find_package(GLEW)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(
	${PROJECT_NAME}
	${SDL2}
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARY}
	#/usr/lib/x86_64-linux-gnu/libGLEW.so
)
