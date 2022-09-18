cmake_minimum_required(VERSION 3.14..3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
	todo_app
	VERSION 1.0
	DESCRIPTION "Simple todo application"
	LANGUAGES CXX)

#find_package(Git REQUIRED)
#include(FetchContent)
#FetchContent_Declare(
#	uuidv4
#	GIT_REPOSITORY https://github.com/crashoz/uuid_v4.git
#	GIT_TAG v1.0.0)
#FetchContent_MakeAvailable(uuidv4)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(app)
add_subdirectory(src)
