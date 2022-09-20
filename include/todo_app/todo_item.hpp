#ifndef FV_TODO_ITEM
#define FV_TODO_ITEM

#include <ostream>
#include <string>

#include "date.hpp"

namespace fv_todo {
	/*
	 * @brief Designates two states of a task, in progress and complete
	 */
	enum class Status {
		IN_PROGRESS,
		COMPLETE
	};
	
	class ToDoItem {
		private:
			unsigned long long _unique_id;
			std::string _title;
			Date _created_at;
			Date _completed_at;
			Status _task_status;

			Date completed_at() const;
		public:
			/*
			 * @brief Parameterized constructor that takes a title and 
			 * 	automatically generates an id, will initialize the 
			 * 	_created_at attribute to the current timestamp
			 */
			ToDoItem(std::string title);

			/*
			 * @brief Getter for _unique_id attribute
			 *
			 * @return String containing pseudo-unique id
			 */
			unsigned long long uid() const;

			/*
			 * @brief Getter for _title attribute
			 *
			 * @return String containing the title of the task
			 */
			std::string title() const;

			/*
			 * @brief Getter for _created_at attribute
			 *
			 * @return A date class containing the task creation date
			 */
			Date created_at() const;

			/*
			 * @brief Getter for _task_status attribute
			 *
			 * @return Status enum detailing if the task is in-progress or
			 * 	complete
			 */
			Status status() const;

			/*
			 * @brief Will mark the task as complete and change the 
			 * 	_task_status from IN_PROGRESS to COMPLETE. The _completed_at
			 * 	attribute will also update to mark when the task is completed.
			 */ 
			void mark_complete();

			/*
			 * @brief Will take the enum and convert it to a string to
			 * 	represent the current state
			 *
			 * @return String representing the current status of the enum
			 */
			std::string status_to_str() const;

			/*
			 * @brief converts all attributes to a sql compatible string,
			 * 	namely having all attributes as comma separated values
			 *
			 * @return String of all attributes as comma separated values
			 */
			std::string to_db_str() const;

			/*
			 * @brief Adds additional functionality to the << operator, so
			 *  it can be printed with std::cout
			 *
			 * @param out An output stream (most likely cout) to write to
			 * @param tdi The ToDoItem class to print the attributes of
			 *
			 * @return The output stream after the class attributes have
			 * 	been written to
			 */
			friend std::ostream& operator<<(
					std::ostream& out, const ToDoItem& tdi);
	};
}
#endif // FV_TODO_ITEM
