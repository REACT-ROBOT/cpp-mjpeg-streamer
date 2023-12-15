cmake_minimum_required(VERSION 3.5)

project(igl_streamer)

set(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)


#add_subdirectory(sound)
#add_subdirectory(include)
#add_subdirectory(lib)

add_subdirectory(examples)
#add_subdirectory(tools)
