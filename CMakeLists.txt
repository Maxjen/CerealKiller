project(CerealKiller)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")

#aux_source_directory(. SRC_LIST)
set(SRC_LIST
	Core.cpp
	main.cpp
)

find_package(OpenGL)

#SDL2 plus dependencies
set(SDL2
    /usr/local/lib/libSDL2.a
    pthread
    dl
    rt
    m
)

include_directories("${PROJECT_SOURCE_DIR}/include/")

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${SDL2} ${OPENGL_gl_LIBRARY})
