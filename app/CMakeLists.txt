cmake_minimum_required(VERSION 3.14..3.22)

add_executable(
	${PROJECT_NAME} 
	app.cpp 
	../src/date_impl.cpp
	../src/uid_generator_impl.cpp
	../src/todo_item_impl.cpp
	../src/sqlite_database_impl.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC sqlite3)
