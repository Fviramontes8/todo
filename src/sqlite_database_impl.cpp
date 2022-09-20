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

	int SQLiteDB::callback(void* not_used,
			int argc, char* argv[], char** az_col_name) {
		for (int i=0; i<argc; ++i) {
			printf("%s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
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
		// Temporary placeholder incase KEY does not work
		// "UID CHAR(16) NOT NULL,"
		std::string sql_statement {
			"CREATE TABLE TODO("
			"ID INT PRIMARY KEY NOT NULL,"
			"TITLE TEXT NOT NULL,"
			"CREATED CHAR(10),"
			"COMPLETED CHAR(10),"
			"STATUS CHAR(11));"
		};
		char* z_err_msg = 0;
		int conn_res = sqlite3_exec(
			_database, 
			sql_statement.c_str(),
			callback, 
			0, 
			&z_err_msg
		);
		if (conn_res != SQLITE_OK) {
			// std::cerr << z_err_msg << '\n';
			write_to_db_log(std::string(z_err_msg));
			sqlite3_free(z_err_msg);
		}
		else {
			write_to_db_log("Created TODO table");
		}
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

	void SQLiteDB::add_task(const ToDoItem& tdi) {
		std::string begin_sql =
			"INSERT INTO TODO("
			"KEY TITLE CREATED COMPLETED STATUS) "
			"VALUES (";
		std::string end_sql = ");";
		std::string sql_statement = begin_sql+tdi.to_db_str()+end_sql;

		char* z_err_msg = 0;
		int conn_res = sqlite3_exec(
			_database, 
			sql_statement.c_str(),
			callback, 
			0, 
			&z_err_msg
		);
		if (conn_res != SQLITE_OK) {
			// std::cerr << z_err_msg << '\n';
			write_to_db_log(std::string(z_err_msg));
			sqlite3_free(z_err_msg);
		}
		else {
			write_to_db_log("Wrote to TODO table");
		}
	}
}

