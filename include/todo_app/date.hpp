#ifndef FV_DATE
#define FV_DATE

#include <ctime>
#include <ostream>

namespace fv_todo {
	class Date {
		private:
			unsigned int _month;
			unsigned int _day;
			unsigned int _year;

			/*
			 * @brief Validates that the month is less than 12
			 *
			 * @param month The proposed month that must be validated
			 */
			unsigned int check_month(unsigned int month);

			/*
			 * @brief Validates that the day is less than the maximum day
			 * 	within the current state of the month
			 *
			 * @param month The proposed day that must be validated
			 */
			unsigned int check_day(unsigned int day);

		public:
			/*
			 * @brief Unparameterized constructor which will get the current
			 * 	timestamp and extracts the date from that information
			 */
			Date();

			/*
			 * @brief Parameterized constructor that will take a proposed
			 * 	month, day, and year, filter the month and day, then set
			 * 	those values to the attributes
			 */
			Date(unsigned int month, unsigned int day, unsigned int year);

			/*
			 * @brief Sets the month attribute of the class to the input
			 * 	provided, the input however, gets filtered
			 *
			 * @param month Represents the new month that the date will change
			 * 	to.
			 */
			void set_month(unsigned int month);

			/*
			 * @brief Sets the day attribute of the class to the input
			 * 	provided, the input however, gets filtered in coordination
			 * 	with the month
			 *
			 * @param day Represents the new day that the date will change
			 * 	to.
			 */
			void set_day(unsigned int day);

			/*
			 * @brief Sets the year attribute of the class to the input
			 * 	provided
			 *
			 * @param year Represents the new year that the date will change
			 * 	to.
			 */
			void set_year(unsigned int year);

			/*
			 * @brief Gets the month attribute of the date class
			 *
			 * @return An unsigned int representing the month
			 */
			unsigned int month() const;

			/*
			 * @brief Gets the day attribute of the date class
			 *
			 * @return An unsigned int representing the day
			 */
			unsigned int day() const;

			/*
			 * @brief Gets the year attribute of the date class
			 *
			 * @return An unsigned int representing the year
			 */
			unsigned int year() const;

			/*
			 * @brief Updates all attributes with the current timestamp
			 */
			void update();

			friend std::ostream& operator<<(std::ostream& out, const Date& d);
	};
}
#endif // FV_DATE
