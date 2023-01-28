#ifndef FV_TODOAPP_HPP
#define FV_TODOAPP_HPP

#include <iostream>

#include "todo_item.hpp"
#include "sqlite_database.hpp"

namespace fv_todo {
	// Only CLI relevant
	void introduction();

	// Main class
	class ToDoApp {
		private:
			int _user_input;
			SQLiteDB _database;

		public:
			ToDoApp();

			// CLI relevant
			void prompt() const;
			void process_user_input();
			void push_task();
			void print_tasks();
			void print_task();
			void pop_task();

			// Webpage relevant
			void push_task(const std::string &title);


			// TODO Later
			void update_task(unsigned long long id);
			void mark_task_complete(unsigned long long id);
	};
}
#endif // FV_TODOAPP_HPP
