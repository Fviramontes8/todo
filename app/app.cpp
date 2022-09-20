#include <iostream>

#include "../include/todo_app/todo_item.hpp"
#include "../include/todo_app/sqlite_database.hpp"

int main() {
	fv_todo::Date today;
	std::cout << "Today's date: " << today << "\n\n";

	fv_todo::ToDoItem init_task("Print this task");
	std::cout << init_task << '\n';

	fv_todo::SQLiteDB db;
	db.add_task(init_task);
	db.print_database();
//	db.read_task(init_task.uid());
//	db.delete_task(init_task.uid());
//	db.print_database();

	return 0;
}
