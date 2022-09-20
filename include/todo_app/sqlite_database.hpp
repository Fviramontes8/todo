#include <sqlite3.h>

#include "todo_item.hpp"

namespace fv_todo {
	class SQLiteDB {
		private:
			sqlite3* _database;

			void check_db_folder();
			void start_db();
			void stop_db();
			void create_todo_db();
			void write_to_db_log(std::string msg);

			/*
			 * @brief Required callback function needed to execute sql commands
			 */
			static int callback(void* not_used, 
					int argc, char* argv[], char** az_col_name);

		public:
			SQLiteDB();
			~SQLiteDB();

			void add_task(const ToDoItem& tdi);
			void update_task(const ToDoItem& tdi);
	};
}
