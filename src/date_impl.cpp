#include "../include/todo_app/date.hpp"

#include <ctime>
#include <ostream>

namespace fv_todo {
	Date::Date() {
		std::time_t timestamp = std::time(0);
		tm* local_time = localtime(&timestamp);
		_year = local_time->tm_year + 1900;
		_month = local_time->tm_mon + 1;
		_day = local_time->tm_mday;
	}

	Date::Date(unsigned int month, unsigned int day, unsigned int year) :
			_month{1}, _day{1}, _year{1970} {
		set_month(month);
		set_day(day);
		set_year(year);
	}

	unsigned int Date::check_month(unsigned int month) {
		if (month > 12) {
			month = 12;
		}
		return month;
	}

	void Date::set_month(unsigned int month) {
		_month = check_month(month);
	}

	unsigned int Date::check_day(unsigned int day) {
		switch (_month) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (day > 31) {
					day = 31;
				}
				break;

			case 4:
			case 6:
			case 9:
			case 11:
				if (day > 30) {
					day = 30;
				}
				break;

			case 2:
				if ( (_year % 4) == 0) {
					if (day > 29) {
						day = 29;
					}
				}
				if (day > 28) {
					day = 28;
				}
				break;
			default:
				_month = 12;
				_day = 31;
				break;
		}
		return day;
	}

	void Date::set_day(unsigned int day) {
		_day = check_day(day);
	}

	void Date::set_year(unsigned int year) {
		_year = year;
	}

	unsigned int Date::month() const {
		return _month;
	}

	unsigned int Date::day() const {
		return _day;
	}

	unsigned int Date::year() const {
		return _year;
	}

	std::ostream& operator<<(std::ostream& out, const Date& d) {
		out << d.month() << '/' << d.day() << '/' << d.year();
		return out;
	}
}
