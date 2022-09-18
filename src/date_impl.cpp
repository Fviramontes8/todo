#include "../include/todo_app/date.hpp"

namespace fv_todo {
	Date::Date() : _month{1}, _day{1}, _year{1970} {}

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
}
