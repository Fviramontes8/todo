cmake_minimum_required(VERSION 3.14..3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
	todo_app
	VERSION 1.0
	DESCRIPTION "Simple todo application"
	LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(app)
add_subdirectory(src)
