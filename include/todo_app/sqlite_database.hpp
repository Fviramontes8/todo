#ifndef FV_SQLITEDB_HPP
#define FV_SQLITEDB_HPP

#include <sqlite3.h>

#include "todo_item.hpp"

namespace fv_todo {
	class SQLiteDB {
		private:
			sqlite3* _database;

			/*
			 * @brief Checks if the db/ folder exists, if it does not exist,
			 * 	it will create the folder then start up the database to create
			 * 	the todo.db file, then the database is closed.
			 */
			void check_db_folder();

			/*
			 * @brief Assumes the db/todo.db file exists or is able to be
			 * 	created, and opens the file, creating the database connection.
			 */
			void start_db();

			/*
			 * @brief Closes the db/todo.db file, closing the connection to
			 * 	the database.
			 */
			void stop_db();

			/*
			 * @brief Creates the TODO database which will host one or many
			 * 	instances of the ToDoItem class.
			 */
			void create_todo_db();

			/*
			 * @brief Writes a string to db/log.txt with the date and time
			 * 	pre-fixed.
			 *
			 * An example: 
			 * 	xx/xx/xx xx:xx:xx <msg>
			 *
			 * @param msg The message to write to a log.
			 */
			void write_to_db_log(std::string msg);

			/*
			 * @brief Executes a sql command via a std::string, also allows
			 * 	for a customized callback function in case the sql command 
			 * 	has feedback.
			 *
			 * @param sql_cmd SQL compatible command formatted as a 
			 * 	std::string.
			 * @param callback_fn Function to process potential feedback from
			 * 	an sql command.
			 */
			void execute_sql(
				const std::string& sql_cmd,
				int (*callback_fn) (void*, int, char**, char**)
			);

			/*
			 * @brief Callback function needed when the execution of sql 
			 * 	commands have feedback.
			 *
			 * @param not_used From 
			 * 	https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm, it
			 * 	holds the data provided by parameter col_name.
			 * @param argc The number of columns from a sql command.
			 * @param argv The contents from each column from a sql command.
			 * @param col_name The names of the columns.
			 */
			static int print_callback(void* not_used, 
					int argc, char** argv, char** col_name);

			static int todoitem_callback(void* not_used,
					int argc, char** argv, char** col_name);

		public:
			SQLiteDB();
			~SQLiteDB();

			/*
			 * @brief Will add all the attributes of the task to the database
			 *
			 * @param tdi The ToDoItem to add to the database
			 */
			void add_task(const ToDoItem& tdi);

			/*
			 * @brief Prints the contents of the todo database from todo.db
			 */
			void print_database();

			/*
			 * @brief Given a particular id, the method will search for that
			 *  entry and display it if it is found
			 *
			 * @param id The Pseudo unique id mostly likely given by some
			 * 	tdi.uid() method call.
			 */
			void print_task(unsigned long long id);

			/*
			 * @brief Given a particular id, the method will search for that
			 *  entry and return it as a ToDoItem class
			 *
			 * @param id The Pseudo unique id that will be searched in the
			 * 	database
			 */
			ToDoItem read_task(unsigned long long id);

			/*
			 * @brief Given a particular id, the method will search for an
			 * 	entry and delete if it exists.
			 */
			void delete_task(unsigned long long id);

			// TODO
			void update_task(const ToDoItem& tdi);
	};
}
#endif // FV_SQLITEDB_HPP
