cmake_minimum_required(VERSION 3.14..3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

project(
	todo_app
	VERSION 1.0
	DESCRIPTION "Simple todo application"
	LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
	crow
	GIT_REPOSITORY https://github.com/crowcpp/crow.git
	GIT_TAG v1.0+4)
FetchContent_MakeAvailable(crow)

add_definitions(-DCMAKE_PROJECT_HOME=${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(app)
add_subdirectory(src)
