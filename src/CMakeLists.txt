set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/todo_app/*.hpp")

set(HEADER_TODO_ITEM "${PROJECT_SOURCE_DIR}/include/todo_app/todo_item.hpp")
set(HEADER_UID_GEN "${PROJECT_SOURCE_DIR}/include/todo_app/uid_generator.hpp")

add_library(todo_item_lib todo_item_impl.cpp ${HEADER_TODO_ITEM})
add_library(uid_gen_lib uid_generator_impl.cpp ${HEADER_UID_GEN})

target_include_directories(todo_item_lib PUBLIC ../include)
target_include_directories(uid_gen_lib PUBLIC ../include)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST})
