#include <filesystem>
#include <iostream>
#include <string>
#include <sqlite3.h>

#include "../include/todo_app/sqlite_database.hpp"
#include "../include/todo_app/todo_item.hpp"

namespace fv_todo {
	SQLiteDB::SQLiteDB() : _database{nullptr} {
		check_db_folder();
		start_db();
		// create_todo_db();
	}

	SQLiteDB::~SQLiteDB() {
		sqlite3_close(_database);
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
		}
	}

	void SQLiteDB::start_db() {
		int conn_res = sqlite3_open("db/todo.db", &_database);
		if (conn_res) {
			std::cerr << "Cannot open todo database";
			exit(-1);
		}
	}

	void SQLiteDB::create_todo_db() {
		std::string sql_statement {
			"CREATE TABLE TODO("
			"ID INT PRIMARY KEY NOT NULL,"
			"UID CHAR(16) NOT NULL,"
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
			std::cerr << z_err_msg << '\n';
			sqlite3_free(z_err_msg);
		}
		else {
			std::cout << "Created TODO table\n";
		}
	}
}

