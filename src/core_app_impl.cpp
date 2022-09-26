#include <sstream>
#include "../include/todo_app/core_app.hpp"
#include "../include/todo_app/date.hpp"

namespace fv_todo {
	std::string homepage() {
		fv_todo::Date today;
		return std::string (
			"<head> <title> ToDo App </title> </head>"
			"<body> <center>"
	
			"<p1> Welcome! <br> "
			"Today is " + today.to_str() + "<br>" +
			"Here are your current tasks: </p1>"
	
			"<div class=\"container\">"
			"<a href=\"add_task\">"
			"<button class=\"btn btn-primary btn-lg\">Add task"
			"</button> </a> </div>"
	
			"</center> </body>"
		);
	}
	
	std::string add_task_page() {
		return std::string(
			"<body> <center>"
	
			"<div class=\"container\"> <form action=\"/adding_task\">"
			"<label for=\"title\">Title name:</label><br>"
			"<input type=\"text\" id=\"title\" name=\"title\"><br>"
			"<input type=\"submit\" value=\"Submit\"><br>"
			"</form> </div>"
	
			"<div class=\"container\">"
			"<a href=\"/\">"
			"<button class=\"btn btn-primary btn-lg\">Return home"
			"</button> </a> </div>"
	
			"</center> </body>"
		);
	}
	
	std::string add_task_failure() {
		return std::string(
			"<body> <center>"
	
			"<h1>Task was not created, please return to add task page</h1>"
	
			"<div class=\"container\">"
			"<a href=\"/\">"
			"<button class=\"btn btn-primary btn-lg\">Return home"
			"</button> </a> </div>"
	
			"</center> </body>"
		);
	}
	
	std::string add_task_success() {
		return std::string(
			"<body> <center>"
	
			"<h1>Task was created!</h1>"
	
			"<div class=\"container\">"
			"<a href=\"/add_task\">"
			"<button class=\"btn btn-primary btn-lg\">Add another task"
			"</button> </a> </div>"
	
			"<div class=\"container\">"
			"<a href=\"/\">"
			"<button class=\"btn btn-primary btn-lg\">Return home"
			"</button> </a> </div>"
	
			"</center> </body>"
		);
	}

	void introduction() {
		Date today;
		std::cout << "Welcome!\nToday is " << today << '\n';
	}

	ToDoApp::ToDoApp() : _user_input{0} {}

	void ToDoApp::prompt() const {
		std::cout << "Select one of the following:\n";
		std::cout << "[0] Exit application\n";
		std::cout << "[1] Add a task\n";
		std::cout << "[2] Print all tasks\n";
		std::cout << "[3] Print a specific task (requires ID)\n";
		std::cout << "[4] Delete a task\n";
	}

	void ToDoApp::process_user_input() {
		std::cin >> _user_input;
		switch (_user_input) {
			case 0:
				exit(0);
				break;
			case 1:
				push_task();
				break;
			case 2:
				print_tasks();
				break;
			case 3:
				print_task();
				break;
			case 4:
				pop_task();
				break;
			default:
				std::cout << "Please enter a valid input specified";
				std::cout << " by the prompt\n";
				break;
		}
	}

	void ToDoApp::push_task() {
		std::cout << "Please enter the title of your task" << std::endl;
		getchar();
		std::string user_title = "";
		std::getline(std::cin, user_title, '\n');
		ToDoItem task_to_push(user_title);
		_database.add_task(task_to_push);
		std::cout << "Added task!\n";
	}

	void ToDoApp::push_task(const std::string &title) {
		ToDoItem task_to_push(title);
		_database.add_task(task_to_push);
	}

	void ToDoApp::print_tasks() {
		std::cout << "---------------------------------------\n";
		_database.print_database();
		std::cout << "---------------------------------------\n";
	}

	void ToDoApp::print_task() {
		int user_id;
		std::cout << "Please enter id of task to print\n";
		std::cin >> user_id;
		_database.print_task(user_id);
	}

	void ToDoApp::pop_task() {
		int user_id;
		std::cout << "Please enter id of task to delete\n";
		std::cin >> user_id;
		_database.delete_task(user_id);
		std::cout << "Entry removed if it exists\n";
	}
}
