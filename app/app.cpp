#include <iostream>

#include "../include/todo_app/todo_item.hpp"
#include "../include/todo_app/sqlite_database.hpp"

int main() {
	fv_todo::Date today;
	std::cout << "Today's date: " << today << "\n\n";

	fv_todo::ToDoItem init_task("Show this instance");
	std::cout << init_task << '\n';

	fv_todo::SQLiteDB db;
	db.add_task(init_task);

	return 0;
}
