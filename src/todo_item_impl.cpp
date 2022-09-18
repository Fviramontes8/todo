#include "../include/todo_app/todo_item.hpp"
#include "../include/todo_app/uid_generator.hpp"

#include <ostream>

namespace fv_todo {
	ToDoItem::ToDoItem(std::string title) : _created_at(), _completed_at(),
		_task_status{Status::IN_PROGRESS}, _title{title} {
		_unique_id = generate_uid();

	}
	std::string ToDoItem::uid() const {
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
