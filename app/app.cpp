#include <iostream>
#include <filesystem>
#include <string>

#include "crow.h"

#include "../include/todo_app/core_app.hpp"

int main() {
	std::string project_name{CMAKE_PROJECT_HOME};
	crow::mustache::set_global_base(project_name+"/html");
//	std::cout << '\'' << project_name << '\'' << '\n';
//	std::cout << '\'' << std::string{project_name+"/html/add_task_page.html"} << "\'\n";
	fv_todo::ToDoApp todo_app;
//	CLI code:
//	 while(1) {
//	 	todo_app.prompt();
//	 	todo_app.process_user_input();
//	 }

	crow::SimpleApp app;
	CROW_ROUTE(app, "/")(
		[]() {
			fv_todo::Date today;
			auto page = crow::mustache::load("index.html");
			crow::mustache::context ctx({{"today", today.to_str()}});
			return page.render(ctx);
			//return fv_todo::homepage();
		}
	);

	CROW_ROUTE(app, "/add_task")(
		[]() {
			return crow::mustache::load_text(
				std::string{"add_task_page.html"}
			);
		}
	);

	CROW_ROUTE(app, "/adding_task")(
		[&todo_app](const crow::request& req) {
			if (req.url_params.get("title") != nullptr) {
				std::string title{req.url_params.get("title")};
				todo_app.push_task(title);
				todo_app.print_tasks();
				return crow::mustache::load_text(
					std::string{"add_task_success.html"}
				);
			}
			return crow::mustache::load_text(
				std::string{"add_task_failure.html"}
			);
		}
	);

	app.port(8080).multithreaded().run();

	return 0;
}
