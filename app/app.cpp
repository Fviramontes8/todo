#include <iostream>
#include <filesystem>
#include <sstream>
#include "crow.h"

#include "../include/todo_app/core_app.hpp"

int main() {
	 fv_todo::ToDoApp todo_app;
	 // CLI code:
//	 while(1) {
//	 	todo_app.prompt();
//	 	todo_app.process_user_input();
//	 }

	crow::SimpleApp app;
	CROW_ROUTE(app, "/")(
		[]() {
			return fv_todo::homepage();
		}
	);

	CROW_ROUTE(app, "/add_task")(
		[]() {
			return fv_todo::add_task_page();
		}
	);

	CROW_ROUTE(app, "/adding_task")(
		[&todo_app](const crow::request& req) {
			if (req.url_params.get("title") != nullptr) {
				std::string title{req.url_params.get("title")};
				todo_app.push_task(title);
				todo_app.print_tasks();
				return fv_todo::add_task_success();
			}
			return fv_todo::add_task_failure();
		}
	);

	app.port(8080).multithreaded().run();

	return 0;
}
