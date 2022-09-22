#include <iostream>

#include "../include/todo_app/core_app.hpp"

int main() {
	 fv_todo::ToDoApp app;
	 while(1) {
	 	app.prompt();
	 	app.process_user_input();
	 }
	return 0;
}
