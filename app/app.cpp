#include <iostream>

#include "../include/todo_app/uid_generator.hpp"
#include "../include/todo_app/date.hpp"
#include "../include/todo_app/todo_item.hpp"

int main() {
	fv_todo::Date today;
	std::cout << "Today's date: " << today << "\n\n";

	fv_todo::ToDoItem init_task("Show this instance");
	std::cout << init_task << '\n';

	return 0;
}
