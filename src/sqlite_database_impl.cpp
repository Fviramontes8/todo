#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <sqlite3.h>

#include "../include/todo_app/sqlite_database.hpp"
#include "../include/todo_app/todo_item.hpp"

namespace fv_todo {
	SQLiteDB::SQLiteDB() : _database{nullptr} {
		check_db_folder();
		start_db();
	}

	SQLiteDB::~SQLiteDB() {
		stop_db();
	}

	int SQLiteDB::print_callback(void* not_used,
			int argc, char** argv, char** az_col_name) {
		for (int i=0; i<argc; ++i) {
			std::cout << az_col_name[i] << "\t";
			std::cout << (argv[i] ? argv[i] : "NULL") << '\n';
		}
		std::cout << '\n';
		return 0;
	}

	void SQLiteDB::check_db_folder() {
		std::filesystem::path database_dir = "./db";
		if (const auto db_exists = std::filesystem::exists(database_dir);
				!db_exists) {
			std::filesystem::create_directory(database_dir);
			start_db();
			create_todo_db();
			stop_db();
		}
	}

	void SQLiteDB::start_db() {
		int conn_res = sqlite3_open("db/todo.db", &_database);
		if (conn_res) {
			std::cerr << "Cannot open todo database";
			exit(-1);
		}
	}

	void SQLiteDB::stop_db() {
		sqlite3_close(_database);
	}

	void SQLiteDB::create_todo_db() {
		std::string sql_statement {
			"CREATE TABLE TODO("
			"ID INT PRIMARY KEY NOT NULL,"
			"TITLE TEXT NOT NULL,"
			"CREATED TEXT,"
			"COMPLETED TEXT,"
			"STATUS TEXT);"
		};
		execute_sql(sql_statement, print_callback);
	}

	void SQLiteDB::write_to_db_log(std::string msg) {
		Date today;
		std::time_t timestamp = std::time(0);
		tm* local_time = localtime(&timestamp);
		std::ofstream log_file;
		log_file.open("db/log.txt", std::ios_base::app);
		if (log_file.is_open()) {
			log_file << today << ' ' << local_time->tm_hour << ':';
			log_file << local_time->tm_min << ':';
			log_file << local_time->tm_sec << ' ' << msg << '\n';
		}
		log_file.close();
	}

	void SQLiteDB::execute_sql(
			const std::string& sql_cmd,
			int (*callback_fn) (void*, int, char**, char**)) {
		char* z_err_msg = 0; int conn_res = sqlite3_exec(
			_database, 
			sql_cmd.c_str(),
			callback_fn, 
			0, 
			&z_err_msg
		);
		if (conn_res != SQLITE_OK) {
			write_to_db_log(std::string(z_err_msg));
			sqlite3_free(z_err_msg);
		}
		else {
			write_to_db_log(
					std::string("Successfully wrote: ") +
					sql_cmd
			);
		}
	}

	void SQLiteDB::add_task(const ToDoItem& tdi) {
		std::string begin_sql =
			"INSERT INTO TODO("
			"ID,TITLE,CREATED,COMPLETED,STATUS) "
			"VALUES (";
		std::string end_sql = ");";
		std::string sql_statement = begin_sql+tdi.to_db_str()+end_sql;
		execute_sql(sql_statement, print_callback);
	}

	void SQLiteDB::print_database() {
		std::string sql_statement = "SELECT * FROM TODO";
		execute_sql(sql_statement, print_callback);
	}

	void SQLiteDB::read_task(unsigned long long id) {
		std::string sql_begin = "SELECT * FROM TODO WHERE ID=";
		std::string id_str = std::to_string(id);
		execute_sql(
			std::string(sql_begin+id_str).c_str(),
			print_callback
		);
	}

	void SQLiteDB::delete_task(unsigned long long id) {
		std::string sql_begin = "DELETE from TODO where ID=";
		std::string id_str = std::to_string(id);
		execute_sql(
			std::string(sql_begin+id_str).c_str(),
			print_callback
		);
	}
}

