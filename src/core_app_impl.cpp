#include <sstream>
#include "../include/todo_app/core_app.hpp"
#include "../include/todo_app/date.hpp"

namespace fv_todo {
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
