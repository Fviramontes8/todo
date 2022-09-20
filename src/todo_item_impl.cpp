#include "../include/todo_app/todo_item.hpp"
#include "../include/todo_app/uid_generator.hpp"

#include <ostream>
#include <sstream>

namespace fv_todo {
	ToDoItem::ToDoItem(std::string title) : _created_at(), _completed_at(),
		_task_status{Status::IN_PROGRESS}, _title{title} {
		_unique_id = generate_uid();
	}

	unsigned long long ToDoItem::uid() const {
		return _unique_id;
	}

	std::string ToDoItem::title() const {
		return _title;
	}

	Date ToDoItem::created_at() const {
		return _created_at;
	}

	Date ToDoItem::completed_at() const {
		return _completed_at;
	}

	Status ToDoItem::status() const {
		return _task_status;
	}

	void ToDoItem::mark_complete() {
		_task_status = Status::COMPLETE;
		_completed_at.update();
	}

	std::string ToDoItem::status_to_str() const {
		std::string result_status;
		switch (status()) {
			case Status::IN_PROGRESS:
				result_status = "In-progress";
				break;
			case Status::COMPLETE:
				result_status = "Complete";
				break;
			default:
				result_status = "In-progress";
				break;
		}
		return result_status;
	}

	std::string ToDoItem::to_db_str() const {
		std::ostringstream db_str;
		db_str << _unique_id << ",'" << _title << "','" << _created_at;
		db_str << "','" << _completed_at << "','" << status_to_str() << "'";
		return db_str.str();
	}

	bool ToDoItem::operator==(const ToDoItem& other) {
		return (_title == other._title) &&
			(_created_at == other._created_at) &&
			(_completed_at == other._completed_at);
	}

	bool ToDoItem::operator!=(const ToDoItem& other) {
		return !(*this == other);
	}

	ToDoItem& ToDoItem::operator=(const ToDoItem& other) {
		if (this == &other) { return *this; }

		_unique_id = other._unique_id;
		_title = other._title;
		_created_at = other._created_at;
		_completed_at = other._completed_at;
		_task_status = other._task_status;

		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const ToDoItem& tdi) {
		out << "Task: " << tdi.title() << '\n' << "ID: " << tdi.uid() << '\n';
		out << "Status: " << tdi.status_to_str() << "\nCreated: ";
		out << tdi.created_at() << '\n';
		if (tdi.status() == Status::COMPLETE) {
			out << "Completed: " << tdi.completed_at() << '\n';
		}
		return out;
	}
}
