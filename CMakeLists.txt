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
	Action.cpp
	ActionManager.cpp
	ActionHandler.cpp
	Layer.cpp

	Context.cpp
	MapEditor/MapEditor.cpp
	MapEditor/Actions/SelectVertices.cpp
	MapEditor/Actions/RemoveSelection.cpp
	MapEditor/Actions/MoveSelection.cpp
	MapEditor/Actions/ScaleSelection.cpp
	MapEditor/Actions/RotateSelection.cpp
	MapEditor/Actions/CreateTriangle.cpp
	MapEditor/Actions/FillTriangle.cpp
	MapEditor/ActionHandler/MoveHandler.cpp
	MapEditor/ActionHandler/ScaleHandler.cpp
	MapEditor/ActionHandler/RotationHandler.cpp
	MapEditor/ActionHandler/TriangleCreationHandler.cpp

	Triangles.cpp
	Selection.cpp

	CharacterEditor/CharacterEditor.cpp
	CharacterEditor/CharSelection.cpp
	CharacterEditor/BoneLayer.cpp
	CharacterEditor/Actions/SelectBoneVertices.cpp
	CharacterEditor/Actions/RemoveBoneSelection.cpp
	CharacterEditor/Actions/MoveBoneSelection.cpp
	CharacterEditor/Actions/ScaleBoneSelection.cpp
	CharacterEditor/Actions/RotateBoneSelection.cpp
	CharacterEditor/Actions/CreateBone.cpp
	CharacterEditor/ActionHandler/MoveBoneHandler.cpp
	CharacterEditor/ActionHandler/ScaleBoneHandler.cpp
	CharacterEditor/ActionHandler/RotationBoneHandler.cpp
	CharacterEditor/ActionHandler/BoneCreationHandler.cpp
	Bones.cpp
	Core.cpp
	main.cpp
)

#SDL2 plus dependencies
set(SDL2
    #/usr/local/lib/libSDL2.a
    /usr/lib64/libSDL2.so
    #/usr/local/lib/libSDL2_image.a
    /usr/lib64/libSDL2_image.so
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
